//Abdullah Bohamad
//Lab 4, Ex2

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// OLED reset pin (not used, so set to -1)
#define OLED_RESET    -1

// I2C address for the OLED display (0x3C for 128x32 displays)
#define SCREEN_ADDRESS 0x3C

// Initialize the OLED display using Adafruit's SSD1306 library
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global variables for analog input pins
const int gSolarPin = A0;      // Analog pin to read solar panel voltage
const int gBatteryPin = A1;    // Analog pin to read battery voltage

void setup() {
  Serial.begin(9600); // Start serial communication for debugging

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); // Error message if OLED fails
    for (;;); // Halt the program if OLED fails to initialize
  }

  // Clear the OLED screen at startup
  display.clearDisplay();
  display.setTextSize(1);                // Set text size for OLED
  display.setTextColor(SSD1306_WHITE);   // Set text color to white

  // Initialize analog input pins
  pinMode(gSolarPin, INPUT);
  pinMode(gBatteryPin, INPUT);
}

void loop() {
  // Read the analog values from the solar panel and battery
  int gSolarADC = analogRead(gSolarPin);    // Read solar panel voltage
  int gBatteryADC = analogRead(gBatteryPin); // Read battery voltage

  // Convert ADC readings to voltages (assuming 5V reference)
  float gSolarVoltage = (gSolarADC * 5.0) / 1023.0;
  float gBatteryVoltage = (gBatteryADC * 5.0) / 1023.0;

  // Output voltage readings to Serial Monitor for debugging
  Serial.print("Solar Voltage: ");
  Serial.println(gSolarVoltage);
  Serial.print("Battery Voltage: ");
  Serial.println(gBatteryVoltage);

  // Clear the OLED screen before updating
  display.clearDisplay();

  // Display Solar Panel Voltage on OLED
  display.setCursor(0, 0); // Position at the top left
  display.print("Solar: ");
  display.print(gSolarVoltage, 2); // Display voltage with 2 decimal places
  display.print("V");

  // Display Battery Voltage on OLED
  display.setCursor(0, 10); // Next line
  display.print("Battery: ");
  display.print(gBatteryVoltage, 2); // Display voltage with 2 decimal places
  display.print("V");

  // Determine which power source is being used
  display.setCursor(0, 20); // Next line for power source info
  if (gSolarVoltage > 2.5) {
    display.print("Power: Solar"); // Use solar if > 2.5V
  } else {
    display.print("Power: Battery"); // Otherwise, use battery
  }

  // Determine if the battery is charging
  if (gBatteryVoltage < gSolarVoltage) {
    display.setCursor(80, 20); // Display charging status on right side
    display.print("Charging"); // Battery is charging
  } else {
    display.setCursor(80, 20);
    display.print("Idle");     // No charging occurring
  }

  // Push all updates to the OLED display
  display.display();

  // Small delay before next reading (updates every 0.5 seconds)
  delay(500);
}