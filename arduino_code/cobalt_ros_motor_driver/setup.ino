void setup() {
  
  //====================Pin Initializations====================

  //Motor driver
  pinMode(LEFTMOTOR_A, OUTPUT);
  pinMode(LEFTMOTOR_B, OUTPUT);
  pinMode(RIGHTMOTOR_A, OUTPUT);
  pinMode(RIGHTMOTOR_B, OUTPUT);

  //Encoders
  pinMode(LEFTENCODER_B,INPUT);
  pinMode(RIGHTENCODER_B,INPUT);

  //====================Interrupts====================
  
  attachInterrupt(digitalPinToInterrupt(LEFTENCODER_A), leftEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHTENCODER_A), rightEncoder, CHANGE);

  //====================PID Initialization====================

  //PID mode set
  left_PID.SetMode(AUTOMATIC);
  right_PID.SetMode(AUTOMATIC);

  //PID update rate in ms
  left_PID.SetSampleTime(10);
  right_PID.SetSampleTime(10);

  //PID limits
  left_PID.SetOutputLimits(-maxMotorSpeed, maxMotorSpeed);
  right_PID.SetOutputLimits(-maxMotorSpeed, maxMotorSpeed);

  //====================Serial Setup====================  
  
  Serial.begin(115200);
  Serial.setTimeout(10);

  //====================Camera Servo Initialization==================== 
  
  cameraServo.attach(CAMERA_SERVO); 
  cameraServoSet(cameraServoRest);

  //====================Neopixel Initialization==================== 

  strip.begin();   
  strip.show();         
  strip.setBrightness(50);
  colorWipe(strip.Color(255, 255, 255));
}
