#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP32Servo.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// const int servoPin = 13;
// Servo servo;
// char ch = '0';
// String incomingMessage = "";
// // Initialize with the I2C addr 0x3C
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// void setup() {
//   Serial.begin(9600);
//   servo.attach(servoPin);
//   servo.write(70);
//   Serial.clearWriteError();
//   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Don't proceed, loop forever
//   }
  
//   display.clearDisplay();       // Clear the display buffer
//   display.setTextSize(1);       // Set text size to 1 (default)
//   display.setTextColor(SSD1306_WHITE);  // Set text color to white
//   display.setCursor(0,27);     // Start at top left, move right
//   display.cp437(true);          // Use full 256 char 'Code Page 437' font
//   display.println("Hello, ESP32!"); // Print text to screen
//   display.display();            // Display buffer content on screen
// }

// void loop() {
//   // 检查是否有数据可读
//   display.clearDisplay();
//   int angle = readDigital();
//   if(angle != -1 && angle >= 0 && angle <= 180) {
//     servo.write(angle);
//     Serial.println("Angle: " + String(angle));
//   }
// }


// // put function declarations here:

// int readDigital() {
//   bool read = false;
//   int res = 0;
//   char ch = '0';
//   int angle = readDigital();
//   if(angle != -1 && angle >= 0 && angle <= 180) {
//     servo.write(angle);
//     Serial.println("Angle: " + String(angle));
//   }
//   if(Serial.available() > 0) {
//     while(ch >= '0' && ch <= '9') {
//       if(Serial.available() > 0) {
//         ch = Serial.read();
//         display.setTextSize(2);
//         display.setCursor(0, 27);
//         display.println(ch);
//         display.display();
//         if(ch < '0' || ch > '9') break;
//         res = res * 10 + int(ch) - 48;
//         Serial.println("ch: " + String(ch));
//         Serial.println("Angle: " + String(res));
//       }
//       read = true;
//     }
//   }
//   if(read) return res;
//   else return -1;
// }
#include <Arduino.h>
#include <ESP32Servo.h>

// put function declarations here:

const int servoPin = 13;
Servo servo;

String incomingMessage = "@$$##@@@";
// Initialize with the I2C addr 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(70);
  Serial.clearWriteError();
  while(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    // for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();       // Clear the display buffer
  display.setTextSize(2);       // Set text size to 1 (default)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  display.setCursor(0,0);     // Start at top left, move right
  display.cp437(true);          // Use full 256 char 'Code Page 437' font
  display.println("#"); // Print text to screen
  display.display(); 
}

int readDigital() {
  bool read = false;
  int res = 0;
  char ch = '0';
  if(Serial.available() > 0) {
    while(ch >= '0' && ch <= '9') {
      if(Serial.available() > 0) {
        ch = Serial.read();
        if((ch < '0' || ch > '9')&&ch!='a'&&ch!='\n'){
          incomingMessage+=ch;
          break;
        }
        if(ch >= '0' && ch <= '9') res = res * 10 + int(ch) - 48;
        Serial.println("ch: " + String(ch));
        Serial.println("Angle: " + String(res));
      }
      read = true;
    }
  }
  if(read) return res;
  else return -1;
}

void loop() {
  // put your main code here, to run repeatedly:
  int angle = readDigital();
  if(angle != -1 && angle >= 0 && angle <= 180) {
    servo.write(angle);
    Serial.println("Angle: " + String(angle));
  }

  display.setTextSize(2);       // Set text size to 1 (default)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  display.setCursor(0,0);     // Start at top left, move right
  display.cp437(true); 
  display.println(incomingMessage); // Print text to screen
  display.display(); 
}