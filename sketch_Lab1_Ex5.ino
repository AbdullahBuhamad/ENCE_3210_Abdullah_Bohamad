//Lab 1, Ex5

#define GREEN_LED_PIN 10 // Pin for green LED
#define RED_LED_PIN 9    // Pin for red LED

char array[] = {'A', 'B', 'C', 'D', 'A', 'B', 'C', 'A', 'B', 'C'}; // Example array
char pattern[] = {'A', 'B', 'C'}; // Pattern to detect

int patternOccurrences = 0; // Counter for pattern occurrences

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT); // Set green LED pin as output
  pinMode(RED_LED_PIN, OUTPUT);   // Set red LED pin as output

  digitalWrite(GREEN_LED_PIN, LOW); // Turn off green LED initially
  digitalWrite(RED_LED_PIN, LOW);   // Turn off red LED initially

  Serial.begin(9600); // Initialize serial communication

  // Call the function to count pattern occurrences
  patternOccurrences = countPatternOccurrences(array, sizeof(array) / sizeof(array[0]),
                                                pattern, sizeof(pattern) / sizeof(pattern[0]));

  // If the pattern is found, turn on the green LED
  if (patternOccurrences > 0) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    Serial.print("Pattern found ");
    Serial.print(patternOccurrences);
    Serial.println(" time(s). Green LED ON.");
  } else {
    // If the pattern is not found, turn on the red LED
    digitalWrite(RED_LED_PIN, HIGH);
    Serial.println("Pattern not found. Red LED ON.");
  }
}

void loop() {
  // No need for anything in the loop
}

// Function to count the number of occurrences of a pattern in an array
int countPatternOccurrences(char arr[], int arrSize, char pat[], int patSize) {
  int count = 0;

  // Traverse the array and compare with the pattern
  for (int i = 0; i <= arrSize - patSize; i++) {
    bool match = true;
    for (int j = 0; j < patSize; j++) {
      if (arr[i + j] != pat[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      count++;
    }
  }

  return count; // Return the total number of occurrences
}

