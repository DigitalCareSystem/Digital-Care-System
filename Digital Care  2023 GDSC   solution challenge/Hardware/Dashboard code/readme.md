# Dashboard device:
It is a device placed next to the secretariat that receives alerts from the vital signs transmitter in case the nurse does not respond to the alarm and displays the name of the patient supervising nurse, room number and bed number on the screen.


![image](https://drive.google.com/uc?export=view&id=1cBKX9p7hML5MsPuUlK7_cI6HAmZe9TOi)


## How does the vital signs measurement device work?

The control panel works when connected to the Internet. It starts receiving alerts from the devices associated with the patient. In case the nurse following the patient does not respond, an alert is sent to the control panel located in the secretariat, and then it sends another nurse to see the patient’s condition.



# Tools used in the device

### 1- ESP32 Development Board :

The ESP32 is a series of low-cost and low-power System on a Chip (SoC) microcontrollers developed by Espressif that include Wi-Fi and Bluetooth wireless capabilities and dual-core processor. If you’re familiar with the ESP8266, the ESP32 is its successor, loaded with lots of new features.

![ESP32 Development Board](https://circuitdigest.com/sites/default/files/inlineimages/u/ESP32-module.png)


### 2- We used many connecting wires of all kinds (male-male, female-female, and female-male)


### 3- pushbutton, LED

### 4- Bell to tirn on when there is emargancey state 

### 5- Mobile with intrnet and our application in it 

# How to implement the program into the device:
We need many offices to implement the code in the device.
How to download it to the device, install it and run the program will be explained

###this is the library you should install it in code 
#####  include <LiquidCrystal_I2C.h> https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git
##### include <WiFi.h> https://github.com/arduino-libraries/WiFi.git
##### include <Firebase_ESP_Client.h>  https://github.com/mobizt/Firebase-ESP-Client.git
##### include <Wire.h> https://github.com/esp8266/Arduino.git


to install it in your computer  follow this step 

We will use Arduino IDE to program our ESP32 . Thus, you should have the latest version of Arduino IDE. Open Arduino IDE and click on Sketch > Library > Manage Libraries


1- ![first step](https://microcontrollerslab.com/wp-content/uploads/2021/05/MPU-6050-Install-library.jpg)


The following window will open up.


2- ![Second step](https://microcontrollerslab.com/wp-content/uploads/2021/05/search-library-Arduino-IDE.jpg)


Type ‘MAX3010x’ in the search bar and press enter. Install the latest version of the SparkFun MAX3010x Pulse and Proximity Sensor Library.


3-![third step](https://microcontrollerslab.com/wp-content/uploads/2022/04/Install-MAX30102-Library.jpg)



