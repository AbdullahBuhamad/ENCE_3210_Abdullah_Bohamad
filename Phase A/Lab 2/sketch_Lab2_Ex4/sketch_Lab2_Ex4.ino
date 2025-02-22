//Lab 2, Ex4

 #define BUTTON 2

// Global arrays
int x[10];
int y[10];

// Counter to track the current index for calculation
volatile int index = 0;

void setup() {
  Serial.begin(9600);

  // Initialize the x array with some values
  for (int i = 0; i < 10; i++) {
    x[i] = i + 1; // Example: Fill with 1, 2, 3, ..., 10
  }

  // Print initial x array
  Serial.println("Initial x array:");
  for (int i = 0; i < 10; i++) {
    Serial.print(x[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Configure button pin
  pinMode(BUTTON, INPUT_PULLUP);

  // Attach interrupt to the button
  attachInterrupt(digitalPinToInterrupt(BUTTON), calculateY, FALLING);
}

void loop() {
  // Main code can do other tasks or print results
  delay(1000); // Just for example
  
  Serial.println("Updated y array:");
  for (int i = 0; i < 10; i++) {
    Serial.print(y[i]);
    Serial.print(" ");
  }
  Serial.println();
}

// Interrupt Service Routine (ISR)
void calculateY() {
  // Ensure index is within bounds
  if (index < 10) {
    if (index == 0) {
      // Special case for the first element, since x[n-1] does not exist
      y[index] = 2 * x[index];
    } else {
      // Apply the formula y[n] = 2 * x[n] - x[n-1]
      y[index] = 2 * x[index] - x[index - 1];
    }
    index++; // Move to the next index
  }
}

