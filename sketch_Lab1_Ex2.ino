//Lab 1, Ex 2

double cosine[360]; // Array to store cosine values for 360 degrees

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  for (int i = 0; i < 360; i++) { // Loop through degrees 0 to 359
    cosine[i] = cos(i * DEG_TO_RAD); // Calculate cosine (convert degrees to radians)
    Serial.println(cosine[i]); // Print the calculated cosine value
  }
}
