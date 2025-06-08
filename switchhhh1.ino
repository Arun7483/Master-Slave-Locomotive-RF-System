#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; // Address for communication

const int buttonPin = 2; // Pin connected to the push button
const int buttonPin1 = 4;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP); // Configure button pin as input with pull-up
  Serial.begin(9600); // Initialize Serial Monitor
  radio.begin(); // Initialize NRF24L01 module
  radio.openWritingPipe(address); // Open the writing pipe with the specified address
  radio.setPALevel(RF24_PA_HIGH); // Set Power Amplifier level to high
  radio.stopListening(); // Set the module as a transmitter // Configure button pin as input with pull-up
  
}

void loop() {
  bool buttonState = digitalRead(buttonPin); // Read the state of the button
  if (buttonState == LOW) { // Button pressed (active LOW)
    const char text[] = "LED_ON"; // Message to turn on the LED
    bool success = radio.write(&text, sizeof(text)); // Send the message
    if (success) {
      Serial.println("Message sent: LED_ON");
    } else {
      Serial.println("Message failed to send.");
    }
  } else {
    const char text[] = "LED_OFF"; // Message to turn off the LED
    bool success = radio.write(&text, sizeof(text)); // Send the message
    if (success) {
      Serial.println("Message sent: LED_OFF");
    } else {
      Serial.println("Message failed to send.");
    }
  }
  delay(200); // Delay to avoid sending messages too frequently
  const char text[] = "Ambresh sissss";
  radio.write(&text, sizeof(text));
  delay(1000);
}
