//Lab 1, Ex5

#define GREEN_LED_PIN 4 // Pin for green LED
#define RED_LED_PIN 5   // Pin for red LED

char gArray[] = {'A', 'B', 'C', 'D', 'A', 'B', 'C', 'A', 'B', 'C'}; // Array to search in
char gPattern[] = {'A', 'B', 'C'}; // Pattern to detect

int gPatternOccurrences = 0; // Global variable for pattern occurrences

// Function to count the number of occurrences of a pattern in an array
int countPatternOccurrences(char *pArray, int arraySize, char *pPattern, int patternSize) {
    int count = 0;

    // Traverse the array and compare with the pattern
    for (int i = 0; i <= arraySize - patternSize; i++) {
        bool match = true;
        for (int j = 0; j < patternSize; j++) {
            if (pArray[i + j] != pPattern[j]) {
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

// Function to control LEDs based on pattern detection
void controlLEDs() {
    if (gPatternOccurrences > 0) {
        digitalWrite(GREEN_LED_PIN, HIGH);
        Serial.print("Pattern found ");
        Serial.print(gPatternOccurrences);
        Serial.println(" time(s). Green LED ON.");
    } else {
        digitalWrite(RED_LED_PIN, HIGH);
        Serial.println("Pattern not found. Red LED ON.");
    }
}

void setup() {
    pinMode(GREEN_LED_PIN, OUTPUT); // Set green LED pin as output
    pinMode(RED_LED_PIN, OUTPUT);   // Set red LED pin as output

    digitalWrite(GREEN_LED_PIN, LOW); // Turn off green LED initially
    digitalWrite(RED_LED_PIN, LOW);   // Turn off red LED initially

    Serial.begin(9600); // Initialize serial communication

    // Call the function to count pattern occurrences
    gPatternOccurrences = countPatternOccurrences(
        gArray, sizeof(gArray) / sizeof(gArray[0]),
        gPattern, sizeof(gPattern) / sizeof(gPattern[0]));

    // Control LEDs based on pattern detection
    controlLEDs();
}

void loop() {
    // No need for anything in the loop
}


