//Lab1, Ex4

#define RED_LED_PIN 5    // Pin for red LED
#define GREEN_LED_PIN 4 // Pin for green LED
#define BLUE_LED_PIN 0  // Pin for blue LED

char letters[] = {'A', 'R', 'C', 'G', 'B', 'R', 'G', 'R', 'B', 'G'}; // Example array
int countR = 0, countG = 0, countB = 0;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);   // Initialize pins as OUTPUT
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, LOW);   // Turn off LEDs initially
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  countR = countG = countB = 0; // Reset counts

  // Traverse the array and count occurrences
  for (int i = 0; i < sizeof(letters) / sizeof(letters[0]); i++) {
    if (letters[i] == 'R') {
      countR++;
    } else if (letters[i] == 'G') {
      countG++;
    } else if (letters[i] == 'B') {
      countB++;
    }
  }

  // Toggle LEDs based on detection
  digitalWrite(RED_LED_PIN, countR > 0 ? HIGH : LOW);
  digitalWrite(GREEN_LED_PIN, countG > 0 ? HIGH : LOW);
  digitalWrite(BLUE_LED_PIN, countB > 0 ? HIGH : LOW);

  // Print the counts to the serial monitor
  Serial.print("R: ");
  Serial.println(countR);
  Serial.print("G: ");
  Serial.println(countG);
  Serial.print("B: ");
  Serial.println(countB);

  delay(10000); // Wait before repeating (adjusted to 10 second)
}
