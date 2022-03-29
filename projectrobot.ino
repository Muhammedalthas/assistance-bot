

#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 

#define R_S A0 //ir sensor Right
#define L_S 11 //ir sensor Left



void setup(){ // put your setup code here, to run once

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

Serial.begin(9600); // start serial communication at 9600bps
analogWrite(enA,255);
analogWrite(enB,255);

}


void loop(){  
  
  

//===============================================================================
//                          Line Follower Control
//===============================================================================     

turnLeft();

}
void turn_right_motor_forwared(){
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
}
void turn_left_motor_forwared(){
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}
void turn_right_motor_reverse(){
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, HIGH);  //Right Motor backword Pin
}
void turn_left_motor_reverse(){
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW);  //Right Motor backword Pin 
}
void read_line(){
  if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){forword();}  //if Right Sensor and Left Sensor are at White color then it will call forword function
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnRight();}//if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnLeft();} //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){stop_motors();}     //if Right Sensor and Left Sensor are at Black color then it will call Stop function
  
}

void forword(){  //forword
  turn_right_motor_forwared();
  turn_left_motor_forwared(); 

}

void backword(){ //backword
  turn_right_motor_reverse();
  turn_left_motor_reverse();

}

void turnRight(){ //turnRight
  turn_right_motor_forwared();
  turn_left_motor_reverse();
}

void turnLeft(){ //turnLeft
 turn_left_motor_forwared();
 turn_right_motor_reverse(); 
}

void stop_motors (){ //stop 
  digitalWrite(in1, LOW); //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin 
  digitalWrite(in3, LOW); //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin 
  delay(300);
}
