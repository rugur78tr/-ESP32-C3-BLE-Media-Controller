#include <NimBLEDevice.h>
#include <BleKeyboard.h>

#define PIN_CLK 2
#define PIN_DT 3
#define PIN_SW 4

#define LED_EXTERNAL 10   // Harici LED pini
#define LED_INTERNAL 8    // ESP32-C3 dahili LED pini (aktif LOW)

BleKeyboard bleKeyboard("ESP32-C3 Media Controller", "DIY", 100);

int lastStateCLK;
bool buttonPressed = false;
unsigned long buttonPressTime = 0;
unsigned long ledBlinkTimer = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(LED_EXTERNAL, OUTPUT);
  pinMode(LED_INTERNAL, OUTPUT);

  lastStateCLK = digitalRead(PIN_CLK);

  Serial.println("BLE Media Controller başlatıldı.");
}

void loop() {
  // 🔆 LED durum yönetimi
  if (!bleKeyboard.isConnected()) {
    // Bağlantı yoksa LED yavaşça yanıp sönsün
    if (millis() - ledBlinkTimer > 500) {
      ledBlinkTimer = millis();
      ledState = !ledState;

      // Harici LED (aktif HIGH)
      digitalWrite(LED_EXTERNAL, ledState ? HIGH : LOW);

      // Dahili LED (aktif LOW)
      digitalWrite(LED_INTERNAL, ledState ? LOW : HIGH);
    }
  } else {
    // Bağlıysa LED sabit yanmalı
    digitalWrite(LED_EXTERNAL, HIGH);  // Harici LED açık
    digitalWrite(LED_INTERNAL, LOW);   // Dahili LED açık (aktif LOW)
  }

  // 🧭 Rotary hareketi
  int currentStateCLK = digitalRead(PIN_CLK);
  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(PIN_DT) != currentStateCLK) {
      Serial.println("Volume Up");
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    } else {
      Serial.println("Volume Down");
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
  }
  lastStateCLK = currentStateCLK;

  // 🔘 Buton işlemleri
  int buttonState = digitalRead(PIN_SW);
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    buttonPressTime = millis();
    delay(5); // debounce
  }

  if (buttonState == HIGH && buttonPressed) {
    unsigned long pressDuration = millis() - buttonPressTime;

    if (pressDuration < 800) {
      Serial.println("Mute Toggle");
      bleKeyboard.write(KEY_MEDIA_MUTE);
    } else {
      Serial.println("Play/Pause");
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    }

    buttonPressed = false;
    delay(150);
  }

  delay(5);
}
