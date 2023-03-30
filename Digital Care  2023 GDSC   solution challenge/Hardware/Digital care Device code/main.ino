//==========================================Start Library Firebase========================
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "root"
#define WIFI_PASSWORD "11221122"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCzO_rDj1dUSfQkunRKpU_fALSjsR7nTqs"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://patient-observing1-default-rtdb.firebaseio.com//" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
//==========================================End Library Firebase========================

//================================================
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <EEPROM.h>
#include "MAX30105.h" //sparkfun MAX3010X library
MAX30105 particleSensor;
LiquidCrystal_I2C lcd(0x27,20,4);
//#define MAX30105 //if you have Sparkfun's MAX30105 breakout board , try #define MAX30105 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
double avered = 0; double aveir = 0;
double sumirrms = 0;
double sumredrms = 0;
int i = 0;
int Num = 100;//calculate SpO2 by this sampling interval
int Temperature;
int temp;
float ESpO2;//initial value of estimated SpO2
float ESpO2_ROM;
double FSpO2 = 0.7; //filter factor for estimated SpO2
double frate = 0.95; //low pass filter for IR/red LED value to eliminate AC component
#define TIMETOBOOT 3000 // wait for this time(msec) to output SpO2
#define SCALE 88.0 //adjust to display heart beat and SpO2 in the same scale
#define SAMPLING 5 //if you want to see heart beat more precisely , set SAMPLING to 1
#define FINGER_ON 30000 // if red signal is lower than this , it indicates your finger is not on the sensor
#define USEFIFO
#define Greenled 18
#define Redled 19
const int BUTTON_PIN =4;  // ESP32 pin GIOP16, which connected to button
const int LED_PIN    =5;  // ESP32 pin GIOP18, which connected to led

int button_state = 0; 
void setup()
{
          Serial.begin(115200);

         // initialize the LED pin as an output:
          pinMode(LED_PIN, OUTPUT);

          // initialize the button pin as an pull-up input:
          // the pull-up input pin will be HIGH when the button is open and LOW when the button is pressed.
          pinMode(BUTTON_PIN, INPUT);
        //==========================================Start Setup Firebase========================

        //

          WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
          Serial.print("Connecting to Wi-Fi");
          while (WiFi.status() != WL_CONNECTED)
          {
              Serial.print(".");
              delay(300);
          }
          Serial.println();
          Serial.print("Connected with IP: ");
          Serial.println(WiFi.localIP());
          Serial.println();

          /* Assign the api key (required) */
          config.api_key = API_KEY;

          /* Assign the RTDB URL (required) */
          config.database_url = DATABASE_URL;

          /* Sign up */
          if (Firebase.signUp(&config, &auth, "", ""))
          {
                Serial.println("ok");
                signupOK = true;
          }
          else
          {
                Serial.printf("%s\n", config.signer.signupError.message.c_str());
          }

          /* Assign the callback function for the long running token generation task */
          config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

          Firebase.begin(&config, &auth);
          Firebase.reconnectWiFi(true);



        //==========================================End Library Firebase========================

          ESpO2 = readEEPROM();
          Temperature = EEPROM.read(6);
          // Initialize sensor
          while (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
          {
              Serial.println("MAX30102 was not found. Please check wiring/power/solder jumper at MH-ET LIVE MAX30102 board. ");
              //while (1);
          }

          //Setup to sense a nice looking saw tooth on the plotter
          byte ledBrightness = 0x7F; //Options: 0=Off to 255=50mA
          byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
          byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
          //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
          int sampleRate = 200; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
          int pulseWidth = 411; //Options: 69, 118, 215, 411
          int adcRange = 16384; //Options: 2048, 4096, 8192, 16384
          // Set up the wanted parameters
          Serial.begin(115200);
          particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

          particleSensor.enableDIETEMPRDY();
          mlx.begin();
}

void loop()
{
  
  uint32_t ir, red , green;
  double fred, fir;
  double SpO2 = 0; //raw SpO2 before low pass filtered
  int hr=HR();
  bool led=led_button();
#ifdef USEFIFO
  particleSensor.check(); //Check the sensor, read up to 3 samples

  while (particleSensor.available()) {//do we have new data
#ifdef MAX30105
   red = particleSensor.getFIFORed(); //Sparkfun's MAX30105
    ir = particleSensor.getFIFOIR();  //Sparkfun's MAX30105
#else
    red = particleSensor.getFIFOIR(); //why getFOFOIR output Red data by MAX30102 on MH-ET LIVE breakout board
    ir = particleSensor.getFIFORed(); //why getFIFORed output IR data by MAX30102 on MH-ET LIVE breakout board
#endif

    
    
    i++;
    fred = (double)red;
    fir = (double)ir;
    avered = avered * frate + (double)red * (1.0 - frate);//average red level by low pass filter
    aveir = aveir * frate + (double)ir * (1.0 - frate); //average IR level by low pass filter
    sumredrms += (fred - avered) * (fred - avered); //square sum of alternate component of red level
    sumirrms += (fir - aveir) * (fir - aveir);//square sum of alternate component of IR level
    if ((i % SAMPLING) == 0) {//slow down graph plotting speed for arduino Serial plotter by thin out
      if ( millis() > TIMETOBOOT) {
                          float ir_forGraph = (2.0 * fir - aveir) / aveir * SCALE;
                          float red_forGraph = (2.0 * fred - avered) / avered * SCALE;
                          //trancation for Serial plotter's autoscaling
                          if ( ir_forGraph > 100.0) ir_forGraph = 100.0;
                          if ( ir_forGraph < 80.0) ir_forGraph = 80.0;
                          if ( red_forGraph > 100.0 ) red_forGraph = 100.0;
                          if ( red_forGraph < 80.0 ) red_forGraph = 80.0;
                          //        Serial.print(red); Serial.print(","); Serial.print(ir);Serial.print(".");
                          float temperature = particleSensor.readTemperatureF();
                          
                         
                          if (ir < FINGER_ON)
                          {
                                  temp = Temperature;
                                  EEPROM.write(6,temp);
                                  ESpO2_ROM = ESpO2;
                                  writeEEPROM(&ESpO2_ROM);
                                 
                                  
                                  break;
                          }
                          if(ir > FINGER_ON)
                          {
                                Temperature = mlx.readObjectTempC();
                                   firebase(ESpO2,hr,led,Temperature);
                  
                          } 
                 
                      }
    }
    
    if ((i % Num) == 0)
    {
            double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
            // Serial.println(R);
            SpO2 = -23.3 * (R - 0.4) + 100; //http://ww1.microchip.com/downloads/jp/AppNotes/00001525B_JP.pdf
            ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;//low pass filter
            //  Serial.print(SpO2);Serial.print(",");Serial.println(ESpO2);
            sumredrms = 0.0; sumirrms = 0.0; i = 0;
            break;
    }         
    particleSensor.nextSample(); //We're finished with this sample so move to next sample
   // Serial.println(SpO2);
  }
#endif
}
// this Function for Write in EEPROM 
void writeEEPROM(float *data)
{
     byte ByteArray[4];
     memcpy(ByteArray, data, 4);
     for(int x = 0; x < 4; x++)
     {
       EEPROM.write(x, ByteArray[x]);
     }  

}
// this Function for read in EEPROM 

float readEEPROM()
{
      float ESpO2 = 85.0;
      byte ByteArray[4];
       memcpy(&ESpO2, ByteArray, 4);
      for(int x = 0; x < 4; x++)
      {
       ByteArray[x] = EEPROM.read(x);    
      }
 
  return ESpO2;
}
double HR(){

 long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
            //We sensed a beat!
            long delta = millis() - lastBeat;
            lastBeat = millis();
        
            beatsPerMinute = 60 / (delta / 1000.0);
            if (beatsPerMinute < 255 && beatsPerMinute > 20)
            {
                    rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
                    rateSpot %= RATE_SIZE; //Wrap variable
              
                    //Take average of readings
                    beatAvg = 0;
                    for (byte x = 0 ; x < RATE_SIZE ; x++)
                      beatAvg += rates[x];
                    beatAvg /= RATE_SIZE;
            }
    
  }
  //
  if (irValue < 50000)
        Serial.print(" No finger?");

  
return beatAvg;
}

