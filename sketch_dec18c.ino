#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define NRF24L01 radio pins and address
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// Define LED pins
const int led1Pin = 2;
const int led2Pin = 4;


void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0,0);     // Start at top-left corner
  display.println("Starting...");
  display.display();
  delay(2000);
}

void loop() {
  if (radio.available()) {
    char message[32] = "";
    radio.read(&message, sizeof(message));

    Serial.print("Received message: ");
    Serial.println(message);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println(message);
    display.display();

    if (strcmp(message, "Break Apply") == 0) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
    } else if (strcmp(message, "Break Release") == 0) {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    } else if (strcmp(message, "Fail safe Break Apply") == 0) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, HIGH);
    } else if (strcmp(message, "ALL_OFF") == 0) {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, LOW);
    }
  }

  delay(100);
}