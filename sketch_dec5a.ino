#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; // Address for communication

const int button1Pin = 2; // Pin connected to push button 1
const int button2Pin = 4; // Pin connected to push button 2

void setup() {
  pinMode(button1Pin, INPUT_PULLUP); // Configure button 1 pin as input with pull-up
  pinMode(button2Pin, INPUT_PULLUP); // Configure button 2 pin as input with pull-up

  Serial.begin(9600); // Initialize Serial Monitor
  radio.begin(); // Initialize NRF24L01 module
  radio.openWritingPipe(address); // Open the writing pipe with the specified address
  radio.setPALevel(RF24_PA_HIGH); // Set Power Amplifier level to high
  radio.stopListening(); // Set the module as a transmitter
}

void loop() {
  bool button1State = digitalRead(button1Pin); // Read the state of button 1
  bool button2State = digitalRead(button2Pin); // Read the state of button 2

  char message[32] = ""; // Buffer to store the message

  // Determine the message to send based on button states
  if (button1State == LOW && button2State == HIGH) {
    strcpy(message, "LED1_ON");
  } else if (button1State == HIGH && button2State == LOW) {
    strcpy(message, "LED2_ON");
  } else if (button1State == LOW && button2State == LOW) {
    strcpy(message, "BOTH_ON");
  } else {
    strcpy(message, "ALL_OFF");
  }

  // Send the message
  bool success = radio.write(&message, sizeof(message));
  if (success) {
    Serial.print("Message sent: ");
    Serial.println(message);
  } else {
    Serial.println("Message failed to send.");
  }

  delay(200); // Delay to debounce and prevent frequent sending
  const char text[] = "Master-Slave Config";
  radio.write(&text, sizeof(text));
  delay(1000);
}