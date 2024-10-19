// Define motor pinss
#define BLMotorPin1 22
#define BLMotorPin2 23
#define BRMotorPin1 16
#define BRMotorPin2 17

#define buttonPin 1

// this has to be defined through calculations at comp (ms)
#define time 100

void handleMovement() {
  move();
  stop();
}

void move() {
  digitalWrite(BLMotorPin1, HIGH);
  digitalWrite(BLMotorPin2, LOW);
  digitalWrite(BRMotorPin1, HIGH);
  digitalWrite(BRMotorPin2, LOW);

  delay(time);
}

void stop() {
  digitalWrite(BLMotorPin1, LOW);
  digitalWrite(BLMotorPin2, LOW);
  digitalWrite(BRMotorPin1, LOW);
  digitalWrite(BRMotorPin2, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(BLMotorPin1, OUTPUT);
  pinMode(BLMotorPin2, OUTPUT);
  pinMode(BRMotorPin1, OUTPUT);
  pinMode(BRMotorPin2, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(buttonPin, handleMovement, FALLING);
}

void loop() {
  // do nothing
}