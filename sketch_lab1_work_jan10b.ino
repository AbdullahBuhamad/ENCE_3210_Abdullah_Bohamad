#define LED_PIN 13

#define myDDRB (*(volatile uint8_t*) 0x24)

#define myPORTB (*(volatile uint8_t*) 0x25)

void setup() {
  // put your setup code here, to run once:
 // pinMode(LED_PIN, OUTPUT);
 myDDRB |= PORTBS;
}

void loop() {
  // put your main code here, to run repeatedly:
  //digtialWire(LED_PIN, HIGH);
  myPORTB |= PORTBS
  delay(200);
  //digtialWire(LED_PIN, LOW);
  myPORTB &= ~PORTBS;
  delay(200);

}
