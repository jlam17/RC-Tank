#include <PS2X_lib.h>

PS2X ps2x;

int pinOne = 2;// right motor
int pinTwo = 3;// right motor (pwm)
int pinThree = 8;// left motor motor
int pinFour = 9;// left motor (pwm)

int error = 0; 
byte type = 0;
byte vibrate = 0;

//switch red and black pins
void setup() {
  Serial.begin(57600);
  pinMode(pinOne, OUTPUT);
  pinMode(pinTwo, OUTPUT);
  pinMode(pinThree, OUTPUT);
  pinMode(pinFour, OUTPUT);

  error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
}

void loop() {


if(error == 1) {//skip loop if no controller found
  return; 
}
 if(type == 2){ //Guitar Hero Controller
 }
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
     
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
       moveForward();
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
        Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
        moveRight();
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
        Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
        moveLeft();
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
        moveBackward();
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState() && ps2x.Button(PSB_GREEN))               //will be TRUE if any button changes state (on to off, or off to on)
    {
         Serial.println("Triangle pressed");
         stop();
    }   
 }
 
 
 delay(50);
     
}

void moveBackward() {
  digitalWrite(pinOne, LOW);
  digitalWrite(pinTwo, HIGH);
  digitalWrite(pinThree, LOW);
  digitalWrite(pinFour,HIGH);
}

void moveForward() {
  digitalWrite(pinOne, HIGH);
  digitalWrite(pinTwo, LOW);
  digitalWrite(pinThree, HIGH);
  digitalWrite(pinFour, LOW);  
}

void moveRight() {
  digitalWrite(pinOne, HIGH);
  digitalWrite(pinTwo, LOW);
  digitalWrite(pinThree, LOW);
  digitalWrite(pinFour, LOW);
}

void moveLeft() {
  digitalWrite(pinOne, LOW);
   digitalWrite(pinTwo, LOW);
  digitalWrite(pinThree, HIGH);
  digitalWrite(pinFour, LOW);
}

void stop() {
  digitalWrite(pinOne, LOW);
  digitalWrite(pinTwo, LOW);
  digitalWrite(pinThree, LOW);
  digitalWrite(pinFour, LOW);
  }
