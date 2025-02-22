//Lab 2, Ex1

#define LED_GREEN 4
#define LED_RED 5

#define Button_1 2  // Interrupt pin for Button 1
#define Button_2 3  // Interrupt pin for Button 2

volatile int button1Count = 0;  // Counter for Button 1
volatile int button2Count = 0;  // Counter for Button 2

void setup() {
  // Initialize communications
  Serial.begin(9600);

  // Initialize I/Os
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(Button_1, INPUT_PULLUP);  // Set button pins as input with pull-up resistors
  pinMode(Button_2, INPUT_PULLUP);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(Button_1), button1ISR, CHANGE); // Trigger on falling edge (button press)
  attachInterrupt(digitalPinToInterrupt(Button_2), button2ISR, CHANGE);
}

void loop() {
  // Compare button press counts and control LEDs
  if (button1Count > button2Count) {
    // Turn on the red LED if Button 1 is pressed more
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  } else if (button1Count < button2Count) {
    // Turn on the green LED if Button 2 is pressed more
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    // Print "BLUE" if button presses are equal
    Serial.println("BLUE");
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
  }
}

// ISR for Button 1
void button1ISR() {
  button1Count++;
}

// ISR for Button 2
void button2ISR() {
  button2Count++;
}
