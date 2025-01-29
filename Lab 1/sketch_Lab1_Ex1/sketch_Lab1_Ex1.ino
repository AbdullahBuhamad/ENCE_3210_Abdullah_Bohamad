//Lab 1, Ex1

#define gArraySize 512 // Define the size of the array

int gResults[gArraySize]; // Global array to store results

// Function to calculate twice the square of a number
int calculateTwiceSquare(int number) {
    return 2 * (number * number);
}

void setup() {
    Serial.begin(9600); // Initialize Serial communication for output

    // Calculate twice the square for numbers from 0 to 511
    for (int i = 0; i < gArraySize; i++) {
        gResults[i] = calculateTwiceSquare(i);
    }

    // Print the results to the Serial Monitor
    Serial.println("Twice the square of numbers from 0 to 511:");
    for (int i = 0; i < gArraySize; i++) {
        Serial.print("Number: ");
        Serial.print(i);
        Serial.print(", Result: ");
        Serial.println(gResults[i]);
    }
}

void loop() {
    // Nothing to do in the loop
}

