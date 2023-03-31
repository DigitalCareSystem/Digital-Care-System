# vital signs measurement device:
It is a device used to measure the vital signs of the human body and sends the vital signs to a mobile application that is placed in the wrist and the sensor is connected to the sensitive finger for measuring heart rate and oxygen saturation and the other sensor is placed at the bottom of the device so that it is connected to the wrist and it is necessary To be at a distance in the sensor and the human body a very short distance


## How does the vital signs measurement device work?

The device consists of three sensors placed in the hand, the first is at the bottom of the device, and the second is a connection from the device to the finger and tied to the finger. The device is installed in the wrist in a correct manner, taking into account the distance between the temperature sensor and the human body. It is necessary to make a very small distance, and after the process of placing it on the hand, it is Connecting the heart sensor and oxygen saturation to the finger. Pay attention during the connection process to the negative and positive electrode in the connection. After the process of placing the device in the hand, the device is turned on using a USB connection. The device uses 5 volts to 3.5 volts while connecting the device to electricity. It turns on the Wi-Fi model and connects to the pre-selected network. And after the process of successful connection to the network, the device sends data to the database and our application is connected to the Internet and connects to the database and takes data from there and updates it in real time



# Tools used in the device
### 1-	Interfacing MAX30102 Pulse Oximeter and Heart Rate Sensor: 

The MAX30102 pulse oximeter and heart rate sensor is an I2C-based low-power plug-and-play biometric sensor. It can be used by students, hobbyists, engineers, manufacturers, and game & mobile developers who want to incorporate live heart-rate data into their projects.
The module features the MAX30102 – a modern (the successor to the MAX30100), integrated pulse oximeter and heart rate sensor IC, from Analog Devices. It combines two LEDs, a photodetector, optimized optics, and low-noise analog signal processing to detect pulse oximetry (SpO2) and heart rate (HR) signals.


![MAX30102](https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MAX30102-Module-Hardware-Overview-IC-and-LEDs.jpg)
 
 
 ### 2- Interface MLX90614 Non-contact Infrared Temperature Sensor: 
 
 Since the emergence of COVID-19, non-contact infrared temperature scanners have been popping up everywhere around the world, from airports to restaurants. Maybe you are curious about these temperature scanners, or maybe you’re interested in building one. Well, in that case, the Melexis MLX90614 Module might be the best inexpensive option out there.
 
 
 ![MLX90614](https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MLX90614-Module-Hardware-Overview.jpg)



### 3- ESP32 Development Board :

The ESP32 is a series of low-cost and low-power System on a Chip (SoC) microcontrollers developed by Espressif that include Wi-Fi and Bluetooth wireless capabilities and dual-core processor. If you’re familiar with the ESP8266, the ESP32 is its successor, loaded with lots of new features.

![ESP32 Development Board](https://circuitdigest.com/sites/default/files/inlineimages/u/ESP32-module.png)


### 4- We used many connecting wires of all kinds (male-male, female-female, and female-male)


### 5- pushbutton, LED

### 6- Mobile with intrnet and our application in it 

# How to implement the program into the device:
We need many offices to implement the code in the device.
How to download it to the device, install it and run the program will be explained

###this is the library you should install it in code 
##### include <Arduino.h>  https://github.com/esp8266/Arduino.git
##### include <WiFi.h> https://github.com/arduino-libraries/WiFi.git
##### include <Firebase_ESP_Client.h>  https://github.com/mobizt/Firebase-ESP-Client.git
##### include <Wire.h> https://github.com/esp8266/Arduino.git
##### include "MAX30105.h" https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library.git
##### include "heartRate.h" https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library.git

to install it in your computer  follow this step 

We will use Arduino IDE to program our ESP32 . Thus, you should have the latest version of Arduino IDE. Open Arduino IDE and click on Sketch > Library > Manage Libraries


1- ![first step](https://microcontrollerslab.com/wp-content/uploads/2021/05/MPU-6050-Install-library.jpg)


The following window will open up.


2- ![Second step](https://microcontrollerslab.com/wp-content/uploads/2021/05/search-library-Arduino-IDE.jpg)


Type ‘MAX3010x’ in the search bar and press enter. Install the latest version of the SparkFun MAX3010x Pulse and Proximity Sensor Library.


3-![third step](https://microcontrollerslab.com/wp-content/uploads/2022/04/Install-MAX30102-Library.jpg)



