#include <Wire.h>
#include <ZX_Sensor.h>
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

Servo servo_ONE;  //Standard

int pos_ONE = 1;    // variable to store the servo position
Servo servo_TWO ; //Continuous
int pos_TWO = 1 ;

int pos = 0 ;
int pos2 = 0 ;
bool holder_ONE = true ;
bool holder_TWO = true ;

// Constants
const int ZX_ADDR_ONE = 0x11;    // ZX Sensor I2C address
const int INTERRUPT_NUM_ONE = 1; // Pin 3 on the UNO
const int ZX_ADDR_TWO = 0x10;    // ZX Sensor I2C address
const int INTERRUPT_NUM_TWO = 0 ; //Pin 2 on the UNO
//pin 2 on the uno is 0
//pin 3 is 1
//pin 4 is 2
//pin 5 is 3
//pin 6 is 4
//pin 7 is 5

// Global Variables
ZX_Sensor zx_sensor_ONE = ZX_Sensor(ZX_ADDR_ONE);
ZX_Sensor zx_sensor_TWO = ZX_Sensor(ZX_ADDR_TWO);
volatile GestureType gesture;
volatile bool interrupt_flag;
uint8_t gesture_speed;
volatile GestureType gesture_TWO;
volatile bool interrupt_flag_TWO;
uint8_t gesture_speed_TWO;

unsigned long lastRotateTime_ONE = 0 ;
unsigned long lastRotateTime_TWO = 0 ;
int rotateWait_ONE = 15 ;
int rotateWait_TWO = 1000 ;
const float pi = 3.14 ;
float someNum = 0 ;
float numHolder = 0 ;

bool powerS1 = false ;
bool powerS2 = false ;
int stage = 1 ;

