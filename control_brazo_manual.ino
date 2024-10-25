// Define pins for Motor 1
const int PUL_PIN_1 = 1;   // Pulse Pin Motor 1
const int DIR_PIN_1 = 4;   // Direction Pin Motor 1
const int EN_PIN_1 = 7;    // Enable Pin Motor 1

// Define pins for Motor 2
const int PUL_PIN_2 = 2;   // Pulse Pin Motor 2
const int DIR_PIN_2 = 5;   // Direction Pin Motor 2
const int EN_PIN_2 = 8;    // Enable Pin Motor 2

// Define pins for Motor 3
const int PUL_PIN_3 = 3;   // Pulse Pin Motor 3
const int DIR_PIN_3 = 6;   // Direction Pin Motor 3
const int EN_PIN_3 = 9;    // Enable Pin Motor 3

// Potentiometer pins
const int POT_PIN_1 = A0;  // Potentiometer for Motor 1
const int POT_PIN_2 = A1;  // Potentiometer for Motor 2
const int POT_PIN_3 = A2;  // Potentiometer for Motor 3

// Motor parameters
const unsigned long MIN_PULSE_DELAY = 50;   // Minimum delay between pulses (microseconds)
const unsigned long MAX_PULSE_DELAY = 2000; // Maximum delay between pulses (microseconds)
const int DEAD_ZONE = 50;                  // Dead zone around center position

// Timing variables for each motor
unsigned long lastPulseTime1 = 0;
unsigned long lastPulseTime2 = 0;
unsigned long lastPulseTime3 = 0;
unsigned long pulseDelay1 = MAX_PULSE_DELAY;
unsigned long pulseDelay2 = MAX_PULSE_DELAY;
unsigned long pulseDelay3 = MAX_PULSE_DELAY;
bool pulseState1 = LOW;
bool pulseState2 = LOW;
bool pulseState3 = LOW;

void setup() {
  // Configure all pins
  pinMode(PUL_PIN_1, OUTPUT);
  pinMode(DIR_PIN_1, OUTPUT);
  pinMode(EN_PIN_1, OUTPUT);
  pinMode(PUL_PIN_2, OUTPUT);
  pinMode(DIR_PIN_2, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  pinMode(PUL_PIN_3, OUTPUT);
  pinMode(DIR_PIN_3, OUTPUT);
  pinMode(EN_PIN_3, OUTPUT);
  
  // Enable all motor drivers
  digitalWrite(EN_PIN_1, LOW);
  digitalWrite(EN_PIN_2, LOW);
  digitalWrite(EN_PIN_3, LOW);
}

void loop() {
  // Read all potentiometers
  int potValue1 = analogRead(POT_PIN_1);
  int potValue2 = analogRead(POT_PIN_2);
  int potValue3 = analogRead(POT_PIN_3);
  
  // Handle Motor 1
  if (potValue1 < 512 - DEAD_ZONE) {
    digitalWrite(DIR_PIN_1, LOW);
    pulseDelay1 = map(potValue1, 0, 512 - DEAD_ZONE, MIN_PULSE_DELAY, MAX_PULSE_DELAY);
  }
  else if (potValue1 > 512 + DEAD_ZONE) {
    digitalWrite(DIR_PIN_1, HIGH);
    pulseDelay1 = map(potValue1, 512 + DEAD_ZONE, 1023, MAX_PULSE_DELAY, MIN_PULSE_DELAY);
  }
  else {
    pulseDelay1 = 0;  // Stop motor 1
  }
  
  // Handle Motor 2
  if (potValue2 < 512 - DEAD_ZONE) {
    digitalWrite(DIR_PIN_2, LOW);
    pulseDelay2 = map(potValue2, 0, 512 - DEAD_ZONE, MIN_PULSE_DELAY, MAX_PULSE_DELAY);
  }
  else if (potValue2 > 512 + DEAD_ZONE) {
    digitalWrite(DIR_PIN_2, HIGH);
    pulseDelay2 = map(potValue2, 512 + DEAD_ZONE, 1023, MAX_PULSE_DELAY, MIN_PULSE_DELAY);
  }
  else {
    pulseDelay2 = 0;  // Stop motor 2
  }
  
  // Handle Motor 3
  if (potValue3 < 512 - DEAD_ZONE) {
    digitalWrite(DIR_PIN_3, LOW);
    pulseDelay3 = map(potValue3, 0, 512 - DEAD_ZONE, MIN_PULSE_DELAY, MAX_PULSE_DELAY);
  }
  else if (potValue3 > 512 + DEAD_ZONE) {
    digitalWrite(DIR_PIN_3, HIGH);
    pulseDelay3 = map(potValue3, 512 + DEAD_ZONE, 1023, MAX_PULSE_DELAY, MIN_PULSE_DELAY);
  }
  else {
    pulseDelay3 = 0;  // Stop motor 3
  }
  
  // Generate pulses for Motor 1
  if (pulseDelay1 > 0) {
    unsigned long currentTime = micros();
    if (currentTime - lastPulseTime1 >= pulseDelay1) {
      pulseState1 = !pulseState1;
      digitalWrite(PUL_PIN_1, pulseState1);
      lastPulseTime1 = currentTime;
    }
  }
  
  // Generate pulses for Motor 2
  if (pulseDelay2 > 0) {
    unsigned long currentTime = micros();
    if (currentTime - lastPulseTime2 >= pulseDelay2) {
      pulseState2 = !pulseState2;
      digitalWrite(PUL_PIN_2, pulseState2);
      lastPulseTime2 = currentTime;
    }
  }
  
  // Generate pulses for Motor 3
  if (pulseDelay3 > 0) {
    unsigned long currentTime = micros();
    if (currentTime - lastPulseTime3 >= pulseDelay3) {
      pulseState3 = !pulseState3;
      digitalWrite(PUL_PIN_3, pulseState3);
      lastPulseTime3 = currentTime;
    }
  }
}
