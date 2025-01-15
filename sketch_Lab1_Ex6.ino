//Lab 1, Ex6

#define RED_LED_PIN 9    // Pin for red LED
#define GREEN_LED_PIN 10 // Pin for green LED
#define BLUE_LED_PIN 11  // Pin for blue LED
#define BUTTON_PIN 7     // Pin for button

bool isRunning = false; // Tracks whether the sequence is active

void setup() {
  // Set LED pins as output
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Set button pin as input with pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Ensure LEDs are initially off
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Initialize serial communication for debugging 
  Serial.begin(9600);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) { // Confirm button press
      isRunning = !isRunning; // Toggle the sequence on/off
      delay(200); // Prevent multiple toggles from a single press
    }
  }

  if (isRunning) {
    // Execute the LED sequence
    turnOnRed();
    turnOnRedGreen();
    turnOnRGB();
    turnOnGreenBlue();
    turnOnBlue();
    turnOnRedBlue();
  }
}

// Functions to turn on specific LED combinations
void turnOnRed() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(500); // Delay to show the LED
}

void turnOnRedGreen() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(500); // Delay to show the LED
}

void turnOnRGB() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(500); // Delay to show the LED
}

void turnOnGreenBlue() {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(500); // Delay to show the LED
}

void turnOnBlue() {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(500); // Delay to show the LED
}

void turnOnRedBlue() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(500); // Delay to show the LED
}