void setup() {

  lcd.begin(16, 2);
  lcd.print("Hello!");

  servo_ONE.attach(9) ;
  servo_TWO.attach(10) ;
  servo_ONE.write(0) ;
//  servo_TWO.write(0) ;

  uint8_t ver_ONE;
  uint8_t ver_TWO;

  // Initialize gesture to no gesture
  gesture = NO_GESTURE;
  gesture_TWO = NO_GESTURE;

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println("---------------------------------------------");
  Serial.println("SparkFun/GestureSense - I2C Gesture Interrupt");
  Serial.println("Note: higher 'speed' numbers mean slower");
  Serial.println("---------------------------------------------");

  // Initialize ZX Sensor (configure I2C and read model ID)
  if ( zx_sensor_ONE.init(GESTURE_INTERRUPTS) ) {
    Serial.println("ZX Sensor ONE initialization complete");
  } else {
    Serial.println("Something went wrong during ZX Sensor ONE init!");
  }
  if ( zx_sensor_TWO.init(GESTURE_INTERRUPTS) ) {
    Serial.println("ZX Sensor TWO initialization complete");
  } else {
    Serial.println("Something went wrong during ZX Sensor TWO init!");
  }

  // Read the model version number and ensure the library will work
  ver_ONE = zx_sensor_ONE.getModelVersion();
  ver_TWO = zx_sensor_TWO.getModelVersion();
  if ( ver_ONE == ZX_ERROR ) {
    Serial.println("Error reading model version number");
  } else {
    Serial.print("Model version: ");
    Serial.println(ver_ONE);
  }
  if ( ver_ONE != ZX_MODEL_VER ) {
    Serial.print("Model version needs to be ");
    Serial.print(ZX_MODEL_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }
  if ( ver_TWO == ZX_ERROR ) {
    Serial.println("Error reading model version number");
  } else {
    Serial.print("Model version: ");
    Serial.println(ver_TWO);
  }
  if ( ver_TWO != ZX_MODEL_VER ) {
    Serial.print("Model version needs to be ");
    Serial.print(ZX_MODEL_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }

  // Read the register map version and ensure the library will work
  ver_ONE = zx_sensor_ONE.getRegMapVersion();
  ver_TWO = zx_sensor_TWO.getRegMapVersion();
  if ( ver_ONE == ZX_ERROR ) {
    Serial.println("Error reading register map version number");
  } else {
    Serial.print("Register Map Version: ");
    Serial.println(ver_ONE);
  }
  if ( ver_ONE != ZX_REG_MAP_VER ) {
    Serial.print("Register map version needs to be ");
    Serial.print(ZX_REG_MAP_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }
  if ( ver_TWO == ZX_ERROR ) {
    Serial.println("Error reading register map version number");
  } else {
    Serial.print("Register Map Version: ");
    Serial.println(ver_TWO);
  }
  if ( ver_TWO != ZX_REG_MAP_VER ) {
    Serial.print("Register map version needs to be ");
    Serial.print(ZX_REG_MAP_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }

  // Initialize interrupt service routine
  interrupt_flag = false;
  interrupt_flag_TWO = false;
  zx_sensor_ONE.clearInterrupt();
  zx_sensor_TWO.clearInterrupt();
  attachInterrupt(INTERRUPT_NUM_ONE, interruptRoutine, RISING);
  attachInterrupt(INTERRUPT_NUM_TWO, interruptRoutine, RISING);
  Serial.println("Interrupts now configured. Gesture away!");
}

void loop() {

  //Gesture sensor ONE
  // If we have an interrupt, read and print the gesture
  if ( interrupt_flag ) {

    // Clear the interrupt flag
    interrupt_flag = false;

    // You MUST read the STATUS register to clear interrupt!
    zx_sensor_ONE.clearInterrupt();

    // Read last gesture
    gesture = zx_sensor_ONE.readGesture();
    gesture_speed = zx_sensor_ONE.readGestureSpeed();
    switch ( gesture ) {
      case NO_GESTURE:
        Serial.println("No Gesture ONE");
        break;
      case RIGHT_SWIPE:
        Serial.print("Right Swipe ONE. Speed: ");
        Serial.println(gesture_speed, DEC);
        pos_ONE++ ;
        lcd.clear() ;
        lcd.print("S1 Speed") ;
        lcd.setCursor(0,1) ;
        lcd.print(pos_ONE) ;
        Serial.print("POS_ONE is ") ;
        Serial.println(pos_ONE) ;
        break;
      case LEFT_SWIPE:
        Serial.print("3Left Swipe ONE. Speed: ");
        Serial.println(gesture_speed, DEC);
        pos_ONE-- ;
        lcd.clear() ;
        lcd.print("S1 Speed") ;
        lcd.setCursor(0,1) ;
        lcd.print(pos_ONE) ;
        Serial.print("POS_ONE is ") ;
        Serial.println(pos_ONE) ;
        break;
      case UP_SWIPE:
        Serial.print("Up Swipe ONE. Speed: ");
        Serial.println(gesture_speed, DEC);
        powerS1 = !powerS1 ;
        if(powerS1 == true) {
          lcd.clear() ;
          lcd.print("S1 ON") ;
        } else if (powerS1 == false) {
          lcd.clear() ;
          lcd.print("S1 OFF") ;
        }
        break;
      default:
        break;
    }
  }

  //Gesture sensor TWO
  if ( interrupt_flag_TWO ) {

    // Clear the interrupt flag
    interrupt_flag_TWO = false;

    // You MUST read the STATUS register to clear interrupt!
    zx_sensor_TWO.clearInterrupt();

    // Read last gesture
    gesture_TWO = zx_sensor_TWO.readGesture();
    gesture_speed_TWO = zx_sensor_TWO.readGestureSpeed();
    switch ( gesture_TWO ) {
      case NO_GESTURE:
        Serial.println("No Gesture TWO");
        break;
      case RIGHT_SWIPE:
        Serial.print("Right Swipe TWO. Speed: ");
        Serial.println(gesture_speed_TWO, DEC);
        stage++ ;
        lcd.clear() ;
        if(stage > 3) {
          stage = 1 ;
        }
        
        if(stage == 1) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("sin(t)") ;
        } else if(stage == 2) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("2") ;
        } else if(stage == 3) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("3") ;
        }
        break;
      case LEFT_SWIPE:
        Serial.print("Left Swipe TWO. Speed: ");
        Serial.println(gesture_speed_TWO, DEC);
        stage-- ;
        lcd.clear() ;
        if(stage < 1) {
          stage = 3 ;
        }
        
        if(stage == 1) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("sin(t)") ;
        } else if(stage == 2) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("2") ;
        } else if(stage == 3) {
          lcd.print("S2 Movement") ;
          lcd.setCursor(0,1) ;
          lcd.print("3") ;
        }
        break;
      case UP_SWIPE:
        Serial.print("Up Swipe TWO. Speed: ");
        Serial.println(gesture_speed_TWO, DEC);
        powerS2 = !powerS2 ;
        if(powerS2 == true) {
          lcd.clear() ;
          lcd.print("S2 ON") ;
        } else if(powerS2 == false) {
          lcd.clear() ;
          lcd.print("S2 OFF") ;
        }
        break;
      default:
        break;
    }
  }

  
  if(powerS1 == true) {
    if(holder_ONE == true && pos <= 180 && millis() - lastRotateTime_ONE > rotateWait_ONE) {
      servo_ONE.write(pos) ;
      pos = pos + pos_ONE ;
      lastRotateTime_ONE = millis() ;
    } else if (holder_ONE == false && pos >= 0 && millis() - lastRotateTime_ONE > rotateWait_ONE) {
      servo_ONE.write(pos) ;
      pos = pos - pos_ONE ;
      lastRotateTime_ONE = millis() ;
    }
  }

  if(powerS2 == true) {
    if(stage == 1) {
      if(millis() - lastRotateTime_TWO > rotateWait_TWO) { 
        someNum = sin(millis()) ;
        someNum = (someNum * 90 + 90) ;
        servo_TWO.write(someNum) ;
        lastRotateTime_TWO = millis() ;
      }
    } else if(stage == 2) {
       if(millis() - lastRotateTime_TWO > rotateWait_TWO) { 
        someNum = sin(millis()) ;
        someNum = (someNum * 90 + 90) ;
        servo_TWO.write(someNum) ;
        lastRotateTime_TWO = millis() ;
      }
    } else if(stage == 3) {
       if(millis() - lastRotateTime_TWO > rotateWait_TWO) { 
        someNum = sin(millis()) ;
        someNum = (someNum * 90 + 90) ;
        servo_TWO.write(someNum) ;
        lastRotateTime_TWO = millis() ;
      }
    }
  } else {
    servo_TWO.write(90) ;
  }


  if(pos > 180) {
      holder_ONE = false ;
      holder_TWO = false ;
  }
  if(pos < 0) {
      holder_ONE = true ;
      holder_TWO = true ;
  }

}

void interruptRoutine() {
  interrupt_flag = true;
  interrupt_flag_TWO = true;
}
