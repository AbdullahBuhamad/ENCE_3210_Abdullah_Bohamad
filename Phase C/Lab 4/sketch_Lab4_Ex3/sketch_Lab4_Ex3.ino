//Abdullah Bohamad
//Lab 4, Ex3

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// Initialize OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global Variables
const int gSolarPin = A0;      // Solar panel voltage sense
const int gBatteryPin = A1;    // Battery voltage sense

// Voltage thresholds
const float gSolarThreshold = 2.5;     // Min voltage to use solar power
const float gBatteryFull = 4.2;        // Battery full charge voltage (Improved)
const float gBatteryLow = 3.0;         // Battery low voltage cutoff

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); // Error message if OLED fails
    for (;;); // Halt if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  pinMode(gSolarPin, INPUT);
  pinMode(gBatteryPin, INPUT);
}

void loop() {
  // Read analog voltages from solar panel and battery
  int gSolarADC = analogRead(gSolarPin);
  int gBatteryADC = analogRead(gBatteryPin);

  // Convert ADC readings to voltages (assuming 5V reference)
  float gSolarVoltage = (gSolarADC * 5.0) / 1023.0;
  float gBatteryVoltage = (gBatteryADC * 5.0) / 1023.0;

  // Debugging in Serial Monitor
  Serial.print("Solar Voltage: ");
  Serial.println(gSolarVoltage);
  Serial.print("Battery Voltage: ");
  Serial.println(gBatteryVoltage);

  // Clear OLED before updating
  display.clearDisplay();

  // Display Solar and Battery voltages
  display.setCursor(0, 0);
  display.print("Solar: ");
  display.print(gSolarVoltage, 2);
  display.print("V");

  display.setCursor(0, 10);
  display.print("Battery: ");
  display.print(gBatteryVoltage, 2);
  display.print("V");

  // ---------- Improved Section Starts Here ----------

  // Check if solar voltage is sufficient
  display.setCursor(0, 20);
  if (gSolarVoltage > gSolarThreshold) {
    
    // Improved Logic: Prioritize charging the battery before using solar power
    if (gBatteryVoltage < gBatteryFull) {
      // Battery is not fully charged, prioritize charging
      display.print("Power: Battery");  // Microcontroller runs on battery
      display.setCursor(80, 20);
      display.print("Charging");        // Indicate charging is in progress
    } else {
      // Battery is fully charged, now solar can power the microcontroller
      display.print("Power: Solar");
      display.setCursor(80, 20);
      display.print("Idle");            // Battery charging is idle
    }
  } else {
    // Solar panel voltage too low, rely on battery
    display.print("Power: Battery");
    display.setCursor(80, 20);
    display.print("Idle");
  }

  // ---------- Improved Section Ends Here ----------

  // Push updates to OLED display
  display.display();

  delay(500); // Refresh every 0.5 sec
}