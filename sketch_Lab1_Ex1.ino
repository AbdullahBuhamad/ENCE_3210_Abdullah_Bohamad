//Lab 1, Ex1

#define LED_PIN 13 // Define LED_PIN for reference

#define myDDRB (*(volatile uint8_t*) 0x24) // Data Direction Register for port B
#define myPORTB (*(volatile uint8_t*) 0x25) // Data Register for port B

void setup() {
  myDDRB |= PORTB; // Set port B pins as output
}

void loop() {
  myPORTB |= PORTB; // Turn LED on
  delay(200); // Wait 200ms
  myPORTB &= ~PORTB; // Turn LED off
  delay(200); // Wait 200ms
}
