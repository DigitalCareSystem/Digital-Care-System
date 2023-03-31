Digital Care, used in this code 3.3.1 version of flutter and MVVM archictcure design pattern,
with GETX for state management, it contains SignUp screen, Login screen, Home screen, patients history list screen,
patient list screen, for the backend used firebase realtime, firebase firestore
this system for now will get only the Temprutre, Heart Rate and SPO2 for the patient, it could be more in future, if these vital signs goes beyond the normal range it gives alarm with a notification that the alarm speaks of the room number and the bed number the same of the notificaiton, when the notificaiton is tapped it Navgiate to the patient detials page.
and contains a proberity to call the nurse in case if the patient wants some help will send a notification to the nurse with the name of the patient and the room number with the bed number, when the notificaiton is tapped it Navgiate to the patient detials page.

## SignUp screen:
this screen use to create account for the users doctors or nurses by the admin. 

## Login screen:
screen that the user (nurse or doctor) will insert his information (that was created by the admin) to log in into the Homepage. 

## Homepage:
screen that contains a QR code section to scan the bed QR code to insert a ptient or show the patient vital signs or modifiy the information in case the patient changed from the bed. 

## patient list screen:
screen that shows all the patients that the nurse or the doctor took in his list that contains the patient's information (name and age), and vital signs that is in realtime.

## patients history list screen: 
this screen shows all the patients that the nurse hvae taken even if the patient leave the hospital,
this screen contains their information, and genrateing report that is contains the patient signs in each hour that he came into the hospital, and contains another report that contains only the vital signs that goes beyond the normal range,



## the third party packages used in this programm:
  get: ^4.6.5
  
  firebase_core: ^2.6.1
  
  shared_preferences: ^2.0.17
  
  firebase_database: ^10.0.13
  
  flutter_spinkit: ^5.1.0
  
  firebase_messaging: ^14.2.5
  
  velocity_x: ^3.6.0
  
  workmanager: ^0.5.1
  
  flutter_isolate: ^2.0.4
  
  flutter_tts: ^3.6.3
  
  lottie: ^2.2.0
  
  flutter_barcode_scanner:
  
  page_transition: ^2.0.9
  
  flutter_staggered_animations: ^1.1.1
  
  introduction_screen: ^3.1.4
  
  audioplayers: ^0.19.1
  
  printing: ^5.0.0
  
  cloud_firestore: ^4.4.5
  
  awesome_notifications: ^0.7.4+1
  


