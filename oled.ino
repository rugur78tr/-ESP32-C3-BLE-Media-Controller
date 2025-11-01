#include <Arduino.h>
#include <BleKeyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === BLE Keyboard Setup ===
BleKeyboard bleKeyboard("ESP32-C3 Media Controller", "DIY", 100);

// === OLED Setup ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === Rotary Encoder Pins ===
#define CLK 2
#define DT 3
#define SW 4

// === LED Pin ===
#define LED_PIN 8

// === Variables ===
int lastClk = HIGH;
int volume = 50;
bool isMuted = false;
bool isConnected = false;
unsigned long lastDebounce = 0;
const int debounceDelay = 200;

// === Helper Functions ===
void drawUI() {
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.print("ESP32-C3 MEDIA CTRL");

  // Bluetooth icon
  if (isConnected) {
    display.setCursor(110, 0);
    display.print("🔵");
  } else {
    display.setCursor(110, 0);
    display.print("❌");
  }

  // Volume Bar
  display.drawRect(10, 20, 108, 10, SSD1306_WHITE);
  int barLength = map(volume, 0, 100, 0, 106);
  display.fillRect(11, 21, barLength, 8, SSD1306_WHITE);

  // Volume percentage
  display.setTextSize(1);
  display.setCursor(45, 35);
  display.print("Volume: ");
  display.print(volume);
  display.print("%");

  // Status Icons
  display.setTextSize(2);
  display.setCursor(10, 50);
  if (isMuted) {
    display.print("🔇 MUTE");
  } else {
    display.print("🎵 PLAY");
  }

  display.display();
}

void setup() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  // OLED init
  Wire.begin(6, 7);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found!"));
    for (;;);
  }
  display.clearDisplay();
  display.display();

  bleKeyboard.begin();

  drawUI();
}

void loop() {
  // LED status
  if (bleKeyboard.isConnected()) {
    digitalWrite(LED_PIN, HIGH);
    isConnected = true;
  } else {
    isConnected = false;
    digitalWrite(LED_PIN, millis() % 1000 < 300);
  }

  // Rotary Encoder Read
  int clkState = digitalRead(CLK);
  int dtState = digitalRead(DT);

  if (clkState != lastClk) {
    if (dtState != clkState) {
      volume = constrain(volume + 5, 0, 100);
      if (bleKeyboard.isConnected()) bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    } else {
      volume = constrain(volume - 5, 0, 100);
      if (bleKeyboard.isConnected()) bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
    drawUI();
  }
  lastClk = clkState;

  // Button Press (Mute / Play)
  if (digitalRead(SW) == LOW && millis() - lastDebounce > debounceDelay) {
    lastDebounce = millis();
    if (bleKeyboard.isConnected()) {
      if (isMuted) {
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        isMuted = false;
      } else {
        bleKeyboard.write(KEY_MEDIA_MUTE);
        isMuted = true;
      }
    }
    drawUI();
  }

  delay(5);
}
