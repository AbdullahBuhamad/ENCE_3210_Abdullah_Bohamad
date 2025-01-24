//Lab 1, Ex3

#define MIN_INT16 -32768 // Define minimum value for 16-bit integer

// Define the global array of integers
int myArray[50] = {5, 23, 67, 12, 34, 87, 45, 91, 16, 29, 
                   14, 18, 22, 33, 44, 55, 66, 77, 88, 99, 
                   13, 17, 24, 31, 48, 51, 60, 70, 80, 90, 
                   10, 20, 30, 40, 50, 61, 71, 81, 91, 6, 
                   3, 11, 21, 32, 42, 52, 62, 72, 82, 92};

// Define the memory location after the array
int* secondMaxLocation = &myArray[50];

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  int secondMax = findSecondMaximum(myArray, 50); // Find second max
  
  *secondMaxLocation = secondMax; // Store result after array
  
  // Debugging output
  Serial.print("Second Maximum: ");
  Serial.println(secondMax);
  Serial.print("Stored at address: ");
  Serial.println((uintptr_t)secondMaxLocation, HEX);
}

void loop() {
  // Nothing to do here
}

// Function to find the second maximum in an array
int findSecondMaximum(int arr[], int size) {
  if (size < 2) {
    Serial.println("Error: Not enough elements to determine second maximum.");
    return -1; // Error code
  }

  int max = MIN_INT16;       // Initialize max to smallest value
  int secondMax = MIN_INT16; // Initialize second max to smallest value

  for (int i = 0; i < size; i++) {
    if (arr[i] > max) {
      secondMax = max;
      max = arr[i];
    } else if (arr[i] > secondMax && arr[i] < max) {
      secondMax = arr[i];
    }
  }

  return secondMax;
}