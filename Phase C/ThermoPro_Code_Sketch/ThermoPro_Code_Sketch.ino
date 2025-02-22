#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "images.h"  // Contains full-screen images:  

//
// OLED Display Configuration
//
#define SCREEN_WIDTH 128         // OLED display width, in pixels
#define SCREEN_HEIGHT 32         // OLED display height, in pixels
#define OLED_RESET    -1         // Reset pin (-1 if sharing Arduino reset)
#define SCREEN_ADDRESS 0x3C      // I2C address for the OLED

// Create OLED display object (without g prefix)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//
// Button and LED Pin Definitions
//
#define ONOFF_BUTTON 2           // System ON/OFF button (digital pin 2)
#define UNITS_BUTTON 4           // Temperature unit toggle button (digital pin 4)
#define LOCK_BUTTON 3            // Lock button (digital pin 3)
#define CAL_BUTTON 5             // Calibration button (digital pin 5)
#define LIGHT_BUTTON 6           // LED toggle button (digital pin 6)
#define LED_PIN 9                // LED connected to digital pin 9

//
// Temperature Sensor Configuration
//
#define TEMP_SENSOR 8            // DS18B20 sensor data pin (digital pin 8)
OneWire gOneWire(TEMP_SENSOR);      
DallasTemperature gSensors(&gOneWire); // Global temperature sensor object

//
// Potentiometer Pin for Temperature Offset
//
#define POT_PIN A0               // Analog pin A0 for the potentiometer

//
// Global State Variables (prefixed with "g")
//
bool gSystemOn = false;          // Global system power state (off by default)
bool gIsLocked = false;          // Global lock state: disables unit change and offset adjustments if true
bool gIsCelsius = true;          // Global temperature unit (true = Celsius, false = Fahrenheit)
bool gLightOn = false;           // Global LED state (off by default)

//
// Setup Function: Initializes Serial, pins, sensor, and OLED
//
void setup() {
  Serial.begin(9600);            // Initialize Serial Monitor for debugging
  
  // Set pin modes for buttons and LED
  pinMode(ONOFF_BUTTON, INPUT);
  pinMode(UNITS_BUTTON, INPUT);
  pinMode(LOCK_BUTTON, INPUT);
  pinMode(CAL_BUTTON, INPUT);
  pinMode(LIGHT_BUTTON, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize the temperature sensor
  gSensors.begin();
  
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED initialization failed"));
    for (;;);                   // Halt if OLED fails to initialize
  }
  
  display.setRotation(2);       // Set display rotation if needed (flip the screen)
  display.clearDisplay();       // Clear the display buffer
  display.display();            // Push the cleared buffer to the display
}

//
// Loop Function: Reads inputs, computes the temperature with offset, and updates display
//
void loop() {
  // ------------------------------
  // 1) Handle Button Inputs
  // ------------------------------
  
  // Toggle system power with ON/OFF button
  if (digitalRead(ONOFF_BUTTON) == HIGH) {
    gSystemOn = !gSystemOn;
    delay(200);                // Debounce delay
  }
  
  // If system is OFF, clear display, turn LED off, and exit
  if (!gSystemOn) {
    display.clearDisplay();
    display.display();
    digitalWrite(LED_PIN, LOW);
    return;
  }
  
  // Toggle lock state with LOCK button (when locked, unit and offset changes are disabled)
  if (digitalRead(LOCK_BUTTON) == HIGH) {
    gIsLocked = !gIsLocked;
    delay(200);
  }
  
  // Toggle temperature unit (Celsius/Fahrenheit) with UNITS button, if not locked
  if (digitalRead(UNITS_BUTTON) == HIGH && !gIsLocked) {
    gIsCelsius = !gIsCelsius;
    delay(200);
  }
  
  // Toggle LED state with LIGHT button
  if (digitalRead(LIGHT_BUTTON) == HIGH) {
    gLightOn = !gLightOn;
    digitalWrite(LED_PIN, gLightOn ? HIGH : LOW);
    delay(200);
  }
  
  // When CAL button is pressed, print "CALIBRATION!" to Serial Monitor
  if (digitalRead(CAL_BUTTON) == HIGH) {
    Serial.println("CALIBRATION!");
    delay(200);
  }
  
  // ------------------------------
  // 2) Read Temperature and Potentiometer Offset
  // ------------------------------
  
  // Request temperature measurement from the sensor
  gSensors.requestTemperatures();
  float tempC = gSensors.getTempCByIndex(0);              // Read temperature in Celsius
  float tempF = DallasTemperature::toFahrenheit(tempC);     // Convert to Fahrenheit
  float tempToShow = gIsCelsius ? tempC : tempF;            // Choose the correct unit
  
  // Read potentiometer value for temperature offset, only if not locked
  float offset = 0;
  if (!gIsLocked) {
    int potVal = analogRead(POT_PIN);
    // Map the potentiometer reading (0-1023) to an offset range (-5.0 to +5.0 degrees)
    offset = map(potVal, 0, 1023, -50, 50) / 10.0;
  }
  float tempAdjusted = tempToShow + offset;                // Adjust temperature by offset
  
  // Debug output: Print the offset value to the Serial Monitor
  Serial.print("Pot Offset: ");
  Serial.println(offset);
  
  // ------------------------------
  // 3) Update OLED Display
  // ------------------------------
  
  display.clearDisplay();  // Clear the display buffer
  
  // Draw full-screen background based on lock state:
  // If locked, show the lock background; if unlocked, show the unlock background.
  if (gIsLocked) {
    display.drawBitmap(0, 0, images[0], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  } else {
    display.drawBitmap(0, 0, images[1], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  }
  
  // Display the temperature value on the left (using normal font size)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 10);
  display.print(tempAdjusted, 1);  // For example, "23.4"
  
  // Append temperature unit as fallback text immediately after the temperature value.
  display.print(gIsCelsius ? " C" : " F");
  
  // Push the updated content to the OLED display
  display.display();
  
  delay(100);  // Short delay before the next loop iteration
}