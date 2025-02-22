//Abdullah Bohamad
//Lab 4, Ex1

#define BITSIZE 14  // Define the number of bits for the SAR ADC (14-bit resolution)

float gVref = 3.0;                // Global reference voltage
float gThresh;                    // Global threshold used for comparison
float gQuantized;                 // Global variable to store quantized voltage
int gBits[BITSIZE];               // Global array to store the resulting digital bits

// Function to simulate the SAR ADC process
void SAR_ADC(float Vin) {
    gThresh = gVref / 2;          // Initial threshold set to half of the reference voltage
    gQuantized = 0;               // Reset quantized voltage before each conversion
    float Vstep = gVref / 2;      // Voltage step size, halved after each iteration

    // SAR conversion process
    for (int count = 0; count < BITSIZE; count++) {
        // Compare input voltage (Vin) with current threshold
        if (Vin >= gThresh) {
            gBits[count] = 1;              // Set bit to 1 if Vin >= threshold
            gQuantized += Vstep;           // Add Vstep to quantized voltage
            gThresh += Vstep / 2;          // Move threshold upwards for next bit
        } else {
            gBits[count] = 0;              // Set bit to 0 if Vin < threshold
            gThresh -= Vstep / 2;          // Move threshold downwards for next bit
        }
        Vstep /= 2;  // Halve the step size for the next bit (binary search logic)
    }

    // Print the results for the current Vin
    Serial.print("Input Voltage: ");
    Serial.print(Vin, 4); // Print Vin with 4 decimal places
    Serial.println(" V");

    Serial.print("Digital Output: ");
    for (int i = 0; i < BITSIZE; i++) {
        Serial.print(gBits[i]);  // Print each bit of the digital result
    }
    Serial.println();

    Serial.print("Quantized Voltage: ");
    Serial.print(gQuantized, 6); // Print quantized voltage with 6 decimal places
    Serial.println(" V\n");
}

void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);

    // Wait for Serial Monitor to open
    while (!Serial) {
        ; // Wait for serial port to connect (only needed for native USB ports)
    }

    // Test voltages to simulate SAR conversion
    float test_voltages[] = {0.42, 0.83, 1.65, 2.752};

    // Run SAR_ADC for each test voltage
    for (int i = 0; i < 4; i++) {
        SAR_ADC(test_voltages[i]);
        delay(1000); // Delay for readability on Serial Monitor
    }
}

void loop() {
    // The loop is left empty as the simulation runs once in setup()
}