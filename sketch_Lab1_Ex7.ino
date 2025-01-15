//Lab 1, Ex7

#define RED_LED_PIN 9    // Pin for red LED (Addition)
#define GREEN_LED_PIN 10 // Pin for green LED (Subtraction)
#define BLUE_LED_PIN 11  // Pin for blue LED (Multiplication)

// Simulated button press variables
bool button1Pressed = false; // Simulates Button 1 (operation selection)
bool button2Pressed = false; // Simulates Button 2 (apply operation)

int array1[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50}; // First array
int array2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};        // Second array
int array3[10] = {0};                                    // Third array (empty initially)

int operationCounter = 0; // Counter for operation selection
bool programStarted = false; // Ensures "Program started" prints only once

void setup() {
  // Serial communication for debugging/testing
  Serial.begin(9600);

  // Setup LED pins as OUTPUT
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Ensure all LEDs are OFF initially
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Print the startup message (once only)
  if (!programStarted) {
    Serial.println("Program started. Simulate button presses in the code.");
    programStarted = true; // Ensure the message prints only once
  }
}

void loop() {
  // Simulate pressing Button 1 for operation selection
  simulateButton1Press();

  // Simulate pressing Button 2 for applying the operation
  simulateButton2Press();
}

// Simulate Button 1 press
void simulateButton1Press() {
  static bool lastButton1State = false;

  if (!lastButton1State) {
    button1Pressed = true; // Simulate a button press
    lastButton1State = true; // Simulate a button being "held"
  }

  if (button1Pressed) {
    operationCounter = (operationCounter + 1) % 3; // Cycle between 0, 1, 2
    updateOperationDisplay(); // Update LED and Serial display
    button1Pressed = false;   // Reset simulated button state
  }
}

// Simulate Button 2 press
void simulateButton2Press() {
  static bool lastButton2State = false;

  if (!lastButton2State) {
    button2Pressed = true; // Simulate a button press
    lastButton2State = true; // Simulate a button being "held"
  }

  if (button2Pressed) {
    applyOperation(); // Perform the selected operation
    indicateOperationComplete(); // Indicate completion with LEDs
    button2Pressed = false; // Reset simulated button state
  }
}

// Update LED and Serial display based on the selected operation
void updateOperationDisplay() {
  // Turn off all LEDs first
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Turn on the appropriate LED
  if (operationCounter == 0) {
    digitalWrite(RED_LED_PIN, HIGH); // Addition
    Serial.println("Selected Operation: Addition");
  } else if (operationCounter == 1) {
    digitalWrite(GREEN_LED_PIN, HIGH); // Subtraction
    Serial.println("Selected Operation: Subtraction");
  } else if (operationCounter == 2) {
    digitalWrite(BLUE_LED_PIN, HIGH); // Multiplication
    Serial.println("Selected Operation: Multiplication");
  }
}

// Perform the selected operation and display results
void applyOperation() {
  Serial.println("Applying operation...");
  for (int i = 0; i < 10; i++) {
    if (operationCounter == 0) {
      array3[i] = array1[i] + array2[i]; // Addition
    } else if (operationCounter == 1) {
      array3[i] = array1[i] - array2[i]; // Subtraction
    } else if (operationCounter == 2) {
      array3[i] = array1[i] * array2[i]; // Multiplication
    }
    // Print the result for each element
    Serial.print("Result for index ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(array3[i]);
  }
  Serial.println("Operation complete.");
}

// Indicate operation completion by turning ON all LEDs briefly
void indicateOperationComplete() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(1000); // Keep all LEDs ON for 1 second
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}