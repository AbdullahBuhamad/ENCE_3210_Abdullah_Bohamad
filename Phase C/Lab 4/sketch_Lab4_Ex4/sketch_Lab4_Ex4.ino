//Abdullah Bohamad
//Lab 4, Ex 4


const int gTempSensorPin = A0;   // Temperature Sensor (Analog Input)
const int gFanLEDPin = 9;        // LED to simulate Fan (Blinking)
const int gButton1Pin = 4;       // Button 1 - Fan ON/OFF
const int gButton2Pin = 5;       // Button 2 - Change Sensitivity

bool gFanState = false;          // g: Fan ON/OFF State
int gSensitivityLevel = 1;       // g: Sensitivity (1-Low, 2-Med, 3-High)
float gAverageTemp = 0;          // g: Averaged Temperature (°C)

// Button States for Debouncing
bool gLastButton1State = LOW;
bool gLastButton2State = LOW;

// Temperature Sampling Variables
unsigned long gLastSampleTime = 0;
const int gSampleInterval = 50;  // g: 50ms between samples
int gSampleCount = 0;            // g: Counter for 100 samples
long gTempSum = 0;               // g: Sum of raw temperature samples

// Blinking Control Variables
unsigned long gLastBlinkTime = 0;
int gBlinkInterval = 500;        // g: LED Blink Interval (ms)
bool gLEDState = LOW;            // g: Current LED State (HIGH/LOW)

void setup() {
  // Set pin modes
  pinMode(gFanLEDPin, OUTPUT);
  pinMode(gButton1Pin, INPUT);   // External pull-down resistors assumed
  pinMode(gButton2Pin, INPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("🔥 Fan Controller with Full Comments and g-prefixed Globals");
}

void loop() {
  handleButtons();              // Manage button presses
  readAveragedTemperature();    // Non-blocking temp sampling over 5s
  controlBlinkingFan();         // Control LED blinking based on temp
}

// ----------------------------
// Non-Blocking Temperature Sampling
// ----------------------------
void readAveragedTemperature() {
  unsigned long currentMillis = millis();

  // Sample temperature every 50ms
  if (currentMillis - gLastSampleTime >= gSampleInterval) {
    gLastSampleTime = currentMillis;

    // Read analog value from temperature sensor
    int rawValue = analogRead(gTempSensorPin);
    gTempSum += rawValue;
    gSampleCount++;

    // After 100 samples (~5s), calculate average temp
    if (gSampleCount >= 100) {
      float avgRaw = gTempSum / gSampleCount;
      float voltage = (avgRaw * 5.0) / 1023.0;  // Convert ADC to voltage
      gAverageTemp = voltage * 100.0;           // LM35: 10mV per °C

      // Output to Serial Monitor
      Serial.print("🌡️ Average Temperature: ");
      Serial.print(gAverageTemp);
      Serial.println(" °C");

      // Reset for next 5s sampling cycle
      gTempSum = 0;
      gSampleCount = 0;
    }
  }
}

// ----------------------------
// Handle Button Presses
// ----------------------------
void handleButtons() {
  bool button1State = digitalRead(gButton1Pin);
  bool button2State = digitalRead(gButton2Pin);

  // Button 1: Toggle Fan ON/OFF
  if (button1State == HIGH && gLastButton1State == LOW) {
    gFanState = !gFanState;
    Serial.print("💡 Fan State: ");
    Serial.println(gFanState ? "ON" : "OFF");
    delay(200); // Debounce
  }

  // Button 2: Cycle Sensitivity (1 -> 2 -> 3 -> 1)
  if (button2State == HIGH && gLastButton2State == LOW) {
    gSensitivityLevel++;
    if (gSensitivityLevel > 3) gSensitivityLevel = 1;
    Serial.print("🎚️ Sensitivity Level: ");
    Serial.println(gSensitivityLevel);
    delay(200); // Debounce
  }

  // Update button states
  gLastButton1State = button1State;
  gLastButton2State = button2State;
}

// ----------------------------
// Control LED Blink Speed
// ----------------------------
void controlBlinkingFan() {
  if (!gFanState) {
    digitalWrite(gFanLEDPin, LOW); // Fan is OFF → LED OFF
    return;
  }

  // Map temperature & sensitivity to blink speed
  switch (gSensitivityLevel) {
    case 1: // Low Sensitivity → Slower Blinks
      gBlinkInterval = map(gAverageTemp, 15, 45, 900, 400);
      break;
    case 2: // Medium Sensitivity
      gBlinkInterval = map(gAverageTemp, 15, 45, 700, 200);
      break;
    case 3: // High Sensitivity → Faster Blinks
      gBlinkInterval = map(gAverageTemp, 15, 45, 500, 80);
      break;
  }

  // Constrain blink speed (avoid crazy fast/slow)
  gBlinkInterval = constrain(gBlinkInterval, 80, 900);

  // Non-blocking LED Blink Logic
  unsigned long currentMillis = millis();
  if (currentMillis - gLastBlinkTime >= gBlinkInterval) {
    gLastBlinkTime = currentMillis;
    gLEDState = !gLEDState;                          // Toggle LED state
    digitalWrite(gFanLEDPin, gLEDState);             // Update LED

    // Output blink speed to Serial Monitor
    Serial.print("💡 Blink Speed (ms): ");
    Serial.println(gBlinkInterval);
  }
}