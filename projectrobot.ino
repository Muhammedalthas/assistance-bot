
#define staff_1 0
#define s1  1
#define s3  2
#define s5  3
#define staff_2  4
#define lab  5

  
 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

String content= "";

#define Dept_1 "1B 12 BC 22"
#define Dept_2 "F9 6D 82 3B"
#define S1  "F9 5E B4 3C"
#define S3   "09 B5 B0 3B"
#define S5   "99 76 CA 3C"

#define switch_dept_1 14
#define switch_dept_2 15
#define switch_s1 16
#define switch_s3 17
#define switch_s5 18
#define switch_lab 19



   // Create MFRC522 instance.


#define enA 2//Enable1 L298 Pin enA 
#define in1 3 //Motor1  L298 Pin in1 
#define in2 4 //Motor1  L298 Pin in1 
#define in3 5 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 7 //Enable2 L298 Pin enB 

#define R_S A2 //ir sensor Right
#define L_S A3 //ir sensor Left
#define S_S A3 //ir sensor Senter

#define slowSpeed 170
#define mediumSpeed 200
#define fastSpeed 250
#define turnDelay 45
#define moveDelay 30
#define stopDelay 100

int where_go , destination_current;



void setup(){ // put your setup code here, to run once
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input
pinMode(S_S, INPUT); // declare ir sensor as input

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

Serial.begin(9600); // start serial communication at 9600bps
analogWrite(enA,155);
analogWrite(enB,155);


pinMode(switch_dept_1,INPUT);  //declare as input for department switch
pinMode(switch_dept_2,INPUT);  //declare as input for department 2 switch
pinMode(switch_s1,INPUT);  //declare as input for s1 switch
pinMode(switch_s3,INPUT);  //declare as input for s3 switch
pinMode(switch_s5,INPUT);  //declare as input for s5 switch
pinMode(switch_lab,INPUT);  //declare as input for lab switch

}


void loop(){  
  
  class_finding();
    
}
void class_finding(){
  rfid_checking();
  

    if (content == Dept_1) // one times aakkanam
    { 
    Serial.print("department 1 detected");
    destination_current = "";
    destination_current = staff_1;
    switch_sensing();
    }
    if (content == Dept_2)
    { 
    Serial.print("department 2 detected");
    destination_current = "";
    destination_current = staff_2;
    switch_sensing();
    }
    else if (content == S1)
    { 
    Serial.print("S1 detected");
    destination_current = "";
    destination_current = s1;
    switch_sensing();
    }
    else if  (content == S3)
    { 
   changeDestination(S3);
    }
    else if  (content == S5)
    { 
    changeDestination(S5);
    }
    else {
    run_motor();
    }
}

void changeDestination(String location){
  Serial.print(location + " detected");
    destination_current = "";
    destination_current = location;
    switch_sensing();
}
void run_motor(){
  if(where_go == destination_current){
    stop_motors();
    where_go = "";
  }
  else{
    read_line();
  }
}

void switch_sensing(){
  if (digitalRead(switch_dept_1)){
    where_go = staff_1;
  }
  else if (digitalRead(switch_dept_2)){
    where_go = staff_2;
  }
  else if (digitalRead(switch_s1)){
    where_go = s1;
  }
  else if (digitalRead(switch_s3)){
    where_go = s3;
  }
  else if (digitalRead(switch_s5)){
    where_go = s5;
  }
}
void rfid_checking(){
  content = "";
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
}
void turn_right_motor_reverse(){
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
}
void turn_left_motor_reverse(){
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}
void turn_right_motor_forwared(){
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, HIGH);  //Right Motor backword Pin
}
void turn_left_motor_forwared(){
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW);  //Right Motor backword Pin 
}
void read_line(){
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)&&(digitalRead(S_S) == 1)){forword();}  //if Right Sensor and Left Sensor are at White color then it will call forword function
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnLeft();}//if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnRight();} //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)&&(digitalRead(S_S) == 0)){round_turn();} 
}
void round_turn(){
  normal();
  turn_right_motor_forwared();
  turn_left_motor_reverse();
 delay(moveDelay);
   stop_motors();
}

void forword(){  //forword
  slow();
  turn_right_motor_forwared();
  turn_left_motor_forwared(); 
 delay(moveDelay);
   stop_motors();

}

void backword(){ //backword
  slow();
  turn_right_motor_reverse();
  turn_left_motor_reverse();
  delay(moveDelay);
    stop_motors();

}

void turnRight(){ //turnRight
  normal();
  turn_right_motor_forwared();
  turn_left_motor_reverse();
 delay(moveDelay);
   stop_motors();
}

void turnLeft(){ //turnLeft
  normal();
 turn_left_motor_forwared();
 turn_right_motor_reverse(); 
  delay(moveDelay);
  stop_motors();
}

void slow(){
  analogWrite(enA,slowSpeed);
analogWrite(enB,slowSpeed);
}
void normal(){
  analogWrite(enA,mediumSpeed);
analogWrite(enB,mediumSpeed);
}
void fast(){
  analogWrite(enA,fastSpeed);
analogWrite(enB,fastSpeed);
}

void stop_motors (){ //stop 
  digitalWrite(in1, LOW); //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin 
  digitalWrite(in3, LOW); //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin 
  delay(stopDelay);
}
