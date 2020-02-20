#include<Servo.h>
#include <NewPing.h>
#include "HX711.h"
#include <LiquidCrystal.h>
Servo servo1;
Servo servo2;
int angle=0;
int trigPin=5;
int echoPin=6;
#define TRIGGER_PIN 9
#define ECHO_PIN    8  
#define MAX_DISTANCE 200
#define DOUT 11
#define CLK  10
float z;
long distance;
long duration;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float calibration_factor = -7050;

HX711 scale;


void setup()
{
  servo1.attach(7);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  lcd.begin(16, 2);
  Serial.begin(9600);
  servo2.attach(4);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  
}

void loop()
{
  ultra();
  servo1.write(0);
  if(distance<=10)
  {
    servo1.write(90);
  }
  delay(50);                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");


  scale.set_scale(calibration_factor);
   z = (scale.get_units(), 1);
  Serial.print("Reading: ");
  Serial.print(-0.454*scale.get_units(), 1);
  Serial.print(" Kg");
  Serial.println();
   z = digitalRead((scale.get_units(), 1));
  delay(1000);
  if( z>0.1){
 
      servo2.write(90);
  }
  else{
    servo2.write(0);
  }

}

void ultra()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration =pulseIn(echoPin,HIGH);
  distance=duration*0.04/2;
}

