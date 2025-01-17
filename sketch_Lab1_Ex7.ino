//Lab 1, Ex7

#define LED_RED 4    // Pin for red LED
#define LED_GREEN 5  // Pin for green LED
#define LED_BLUE 6   // Pin for blue LED (optional, or simulate by printing)
#define BUTTON 2     // Pin for the first button
#define BUTTON_2 3   // Pin for the second button

// Define three arrays
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // First array with integers
int array2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // Second array with integers
int resultArray[10]; // Third array to store results

int gCounter = 0;  // Global counter to keep track of button presses
bool buttonState = LOW;  // Current state of the first button
bool lastButtonState = LOW;  // Previous state of the first button
bool button2State = LOW; // Current state of the second button
bool lastButton2State = LOW; // Previous state of the second button

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(LED_RED, OUTPUT);    // Set the red LED pin as output
  pinMode(LED_GREEN, OUTPUT);  // Set the green LED pin as output
  pinMode(LED_BLUE, OUTPUT);   // Set the blue LED pin as output
  pinMode(BUTTON, INPUT);      // Set the first button pin as input
  pinMode(BUTTON_2, INPUT);    // Set the second button pin as input

  // Initialize the result array to 0
  for (int i = 0; i < 10; i++) {
    resultArray[i] = 0;
  }
}

void loop() {
  buttonState = digitalRead(BUTTON); // Read the first button state
  button2State = digitalRead(BUTTON_2); // Read the second button state

  // Handle the first button (selection of operation)
  if (buttonState == HIGH && lastButtonState == LOW) {
    gCounter++; // Increment the global counter
    if (gCounter > 3) gCounter = 1; // Wrap around to 1 if it exceeds 3
    Serial.print("Button pressed! gCounter: ");
    Serial.println(gCounter);
  }

  // Handle the second button (apply operation to all elements)
  if (button2State == HIGH && lastButton2State == LOW) {
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

  // Update button states
  lastButtonState = buttonState;
  lastButton2State = button2State;
}
