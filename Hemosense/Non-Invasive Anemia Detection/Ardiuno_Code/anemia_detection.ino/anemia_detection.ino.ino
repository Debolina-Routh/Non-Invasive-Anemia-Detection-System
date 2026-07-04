#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "add your template id"
#define BLYNK_TEMPLATE_NAME "HEMOSENSE"
#define BLYNK_AUTH_TOKEN "token id"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi
const char* ssid = "wifi name";
const char* password = "wifi passward";

// Flask
const char* server = "give your server name";

// Sensor
MAX30105 particleSensor;

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 🔥 LED PIN ADD
#define LED_PIN D5

// Buffers (FAST)
uint32_t irBuffer[50];
uint32_t redBuffer[50];

// Variables
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

float hb = 0;
int filteredHR = 0;

void setup() {
  Serial.begin(115200);

    // 🔥 LED INIT
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  if (!particleSensor.begin(Wire)) {
    Serial.println("MAX30102 not found");
    while (1);
  }

  particleSensor.setup();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  // 🔵 Startup Screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("HELLO !");
  delay(1000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("HEMOSENSE");
  display.setTextSize(1);
  display.setCursor(10, 40);
  display.println("System is ready");

  display.display();
  delay(2000);
}

void loop() {

  Blynk.run();

  long irValue = particleSensor.getIR();

  display.clearDisplay();

  // 🔴 NO FINGER
  if (irValue < 40000) {

        // 🔥 LED OFF
    digitalWrite(LED_PIN, HIGH);

    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("Place");
    display.setCursor(10, 45);
    display.println("Finger");
    display.display();
    return;
  }

    // 🔥 FINGER DETECTED → LED ON
  digitalWrite(LED_PIN, LOW);

  // Collect 50 samples (FAST)
  for (byte i = 0; i < 50; i++) {
    while (!particleSensor.available())
      particleSensor.check();

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }

  // Calculate HR & SpO2
  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, 50, redBuffer,
    &spo2, &validSPO2,
    &heartRate, &validHeartRate
  );

  // 🟢 HR FILTER
  if (heartRate > 40 && heartRate < 120) {
    filteredHR = heartRate;
  }

  int redValue = redBuffer[49];
  int irValue2 = irBuffer[49];

  // 📡 Flask API
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, server);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"red\":" + String(redValue) +
                  ",\"ir\":" + String(irValue2) +
                  ",\"age\":22,\"gender\":0}";

    int code = http.POST(json);

    if (code > 0) {
      String payload = http.getString();

      int start = payload.indexOf(":") + 1;
      int end = payload.indexOf("}");

      hb = payload.substring(start, end).toFloat();
    }

    http.end();
  }

  // 🟣 Risk
  String risk = (hb < 10.0) ? "Anemia" : "Normal";

  // 📟 OLED UI (YOUR DESIGN)
  display.setTextSize(1);

  // Line 1 → HR & SpO2
  display.setCursor(0, 0);
  display.print("HR:");
  display.print(filteredHR);

  display.setCursor(64, 0);
  display.print("SpO2:");
  display.print(spo2);

  // Line 2 → Hb
  display.setTextSize(2);
  display.setCursor(0,20);
  display.print("Hb:");
  display.print(hb, 1);
  display.setTextSize(1);
  display.print("g/dL");

  // Line 3 → Risk
  display.setTextSize(1);
  display.setCursor(0,50);
  display.print("risk: ");
  display.print(risk);

  display.display();

  // 📱 Blynk
  Blynk.virtualWrite(V0, filteredHR);
  Blynk.virtualWrite(V1, spo2);
  Blynk.virtualWrite(V2, hb);
  Blynk.virtualWrite(V3, risk);

  delay(1000);
}