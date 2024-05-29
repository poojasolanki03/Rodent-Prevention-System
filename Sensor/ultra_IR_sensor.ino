#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>


//internet credentials
/* ======================================== */
const char* ssid = "Solanki";      //--> Enter your SSID / your WiFi network name.
const char* password = "asdfghjkl";  //--> Enter your WiFi password.
/* ======================================== */

//telegram credentials
/* ======================================== */
String BOTtoken = "6821060622:AAFvkwLfj0zdnRkZs5O4yAxpslHh1tFVQZw";  //--> your Bot Token (Get from Botfather).
String CHAT_ID = "5178788904"; //--> your chat ID (Get @myidbot)
/* ======================================== */

/* ======================================== Initialize WiFiClientSecure. */
WiFiClientSecure clientTCP;
/* ======================================== */

/* ======================================== Initialize UniversalTelegramBot. */
UniversalTelegramBot bot(BOTtoken, clientTCP);
/* ======================================== */


//Initializing sensor pins
#define trigPin 15
#define echoPin 13
#define Buzzer 4
#define IRout 14

//for LED Flash & buzzer
#define ldelay 500  
#define FLASH_LED_PIN 4
#define ON HIGH
#define OFF LOW

//Variables for millis()
int botRequestDelay = 1000; //Checks for new messages every 1 second (1000 ms).
unsigned long lastTimeBotRan;

//variables for Ultrasonic Sensor & IR Sensor
int warmup;
long duration, distance;
const int OutPin=12;

//initial values
int state=LOW;
int val=0;

//Subroutine to turn on or off the LED Flash.
void LEDFlash_State (bool ledState) {
  digitalWrite(FLASH_LED_PIN, ledState);
}

//Subroutine for beeping Buzzer
void alert() {  
      
    digitalWrite(Buzzer, HIGH);  
    delay(ldelay);  
    
    digitalWrite(Buzzer, LOW);  
    delay(ldelay);  
   
    digitalWrite(Buzzer, HIGH);  
    delay(ldelay);  
     
    digitalWrite(Buzzer, LOW);  
    delay(ldelay);  
 
    digitalWrite(Buzzer, HIGH);  
    delay(ldelay);  
    
    digitalWrite(Buzzer, LOW);  
    delay(ldelay);
    
}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  //Setting Baudrate
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");

  //Pin Modes
  pinMode(IRout, INPUT);
  pinMode(OutPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(FLASH_LED_PIN, OUTPUT); 
  pinMode(trigPin, OUTPUT);

  //Connect to Wi-Fi. 
  WiFi.mode(WIFI_STA);
  Serial.println("------------");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  clientTCP.setCACert(TELEGRAM_CERTIFICATE_ROOT); //--> Add root certificate for api.telegram.org
  int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    LEDFlash_State(ON);
    delay(250);
    LEDFlash_State(OFF);
    delay(250);
    if(connecting_process_timed_out > 0) connecting_process_timed_out--;
    if(connecting_process_timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }
  Serial.println();
  Serial.print("Successfully connected to ");
  Serial.println(ssid);
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP()); 
  Serial.println("------------");
  Serial.println();

  Serial.println("Waiting for power on warmup....");
  delay(20000);
  Serial.println("Ready!!");
}

void loop() {
  int sensorValue = digitalRead(IRout);
  int sensor = digitalRead(OutPin);
  String send_feedback_message = "";

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  String disp = String(distance);

  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if(sensorValue == LOW)
    {
    Serial.println("IR sensor detected an obstacle!");
    send_feedback_message += "Obstacle";
    bot.sendMessage(CHAT_ID, send_feedback_message, "");
    digitalWrite(IRout, LOW);  // turn on relay
    Serial.print("Distance: ");
    Serial.print(disp);
    Serial.println(" cm");
    delay(1000);
    alert();
    }
   /* while (numNewMessages) {
      Serial.println();
      Serial.println("------------");
      Serial.println("Got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    } */
    lastTimeBotRan = millis();
  }
}