//=========================== Send to firebase  =============================================
float firebase(int ESpO2,int HR,bool led ,double Temp){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)){
              sendDataPrevMillis = millis();
              // Write an Int number on the database path test/int
              if (Firebase.RTDB.setInt(&fbdo, "Bed/newbarcode/HR", HR))
              {
                      Serial.println("PASSED");
                      Serial.println("TYPE: " + fbdo.dataType());
                      Serial.println( HR);
              }
              else 
              {
                      Serial.println("FAILED");
                      Serial.println("REASON: " + fbdo.errorReason());
              }
              count++;
              
          //    // Write an Float number on the database path test/float
              if (Firebase.RTDB.setBool(&fbdo, "Bed/newbarcode/B_state",led))
              {
                      Serial.println("PASSED");
                      Serial.println("PATH: " + fbdo.dataPath());
                      Serial.println("TYPE: " + fbdo.dataType());
              }
              else 
              {
                      Serial.println("FAILED");
                      Serial.println("REASON: " + fbdo.errorReason());
              }
               // Write an Int number on the database path test/int
              if (Firebase.RTDB.setInt(&fbdo, "Bed/newbarcode/SPO2", ESpO2))
              {
                      Serial.println("PASSED");
                      Serial.println("TYPE: " + fbdo.dataType());
                      Serial.println( ESpO2);
              }
              else 
              {
                      Serial.println("FAILED");
                      Serial.println("REASON: " + fbdo.errorReason());
              }
                if (Firebase.RTDB.setInt(&fbdo, "Bed/newbarcode/Temp", Temp))
                {
                      Serial.println("PASSED");
                      Serial.println("TYPE: " + fbdo.dataType());
                      Serial.println( ESpO2);
              }
              else 
              {
                      Serial.println("FAILED");
                      Serial.println("REASON: " + fbdo.errorReason());
              }
              
  }
  }


bool led_button(){
  
           button_state = digitalRead(BUTTON_PIN);
        
          // control LED according to the state of button
          if (button_state == HIGH) {      // if button is pressed
                digitalWrite(LED_PIN, LOW);
               return true;
         }// turn on LED
          else{           
           
                // otherwise, button is not pressing
                digitalWrite(LED_PIN, HIGH);
                return false;
            }// turn off LED
  
  }
  
