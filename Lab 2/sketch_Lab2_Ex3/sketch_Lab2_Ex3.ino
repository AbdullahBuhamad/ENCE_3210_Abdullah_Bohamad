//Lab 2, Ex3

#define LED_RED 4    // Pin for red LED
#define LED_GREEN 5  // Pin for green LED
#define LED_BLUE 6   // Pin for blue LED (optional, or simulate by printing)
#define BUTTON 2     // Pin for the first button
#define BUTTON_2 3   // Pin for the second button

// Define three arrays
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // First array with integers
int array2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // Second array with integers
int resultArray[10]; // Third array to store results

volatile int gCounter = 0; // Global counter to keep track of button presses (volatile for use in ISR)
volatile bool operationFlag = false; // Flag to trigger operation in the main loop

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(LED_RED, OUTPUT);    // Set the red LED pin as output
  pinMode(LED_GREEN, OUTPUT);  // Set the green LED pin as output
  pinMode(LED_BLUE, OUTPUT);   // Set the blue LED pin as output
  pinMode(BUTTON, INPUT_PULLUP); // Set the first button pin as input with pull-up resistor
  pinMode(BUTTON_2, INPUT_PULLUP); // Set the second button pin as input with pull-up resistor

  // Attach interrupts to the buttons
  attachInterrupt(digitalPinToInterrupt(BUTTON), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), button2ISR, FALLING);

  // Initialize the result array to 0
  for (int i = 0; i < 10; i++) {
    resultArray[i] = 0;
  }
}

void loop() {
  // If the operation flag is set, perform the operation
  if (operationFlag) {
    operationFlag = false; // Reset the flag

    Serial.println("Second button pressed! Applying operation...");

    // Turn off all LEDs initially
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);

    // Perform the operation based on gCounter
    for (int i = 0; i < 10; i++) {
      if (gCounter == 1) {
        // Addition
        resultArray[i] = array1[i] + array2[i];
      } else if (gCounter == 2) {
        // Subtraction
        resultArray[i] = array1[i] - array2[i];
      } else if (gCounter == 3) {
        // Multiplication
        resultArray[i] = array1[i] * array2[i];
      }
    }

    // Print the results to the Serial Monitor
    Serial.print("Result array: ");
    for (int i = 0; i < 10; i++) {
      Serial.print(resultArray[i]);
      Serial.print(" ");
    }
    Serial.println();

    // Turn on all LEDs to indicate completion
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);

    // Brief delay to show the result
    delay(1000);

    // Turn off all LEDs
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
}

// ISR for the first button (selection of operation)
void button1ISR() {
  gCounter++; // Increment the global counter
  if (gCounter > 3) gCounter = 1; // Wrap around to 1 if it exceeds 3
  Serial.print("Button pressed! gCounter: ");
  Serial.println(gCounter);
}

// ISR for the second button (apply operation)
void button2ISR() {
  operationFlag = true; // Set the flag to perform operation in the main loop
}
