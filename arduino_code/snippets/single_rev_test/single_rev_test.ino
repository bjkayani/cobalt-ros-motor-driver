
#define LEFTENCODER_A 3
#define LEFTENCODER_B 7
#define RIGHTENCODER_A 2
#define RIGHTENCODER_B 4

#define LEFTMOTOR_A 10
#define LEFTMOTOR_B 9
#define RIGHTMOTOR_A 6
#define RIGHTMOTOR_B 5

int EncoderTicksPerRev = 16;
int MotorRevsPerWheelRev = 120;
int ticksPerWheelRev = EncoderTicksPerRev * MotorRevsPerWheelRev;

volatile long leftEncoderPos = 0;
volatile long rightEncoderPos = 0;

volatile boolean leftAset = false;
volatile boolean leftBset = false;
volatile boolean rightAset = false;
volatile boolean rightBset = false;

long lastLeftPos = 0;
long lastRightPos = 0;
long lastEncoderTime = 0;

void setup() {

  pinMode(LEFTMOTOR_A, OUTPUT);
  pinMode(LEFTMOTOR_B, OUTPUT);
  pinMode(RIGHTMOTOR_A, OUTPUT);
  pinMode(RIGHTMOTOR_B, OUTPUT);
  
  pinMode(LEFTENCODER_B,INPUT);
  pinMode(RIGHTENCODER_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFTENCODER_A), leftEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHTENCODER_A), rightEncoder, CHANGE);

  Serial.begin(115200);

}

void loop() {
  Serial.println(leftEncoderPos);
  
  if(leftEncoderPos <= ticksPerWheelRev){
    analogWrite(LEFTMOTOR_A, 40);
    digitalWrite(LEFTMOTOR_B, LOW);
  }
  else if (leftEncoderPos > ticksPerWheelRev){
    analogWrite(LEFTMOTOR_A, 0);
    digitalWrite(LEFTMOTOR_B, LOW);
  }

}

void leftEncoder(){
  //checking values of both inputs
  leftAset = digitalRead(LEFTENCODER_A)== HIGH;
  leftBset = digitalRead(LEFTENCODER_B)== HIGH;
  
  //incremending or decrementing based on leading or lagging
  leftEncoderPos += (leftAset != leftBset) ? -1 : +1;
}

void rightEncoder(){
  //checking values of both inputs
  rightAset = digitalRead(RIGHTENCODER_A)== HIGH;
  rightBset = digitalRead(RIGHTENCODER_B)== LOW;

  //incremending or decrementing based on leading or lagging
  rightEncoderPos += (rightAset != rightBset) ? -1 : +1;
}
