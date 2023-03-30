#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>
#define WIFI_SSID "root"

#define WIFI_PASSWORD "11221122"

// Insert Firebase project API Key

#define API_KEY "AIzaSyCzO_rDj1dUSfQkunRKpU_fALSjsR7nTqs"

// ----Insert real-time database URL

#define DATABASE_URL "https://patient-observing1-default-rtdb.firebaseio.com//"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//======================================LED_LCD_BUTTONT=================================

#include <LiquidCrystal_I2C.h>
// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN =2;  // ESP32 pin GIOP16, which connected to button
 
const int alart =4;// the number of the LED pin

// variables will change:
int button_state = 0;        // variable for reading the pushbutton status
LiquidCrystal_I2C lcd(0x27,20,4);

//======================================LED_LCD_BUTTONT=================================




void FireBase_setup();
void FireBase_setup();
void LED_LCD_BUTTONT_Setup();
bool LED_LCD_BUTTONT_loop();
void setup()
{

  Serial.begin(115200);
    
  LED_LCD_BUTTONT_Setup();
 FireBase_setup();
}

void loop()
{

  bool led=LED_LCD_BUTTONT_loop();
  Firebase_loop(led);
}
bool LED_LCD_BUTTONT_loop()
{
                      button_state = digitalRead(BUTTON_PIN);
                      Serial.println(button_state);
              
         
                // control LED according to the state of button
                if (button_state == HIGH) {      // if button is pressed
                  
                   digitalWrite(alart, LOW);
                   

                   return false;
                   }// turn on LED
                else{                           // otherwise, button is not pressing
                 
                   digitalWrite(alart, HIGH);
                   
                   return true;}// turn off LED


            
  }
void LED_LCD_BUTTONT_Setup()
{
  
          lcd.init();
          lcd.backlight();
          lcd.setCursor(3,1);
          lcd.print("| Digital Care.|");
          delay(3000);
          lcd.clear();
          lcd.setCursor(0,0);
                lcd.print("nurse:");
                lcd.setCursor(0,1);
                 lcd.print("Ro:");
                 lcd.setCursor(8,1);
                  lcd.print("Bed:");
          
      
         pinMode(BUTTON_PIN, INPUT);
         pinMode(alart,OUTPUT);
        
  
  }
void FireBase_setup()
{
  
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
              Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
            
              /* Assign the api key (required) */
              config.api_key = API_KEY;
              config.database_url = DATABASE_URL;
              Firebase.begin(DATABASE_URL, API_KEY); 
              }
            
  void Firebase_loop(bool led){
                if (Firebase.ready()) 
              {
    
              String d=Firebase.getInt(fbdo,"Nurse/-NP34Gf63YLCvDzD-OHS/Name" ) ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str();
               lcd.setCursor(6,0);
                lcd.print(d);
                String room=Firebase.getInt(fbdo,"Bed/jahdflkjasdfsdfsd123/Room_Number" ) ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str();
               lcd.setCursor(4,1);
                lcd.print(room);
                String num=Firebase.getInt(fbdo,"Bed/jahdflkjasdfsdfsd123/Number" ) ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str();
               lcd.setCursor(12,1);
                lcd.print(num);
              Serial.println(d);
//            Serial.printf("Get int a--  %s\n", Firebase.getInt(fbdo,dat ) ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str());
            
                  
            
              }
    }
