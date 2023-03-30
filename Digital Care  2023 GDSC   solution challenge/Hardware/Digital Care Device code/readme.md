# Digital care device:
It is a device used to measure the vital signs of the human body and sends the vital signs to a mobile application that is placed in the wrist and the sensor is connected to the sensitive finger for measuring heart rate and oxygen saturation and the other sensor is placed at the bottom of the device so that it is connected to the wrist and it is necessary To be at a distance in the sensor and the human body a very short distance

# The physical side of the project will now be explained

## Tools used in the device
1-	Interfacing MAX30102 Pulse Oximeter and Heart Rate Sensor: The MAX30102 pulse oximeter and heart rate sensor is an I2C-based low-power plug-and-play biometric sensor. It can be used by students, hobbyists, engineers, manufacturers, and game & mobile developers who want to incorporate live heart-rate data into their projects.
The module features the MAX30102 – a modern (the successor to the MAX30100), integrated pulse oximeter and heart rate sensor IC, from Analog Devices. It combines two LEDs, a photodetector, optimized optics, and low-noise analog signal processing to detect pulse oximetry (SpO2) and heart rate (HR) signals.
https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MAX30102-Module-Hardware-Overview-IC-and-LEDs.jpg
![MAX30102]([http://url/to/img.png](https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MAX30102-Module-Hardware-Overview-IC-and-LEDs.jpg))
 
Behind the window on one side, the MAX30102 has two LEDs – a RED and an IR LED. On the other side is a very sensitive photodetector. The idea is that you shine a single LED at a time, detecting the amount of light shining back at the detector, and, based on the signature, you can measure blood oxygen level and heart rate.
