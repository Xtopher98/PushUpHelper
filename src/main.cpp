#include <Arduino.h>
#include <ESP8266WiFi.h>       //Huzzah board
#include <Adafruit_SH110X.h>   //OLED Display
#include <Adafruit_GFX.h>      //Extra Display controls
#include <Adafruit_VL53L0X.h>  //Distance Sensor

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

//LCD buttons
#define BUTTON_A  0
#define BUTTON_B 16
#define BUTTON_C  2

//buzzer
#define BUZZER 13
int value = 110;

void setup() {
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);

  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 

  display.begin(0x3C, true);
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  display.setTextSize(4);
  display.setTextColor(SH110X_WHITE);
}


void loop() {
  value += 10;
  tone(BUZZER, value);
  delay(100);
  noTone(BUZZER);

  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  display.setCursor(0,0);
  display.clearDisplay();
  // display.display();
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    display.println(measure.RangeMilliMeter); display.println("mm");
  } else {
    Serial.println(" out of range ");
    display.println("D:");
  }
  display.display();
  delay(100);
}



// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SH110X.h>

// Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

// #define BUTTON_A  0
// #define BUTTON_B 16
// #define BUTTON_C  2

// void setup() {
//   Serial.begin(115200);

//   Serial.println("128x64 OLED FeatherWing test");
//   display.begin(0x3C, true); // Address 0x3C default

//   Serial.println("OLED begun");

//   // Show image buffer on the display hardware.
//   // Since the buffer is intialized with an Adafruit splashscreen
//   // internally, this will display the splashscreen.
//   display.display();
//   delay(1000);

//   // Clear the buffer.
//   display.clearDisplay();
//   display.display();

//   display.setRotation(1);
//   Serial.println("Button test");

//   pinMode(BUTTON_A, INPUT_PULLUP);
//   pinMode(BUTTON_B, INPUT_PULLUP);
//   pinMode(BUTTON_C, INPUT_PULLUP);

//   // text display tests
//   display.setTextSize(1);
//   display.setTextColor(SH110X_WHITE);
//   display.setCursor(0,0);
//   display.print("Connecting to SSID\n'adafruit':");
//   display.print("connected!");
//   display.println("IP: 10.0.1.23");
//   display.println("Sending val #0");
//   display.display(); // actually display all of the above
// }

// void loop() {
//   if(!digitalRead(BUTTON_A)) display.print("A");
//   if(!digitalRead(BUTTON_B)) display.print("B");
//   if(!digitalRead(BUTTON_C)) display.print("C");
//   delay(10);
//   yield();
//   display.display();
// }



// // #include <Arduino.h>
// // #include <ESP8266WiFi.h>       //Huzzah board
// // #include <Adafruit_SH110X.h>   //OLED Display
// // #include <Adafruit_GFX.h>      //Extra Display controls
// // #include <Adafruit_VL53L0X.h>  //Distance Sensor

// // const char* ssid     = "ianjulie";
// // const char* password = "Charlie1";

// // const char* host = "wifitest.adafruit.com";

// // void setup() {
// //   Serial.begin(115200);
// //   delay(100);

// //   // We start by connecting to a WiFi network

// //   Serial.println();
// //   Serial.println();
// //   Serial.print("Connecting to ");
// //   Serial.println(ssid);
  
// //   WiFi.begin(ssid, password);
  
// //   while (WiFi.status() != WL_CONNECTED) {
// //     delay(500);
// //     Serial.print(".");
// //   }

// //   Serial.println("");
// //   Serial.println("WiFi connected");  
// //   Serial.println("IP address: ");
// //   Serial.println(WiFi.localIP());
// // }

// // int value = 0;

// // void loop() {
// //   delay(5000);
// //   ++value;

// //   Serial.print("connecting to ");
// //   Serial.println(host);
  
// //   // Use WiFiClient class to create TCP connections
// //   WiFiClient client;
// //   const int httpPort = 80;
// //   if (!client.connect(host, httpPort)) {
// //     Serial.println("connection failed");
// //     return;
// //   }
  
// //   // We now create a URI for the request
// //   String url = "/testwifi/index.html";
// //   Serial.print("Requesting URL: ");
// //   Serial.println(url);
  
// //   // This will send the request to the server
// //   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
// //                "Host: " + host + "\r\n" + 
// //                "Connection: close\r\n\r\n");
// //   delay(500);
  
// //   // Read all the lines of the reply from server and print them to Serial
// //   while(client.available()){
// //     String line = client.readStringUntil('\r');
// //     Serial.print(line);
// //   }
  
// //   Serial.println();
// //   Serial.println("closing connection");
// // }
