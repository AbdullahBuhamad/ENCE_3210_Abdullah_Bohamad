//Lab 1, Ex 2

#include <math.h> // For trigonometric functions

#define gArraySize 360 // Define the size of the array (0 to 359 degrees)
float gCosineValues[gArraySize]; // Global array to store cosine values

// Function to calculate cosine values
void calculateCosineValues() {
    for (int i = 0; i < gArraySize; i++) {
        gCosineValues[i] = cos(i * DEG_TO_RAD); // Convert degrees to radians and calculate cosine
    }
}

void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 baud
    delay(100); // Allow Serial Monitor to sync
    Serial.println("Setup started..."); // Debug message

    // Calculate cosine values for 0 to 359 degrees
    calculateCosineValues();

    // Print the cosine values to the Serial Monitor
    Serial.println("Cosine values for 0 to 359 degrees:");
    for (int i = 0; i < gArraySize; i++) {
        Serial.print("Angle: ");
        Serial.print(i);
        Serial.print(" degrees, Cosine: ");
        Serial.println(gCosineValues[i], 6); // Print with 6 decimal places
    }
}

void loop() {
    // Empty loop since calculations and printing are done in setup()
}

