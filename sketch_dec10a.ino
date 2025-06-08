#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001"; // Same address as used in the Master

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  radio.begin();      // Initialize the NRF24L01 module
  radio.openReadingPipe(0, address); // Open a reading pipe with the specified address
  radio.setPALevel(RF24_PA_HIGH);    // Set power amplifier level to high
  radio.startListening();            // Start listening for incoming data
}

void loop() {
  if (radio.available()) {           // Check if data is available to read
    char text[32] = "";              // Create a buffer to store received data
    radio.read(&text, sizeof(text)); // Read the data into the buffer
    Serial.print("Received message: ");
    Serial.println(text);            // Print the received message
  }
  delay(100); // Add a small delay to avoid overwhelming the serial output
}
