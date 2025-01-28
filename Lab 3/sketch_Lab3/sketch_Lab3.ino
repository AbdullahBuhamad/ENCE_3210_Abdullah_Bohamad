//Lab 3

#define LED_RED 5         // Red LED pin
#define LED_GREEN 4       // Green LED pin
#define BUTTON 2          // Button pin

volatile unsigned long gCounter = 0;      // Global counter for Task 1 (declared volatile)
unsigned long gPreviousMillisTask1 = 0;   // Timer for Task 1
unsigned long gPreviousMillisTask2 = 0;   // Timer for Task 2
unsigned long gPreviousMillisMainTask = 0; // Timer for Main Task

const unsigned long gIntervalTask1 = 1000;   // Interval for Task 1 (1 Hz, 1000 ms)
const unsigned long gIntervalTask2 = 100;    // Interval for Task 2 (10 Hz, 100 ms)
const unsigned long gIntervalMainTask = 3000; // Interval for Main Task (3 seconds)

void setup() {
  // Initialize serial communication for debugging and printing messages
  Serial.begin(9600); 

  // Configure pins as output or input
  pinMode(LED_RED, OUTPUT);    // Set Red LED pin as output
  pinMode(LED_GREEN, OUTPUT);  // Set Green LED pin as output
  pinMode(BUTTON, INPUT);      // Set Button pin as input
}

void loop() {
  // Get the current time using millis()
  unsigned long currentMillis = millis();

  // === Task 1: Blink Green LED at 1 Hz ===
  if (currentMillis - gPreviousMillisTask1 >= gIntervalTask1) {
    gPreviousMillisTask1 = currentMillis; // Reset Task 1 timer

    // Toggle Green LED state
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));

    // Increment the global counter (used as a timer for the main task)
    gCounter++;
  }

  // === Task 2: Read button state and control Red LED at 10 Hz ===
  if (currentMillis - gPreviousMillisTask2 >= gIntervalTask2) {
    gPreviousMillisTask2 = currentMillis; // Reset Task 2 timer

    // Read the current state of the button
    int buttonState = digitalRead(BUTTON); 

    // If button is pressed (HIGH), turn on Red LED. Otherwise, turn it off
    if (buttonState == HIGH) {
      digitalWrite(LED_RED, HIGH);  // Turn on Red LED
    } else {
      digitalWrite(LED_RED, LOW);   // Turn off Red LED
    }
  }

  // === Main Task: Print a message every 3 seconds ===
  if (currentMillis - gPreviousMillisMainTask >= gIntervalMainTask) {
    gPreviousMillisMainTask = currentMillis; // Reset Main Task timer

    // Print a message to the Serial Monitor
    Serial.print("David Lynch is The Greatest | Counter: ");
    Serial.println(gCounter); // Include the counter value
  }
}

