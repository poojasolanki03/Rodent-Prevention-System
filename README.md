# Rodent-Prevention-System
**Introduction:**

Rodents pose a significant threat to vehicles, causing extensive damage and safety hazards. This project introduces a pioneering solution: a rodent prevention system tailored for vehicle use during rest periods. The system integrates advanced sensors capable of detecting rodent activity and precisely locating the affected area. Upon detection, the system swiftly alerts the vehicle owner and employs innovative techniques to repel rodents.

**Features:**

Rodent Detection: Utilizes IR and ultrasonic sensors to detect rodent presence and measure distance.

Notification System: Sends real-time alerts and images via the Telegram application.

Rodent Repellent: Emits deterrent ultrasonic waves and activates a buzzer to scare rodents away.

Remote Monitoring: Allows users to monitor the system and receive notifications on their smartphones or tablets.

**Installation

Prerequisites**

-Arduino IDE

-ESP32 CAM Module

-FTDI Programmer

-Telegram Account and Bot API Token


**Steps**

1.Clone the repository:

git clone https://github.com/poojasolanki03/rodent-prevention-system.git

cd rodent-prevention-system


2.Install dependencies:
Ensure you have the necessary libraries installed in the Arduino IDE:

-WiFi
-WiFiClientSecure
-ArduinoJson
-UniversalTelegramBot

3.Configure the ESP32 CAM:
-Connect the FTDI programmer to the ESP32 CAM module.
-Open the rodent_prevention.ino file in the Arduino IDE.
-Replace placeholder values with your WiFi credentials and Telegram Bot API token.
-Select the appropriate board and port, then upload the code.

**Usage**
1.Power on the ESP32 CAM module.
2.Monitor the Telegram bot:
-The bot will send alerts and images when rodent activity is detected.
-View the captured images and take necessary actions to prevent rodent damage.

