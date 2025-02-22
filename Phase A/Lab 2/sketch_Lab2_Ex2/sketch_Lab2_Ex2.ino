//Lab 2, Ex2

#define LED_RED 4    // Pin for red LED
#define LED_GREEN 5  // Pin for green LED
#define BUTTON 2     // Pin for button

volatile bool buttonPressed = false; // Tracks button state via interrupt

void setup() {
  Serial.begin(9600);

  // Initialize I/Os
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Button with pull-up resistor

  // Ensure LEDs are off initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  // Attach interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON), toggleButtonState, FALLING); // Trigger on button press (falling edge)
}

void loop() {
  static bool sequenceRunning = false; // Tracks the state of the LED sequence
  static int currentStep = 0;          // Tracks the current step in the LED sequence
  static unsigned long lastStepTime = 0; // Tracks time for each step

  // Check if the button state has been updated via the interrupt
  if (buttonPressed) {
    buttonPressed = false; // Reset the flag
    sequenceRunning = !sequenceRunning; // Toggle sequence state
  }

  // If the sequence is running, execute LED sequence
  if (sequenceRunning) {
    unsigned long currentTime = millis();
    if (currentTime - lastStepTime >= 500) { // Change step every 500ms
      lastStepTime = currentTime;
      executeSequenceStep(currentStep); // Execute the current step
      currentStep = (currentStep + 1) % 6; // Loop through 6 steps
    }
  } else {
    // Ensure all LEDs are turned off when sequence is stopped
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
  }
}

void toggleButtonState() {
  // Interrupt Service Routine (ISR) for button press
  buttonPressed = true;
}

void executeSequenceStep(int step) {
  // Turn off all LEDs initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  // Turn on LEDs based on the current step
  switch (step) {
    case 0:
      digitalWrite(LED_RED, HIGH); // R
      Serial.println("Red");
      break;
    case 1:
      digitalWrite(LED_RED, HIGH); // RG
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("Red and Green");
      break;
    case 2:
      digitalWrite(LED_RED, HIGH); // RGB
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("Red, Green, and Blue");
      break;
    case 3:
      digitalWrite(LED_GREEN, HIGH); // GB
      Serial.println("Green and Blue");
      break;
    case 4:
      Serial.println("Blue"); // Print Blue
      break;
    case 5:
      digitalWrite(LED_RED, HIGH); // RB
      Serial.println("Red and Blue");
      break;
  }
}



