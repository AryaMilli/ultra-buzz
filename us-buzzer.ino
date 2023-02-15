#define BLYNK_TEMPLATE_ID           "TMPLryMBKPtt"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "ygcz0V187rj_eUIgChaYV7nJmILSBrPc"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define MA1 14
#define MA2 12
#define MB1 13
#define MB2 15
#define trigpin 6 //pinout
#define echopin 7
#define buzzer_pin 9
float duration,distance;

char ssid[] = "";
char pass[] = "";
char auth[ ] = "1BsQMUXjC4lRc4JB70fr2xODw93RgdHA";
 
Servo myservo; 
BlynkTimer timer;

int pos = 0;  
int servoPin = 19;

BLYNK_WRITE(V1){ //moving forward
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Forward
   digitalWrite(MA1,HIGH);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,HIGH);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Forward");
 }
}

BLYNK_WRITE(V2){ //moving backward
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Backward
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,HIGH);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,HIGH);
   Serial.println("Moving Backwards");
 }
}

BLYNK_WRITE(V3){ //moving left
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Left
   digitalWrite(MA1,HIGH);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Left");
 }
}

BLYNK_WRITE(V4){ //moving right
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Right
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,HIGH);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Right");
 }
}
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
void setup() {
  pinMode(MA1, OUTPUT);
  pinMode(MA2,OUTPUT);
  pinMode(MB1,OUTPUT);
  pinMode(MB2,OUTPUT);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
  myservo.attach(servoPin, 500, 2400); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}
 void loop() {
  
  Blynk.run();
  timer.run();

  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.println(distance);
  delay(100);
  if(distance<13){
    digitalWrite(MB1,LOW);
    digitalWrite(MA1,LOW);
    digitalWrite(MA2,LOW);
    digitalWrite(MB1,LOW);
   }
  //myservo.write(60);
  if(distance<=13){
    myservo.write(150);
    tone(buzzer_pin, 500);
  }
}
