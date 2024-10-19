// Front left motor
#define FLMotorPin1 16
#define FLMotorPin2 17
#define FLMotorEn 22

// Front right motor
#define FRMotorPin1 18
#define FRMotorPin2 19
#define FRMotorEn 23

// Back left motor 
#define BLMotorPin1 12
#define BLMotorPin2 14
#define BLMotorEn 13

// Back right motor
#define BRMotorPin1 27
#define BRMotorPin2 26
#define BRMotorEn 25

// Button
#define buttonPin 1

// MPU control/status vars
MPU6050 mpu;
bool dmpReady = false;  
uint8_t devStatus;      
uint8_t fifoBuffer[64]; 
VectorFloat gravity;    
float ypr[3];           

// These have to be defined properly through testing 
#define speed 200
// in ms of how long it takes to get to the center of the square 
#define time 100
// this array will be edited at comp 
String movement[4] = {"right", "up", "down", "left"}

void setupMPU()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  // setup buttons 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) 
  {
      // Calibration Time: generate offsets and calibrate our MPU6050
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.setDMPEnabled(true);
      dmpReady = true;
  } 
}

void left() {
  // Move motor BR backward 
  digitalWrite(BRMotorPin1, HIGH);
  digitalWrite(BRMotorPin2, LOW);
  analogWrite(BRMotorEn, 200);

  // Move motor FL forward
  digitalWrite(FLMotorPin1, LOW);
  digitalWrite(FLMotorPin2, HIGH);
  analogWrite(FLMotorEn, 200);

  // Move motor FR forward (reversed)
  digitalWrite(FRMotorPin1, LOW);
  digitalWrite(FRMotorPin2, HIGH);
  analogWrite(FRMotorEn, 200);

  // Move motor BL backward 
  digitalWrite(BLMotorPin1, LOW);
  digitalWrite(BLMotorPin2, HIGH);
  analogWrite(BLMotorEn, 200);

  Serial.println("Moving Left");
  delay(time);
}

void right() {
  // Move motor FL forward
  digitalWrite(FLMotorPin1, HIGH);
  digitalWrite(FLMotorPin2, LOW);
  analogWrite(FLMotorEn, 200);

  // Move motor FR backward (reversed)
  digitalWrite(FRMotorPin1, HIGH);
  digitalWrite(FRMotorPin2, LOW);
  analogWrite(FRMotorEn, 200);

  // Move motor BL forward 
  digitalWrite(BLMotorPin1, HIGH);
  digitalWrite(BLMotorPin2, LOW);
  analogWrite(BLMotorEn, 200);

  // Move motor BR backward 
  digitalWrite(BRMotorPin1, LOW);
  digitalWrite(BRMotorPin2, HIGH);
  analogWrite(BRMotorEn, 200);

  Serial.println("Moving Right");
  delay(time);
}

void up() {

  // Move motor FL forward
  digitalWrite(FLMotorPin1, HIGH);
  digitalWrite(FLMotorPin2, LOW);
  analogWrite(FLMotorEn, 200);

  // Move motor FR forward (reversed)
  digitalWrite(FRMotorPin1, LOW);
  digitalWrite(FRMotorPin2, HIGH);
  analogWrite(FRMotorEn, 200);

  // Move motor BL forward 
  digitalWrite(BLMotorPin1, HIGH);
  digitalWrite(BLMotorPin2, LOW);
  analogWrite(BLMotorEn, 200);

  // Move motor BR forward 
  digitalWrite(BRMotorPin1, HIGH);
  digitalWrite(BRMotorPin2, LOW);
  analogWrite(BRMotorEn, 200);

  Serial.println("Moving Up");
  delay(time);
} 

void down() {
  // Move motor FL backward
  digitalWrite(FLMotorPin1, LOW);
  digitalWrite(FLMotorPin2, HIGH);
  analogWrite(FLMotorEn, 200);

  // Move motor FR backward (reversed)
  digitalWrite(FRMotorPin1, HIGH);
  digitalWrite(FRMotorPin2, LOW);
  analogWrite(FRMotorEn, 200);

  // Move motor BL backward 
  digitalWrite(BLMotorPin1, LOW);
  digitalWrite(BLMotorPin2, HIGH);
  analogWrite(BLMotorEn, 200);

  // Move motor BR backward 
  digitalWrite(BRMotorPin1, LOW);
  digitalWrite(BRMotorPin2, HIGH);
  analogWrite(BRMotorEn, 200);

  Serial.println("Moving Down");
  delay(time);
}

void handleMovement(String movement[]) {
  for (int i = 0; i < 4; i++) {
    if (movement[i] == "left") {
      left();
    } else if (movement[i] == "right") {
      right();
    } else if (movement[i] == "up") {
      up();
    } else if (movement[i] == "down") {
      down();
    }
  }
}


void setup() {

  Serial.begin(115200);

  // Init button
  pinMode(buttonPin, INPUT_PullUP);

  // set up MPU
  setupMPU();

  attachInterrupt(buttonPin, [] { handleMovement(movement); }, FALLING);
}

void loop() {
  // do nothing 
}

