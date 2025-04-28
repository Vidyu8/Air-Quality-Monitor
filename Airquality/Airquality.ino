const int MQ135_PIN = A0;   
const int LED_PIN = 9;       
const int IR_SENSOR_1 = 7; 
const int IR_SENSOR_2 = 8;  

// Air quality thresholds
const int GOOD_AIR_THRESHOLD = 38;
const int MODERATE_AIR_THRESHOLD = 60;

// Alert timing
const unsigned long SAMPLE_INTERVAL = 1000; // Main loop delay (ms)
const unsigned long FIRE_BLINK_INTERVAL = 100; // LED blink speed for fire (ms)
const unsigned long MODERATE_BLINK_INTERVAL = 500; // LED blink speed for moderate (ms)

// System states
enum SystemState {
  STATE_NONE,
  STATE_GOOD,
  STATE_MODERATE,
  STATE_POOR,
  STATE_FIRE
};

SystemState lastState = STATE_NONE;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println(F("\nAir Quality & Fire Detection System Initialized\n"));
  
  // Configure pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  
  // Initial LED test
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read sensor values
  int airQualityValue = analogRead(MQ135_PIN);
  bool isFireDetected = (digitalRead(IR_SENSOR_1) == LOW || digitalRead(IR_SENSOR_2) == LOW);
  
  // Handle fire detection (highest priority)
  if (isFireDetected) {
    handleFireDetection();
    return; // Skip air quality check during fire
  }
  
  // Evaluate air quality
  evaluateAirQuality(airQualityValue);
  
  // Normal operation delay
  delay(SAMPLE_INTERVAL);
}

void handleFireDetection() {
  if (lastState != STATE_FIRE) {
    Serial.println(F("\n🔥🔥🔥 FIRE DETECTED! 🔥🔥🔥"));
    Serial.println(F("EVACUATE AREA IMMEDIATELY!\n"));
    lastState = STATE_FIRE;
  }
  
  // Rapid blinking LED alert
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(FIRE_BLINK_INTERVAL);
    digitalWrite(LED_PIN, LOW);
    delay(FIRE_BLINK_INTERVAL);
  }
}

void evaluateAirQuality(int airValue) {
  Serial.print(F("Air Quality Reading: "));
  Serial.println(airValue);
  
  // Determine air quality state
  if (airValue <= GOOD_AIR_THRESHOLD) {
    if (lastState != STATE_GOOD) {
      Serial.println(F("Air Quality: GOOD 🌿"));
      Serial.println(F("No health risks detected.\n"));
      digitalWrite(LED_PIN, LOW);
      lastState = STATE_GOOD;
    }
  } 
  else if (airValue <= MODERATE_AIR_THRESHOLD) {
    if (lastState != STATE_MODERATE) {
      Serial.println(F("Air Quality: MODERATE 🌫️"));
      Serial.println(F("Sensitive individuals should take precautions.\n"));
      lastState = STATE_MODERATE;
    }
    // Pulsing LED for moderate alert
    for (int i = 0; i < 6; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(MODERATE_BLINK_INTERVAL);
      digitalWrite(LED_PIN, LOW);
      delay(MODERATE_BLINK_INTERVAL);
    }
  } 
  else {
    if (lastState != STATE_POOR) {
      Serial.println(F("Air Quality: POOR ☠️"));
      Serial.println(F("Health alert! Avoid outdoor activity.\n"));
      digitalWrite(LED_PIN, HIGH);
      lastState = STATE_POOR;
    }
  }
}