/*
**********************************************************************************
Tekbot Arduino Code

Arduino code to control tekbot in default bump bot behavior
Mimics functionality of analog control board
**********************************************************************************
*/
#include <Adafruit_NeoPixel.h>

#define NEOPIN1 4
#define NEOPIN2 3
Adafruit_NeoPixel pixels1(1, NEOPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(1, NEOPIN2, NEO_GRB + NEO_KHZ800);

#define motor1Ch1 8 //left motor
#define motor1Ch2 9 
#define motor2Ch1 10 //right motor
#define motor2Ch2 11

#define motor1Enable 5
#define motor2Enable 6

#define leftBumper 7
#define rightBumper 12

#define BACKUPDELAY 700  //time in milliseconds for robot to back up
#define TURNDELAY 450      //time in milliseconds for robot to turn

int Data; // the data received

void setup() {
  Serial.begin(9600);
  Serial.println("0 to go forward, 1 to bo backward, 2 to turn right, 3 to turn left, 4 to stop");
  pinMode(motor1Ch1, OUTPUT);
  pinMode(motor1Ch2, OUTPUT);
  pinMode(motor2Ch1, OUTPUT);
  pinMode(motor2Ch2, OUTPUT);
  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Enable, OUTPUT);

  pinMode(leftBumper, INPUT_PULLUP);
  pinMode(rightBumper, INPUT_PULLUP);

  
  analogWrite(motor1Enable, 210);
  analogWrite(motor2Enable, 210);  

  stop_bot(); 
  pixels1.begin();
  pixels2.begin();
}

void loop() {
   if (Serial.available()){ //wait for data received
      Data = Serial.read();
      if(Data=='1'){ 
        Serial.println("Forward"); 
        forward();
      }
      if(Data=='2'){
         Serial.println("Backwards");
         back_up();
      }
      if(Data=='3'){
        Serial.println("Left");
        turn_left();
        delay(200);
        stop_bot();
       }
      if(Data=='4'){
         Serial.println("Right");
         turn_right();
         delay(200);
         stop_bot();
      }
      if(Data=='5'){
         Serial.println("Stop");
         stop_bot();
      }
      if(Data == '6'){
        Serial.println("DONUT");
        turn_right();
      }
   }

    if((!digitalRead(leftBumper)) && (!digitalRead(rightBumper))){
      Serial.println("both bumpers");
      //back up
      back_up();
      //wait
      delay(BACKUPDELAY);
      //turn right
      turn_right();
      //wait
      delay(700);
      //set bot forward
      forward();
      delay(400);
      stop_bot();
    }
    if(!digitalRead(leftBumper)){
      Serial.println("left bumper");
      //turn bot right
      back_up();
      //wait
      delay(BACKUPDELAY);
      //turn right
      turn_right();
      //wait
      delay(TURNDELAY);
      //set bot forward
      forward();
      delay(500);
      stop_bot();
    }
    if(!digitalRead(rightBumper)){
      Serial.println("right bumper");
      //turn bot left
      back_up();
      //wait
      delay(BACKUPDELAY);
      //turn left
      turn_left();
      //wait
      delay(TURNDELAY);
      //set bot forward
      forward();
      delay(500);
      stop_bot();
    } 
} 

void back_up(){
    //set bot to back up
    digitalWrite(motor1Ch1, LOW);
    digitalWrite(motor1Ch2, HIGH);
    digitalWrite(motor2Ch1, LOW);
    digitalWrite(motor2Ch2, HIGH);
    
    pixels1.clear();
    pixels1.setPixelColor(0, pixels1.Color(255, 69, 0));
    pixels1.show();
    pixels2.clear();
    pixels2.setPixelColor(0, pixels2.Color(255, 69, 0));
    pixels2.show();
}

void turn_left(){
    //set bot to turn left
    digitalWrite(motor1Ch1, LOW);
    digitalWrite(motor1Ch2, HIGH);
    digitalWrite(motor2Ch1, HIGH);
    digitalWrite(motor2Ch2, LOW);

    pixels2.clear();
    pixels1.clear();
    pixels1.setPixelColor(0, pixels1.Color(0, 100, 100));
    pixels1.show();
}

void turn_right(){
    //set bot to turn right
    digitalWrite(motor1Ch1, HIGH);
    digitalWrite(motor1Ch2, LOW);
    digitalWrite(motor2Ch1, LOW);
    digitalWrite(motor2Ch2, HIGH);

    pixels1.clear();
    pixels2.clear();
    pixels2.setPixelColor(0, pixels2.Color(0, 100, 100));
    pixels2.show();
}

void forward(){
    //set bot to move forward
    digitalWrite(motor1Ch1, HIGH);
    digitalWrite(motor1Ch2, LOW);
    digitalWrite(motor2Ch1, HIGH);
    digitalWrite(motor2Ch2, LOW);
    
    pixels1.clear();
    pixels1.setPixelColor(0, pixels1.Color(0, 200, 0));
    pixels1.show();
    pixels2.clear();
    pixels2.setPixelColor(0, pixels2.Color(0, 200, 0));
    pixels2.show();
}

void stop_bot(){
    //set bot to back up
    digitalWrite(motor1Ch1, HIGH);
    digitalWrite(motor1Ch2, HIGH);
    digitalWrite(motor2Ch1, HIGH);
    digitalWrite(motor2Ch2, HIGH);

    pixels1.clear();
    pixels1.setPixelColor(0, pixels1.Color(200, 0, 0));
    pixels1.show();
    pixels2.clear();
    pixels2.setPixelColor(0, pixels2.Color(200, 0, 0));
    pixels2.show();
}
