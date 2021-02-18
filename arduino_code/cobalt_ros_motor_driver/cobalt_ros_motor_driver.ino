#include <PID_v1.h>
#include <ServoTimer2.h> 
#include <Adafruit_NeoPixel.h>

//====================Camera Servo====================

ServoTimer2 cameraServo; 
#define CAMERA_SERVO 11
int cameraServoPosition;
int cameraServoRest = 120;

//====================Battery Voltage====================

float batteryVoltage;
float batteryConstant = 2.0;
float minBatteryVoltage = 6.0;
bool lowBattery = false;
#define BATTSENS 0

//====================Debug====================

bool debug = true;

//====================Pin Definitions====================

#define LEFTMOTOR_A 10
#define LEFTMOTOR_B 9
#define RIGHTMOTOR_A 6
#define RIGHTMOTOR_B 5

#define LEFTENCODER_A 3
#define LEFTENCODER_B 7
#define RIGHTENCODER_A 2
#define RIGHTENCODER_B 4

//====================Inverse Kinematics====================

float WheelSpacing = 0.125; //wheel spacing in meters
float WheelDiameter = 0.0795; //wheel diameter in meters
float wheelCircMult = 0.81;
float WheelCirumference = WheelDiameter * 3.1416 * wheelCircMult; //wheel circumference

//====================Encoder====================

int EncoderTicksPerRev = 16;
int MotorRevsPerWheelRev = 120;

volatile long leftEncoderPos = 0;
volatile long rightEncoderPos = 0;

volatile boolean leftAset = false;
volatile boolean leftBset = false;
volatile boolean rightAset = false;
volatile boolean rightBset = false;

long lastLeftPos = 0;
long lastRightPos = 0;
long lastEncoderTime = 0;

float leftDist = 0.0;
float rightDist = 0.0;

//====================Global Velocity====================

//desired motor speed in m/s
double desLeftMotorSpeed;
double desRightMotorSpeed;

//commanded motor speed in m/s
double cmdLeftMotorSpeed;
double cmdRightMotorSpeed;

//robot velocity from ROS
double autoLinearVelocity; //in m/s
double autoAngularVelocity; //in rad/s

double mesLinearVelocity; //in m/s
double mesAngularVelocity; //in rad/s

//motor directions (1 - forward) (0 - reverse)
int leftMotorDirection; 
int rightMotorDirection;

//motor pwm speed values
float pwmLeftMotorSpeed;
float pwmRightMotorSpeed;

//measured motor speeds
double obsLeftMotorSpeed;
double obsRightMotorSpeed;

//maximum motor speed
float maxMotorSpeed = 0.5;
float maxLinearVelocity = 0.5;
float maxAngularVelocity = 3.0;

float x = 0.0;
float y = 0.0;
float theta = 0.0;

//====================Loop Timing====================

long LastDebug = 0;
long ControlLoopLastTime = 0;
long MotorCommandLastSent = 0;
long LedRefreshLastTime = 0;

#define DEBUGOUTPUTRATE 100
#define CONTROLLOOPRATE 20
#define MOTORCOMMANDLOOPRATE 10
#define LEDREFRESHRATE 5000

//====================PID Stuff====================

float Kp = 3.0; //proportional
float Ki = 0.0; //integral
float Kd = 0.0; //derivative 

PID left_PID(&obsLeftMotorSpeed, &cmdLeftMotorSpeed, &desLeftMotorSpeed, Kp, Ki, Kd, DIRECT);
PID right_PID(&obsRightMotorSpeed, &cmdRightMotorSpeed, &desRightMotorSpeed, Kp, Ki, Kd, DIRECT);

//====================Serial Message====================

String message;
String cmd;
float value;

long odom_time = 0;
int odom_seq = 0;

//====================Neopixel Strip====================

#define LED_PIN    12
#define LED_COUNT 13
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
