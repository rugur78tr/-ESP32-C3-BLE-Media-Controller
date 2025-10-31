🧭 ESP32-C3 BLE Media Controller

⚡ ESP32-C3 BLE Media Controller — Bağlantı Şeması
🧩 Malzemeler:

ESP32-C3 SuperMini

Rotary Encoder (3 pinli sinyal + 2 pinli buton)

1x Harici LED

1x 220Ω direnç

Breadboard ve jumper kablolar

🔌 Bağlantı Şeması (metin olarak)
Bileşen	ESP32-C3 Pin	Açıklama
Rotary Encoder A	GPIO 4	Encoder sinyali A
Rotary Encoder B	GPIO 5	Encoder sinyali B
Encoder Butonu (SW)	GPIO 6	Basıldığında Mute/Play komutu gönderir
Harici LED (+)	GPIO 2	Durum LED’i (bağlantı / bekleme)
Harici LED (-)	GND	Direnç (220Ω) üzerinden bağla
ESP32 Dahili LED	GPIO 8 (çoğu ESP32-C3 SuperMini’de yerleşik)	Kodda eşzamanlı yanar
VCC	3V3	Güç
GND	GND	Ortak toprak
💡 LED Durumları
Durum	LED Davranışı
Güç verildi, bekliyor	Yanıp sönüyor
Bluetooth bağlı	Sürekli yanıyor
PC bağlantısı kesildi	Tekrar yanıp sönmeye başlar
🧠 Proje Özeti (README / GitHub için)
🇹🇷 Türkçe Açıklama

Bu proje, ESP32-C3 SuperMini kullanarak yapılan bir Bluetooth Medya Denetleyici (BLE Keyboard) uygulamasıdır.
Cihaz, bilgisayarınıza Bluetooth klavye olarak bağlanır ve

Rotary encoder ile ses seviyesini artırıp azaltabilir,

Butona basarak sesi kapatabilir (Mute) veya çalmayı durdurup başlatabilir,

Bağlantı durumuna göre LED yanıp sönme efektleriyle kullanıcıya görsel geri bildirim sağlar.

Özellikler:

ESP32-C3 BLE desteği (NimBLE tabanlı)

LED durum göstergesi (harici + dahili LED senkron)

Düşük güç tüketimi

Windows / macOS / Linux desteği

Arduino IDE uyumlu

🇬🇧 English Description

This project is a Bluetooth Media Controller (BLE Keyboard) built with the ESP32-C3 SuperMini.
Once powered on, it waits for Bluetooth pairing while blinking LEDs.
When connected, LEDs stay solid, and the encoder controls the PC volume via Bluetooth HID.
The push button toggles Mute or Play/Pause functions.

Features:

ESP32-C3 BLE Keyboard (NimBLE-based)

Dual LED indicator (external + onboard LED)

Low power, fast connection

Works with Windows, macOS, Linux

Arduino IDE compatible

🇹🇷 Türkçe Açıklama
🎯 Proje Özeti

Bu proje, ESP32-C3 SuperMini kullanarak bir Bluetooth (BLE) medya denetleyicisi oluşturur.
Cihaz, bir rotary encoder (döner buton) aracılığıyla bilgisayarın sesini kontrol eder.
Ayrıca bir buton ile mute (sessize alma) ve play/pause (oynat/duraklat) işlevleri sunar.

⚙️ Özellikler

🔊 Rotary encoder ile ses açma/kısma

🔇 Butona kısa basma → Mute (sessize al)

⏯️ Butona uzun basma → Play / Pause

💡 LED göstergesi:

Güç verildiğinde ve bağlantı yokken: LED yanıp söner

Bilgisayara bağlanınca: LED sabit yanar

Dahili LED (aktif LOW) ve harici LED senkronize çalışır

🔋 Düşük güç tüketimli BLE (Bluetooth Low Energy) bağlantısı

🧩 Donanım Bağlantıları
Bileşen	ESP32-C3 GPIO	Açıklama
Encoder CLK	2	Ses kontrolü
Encoder DT	3	Ses kontrolü
Encoder SW	4	Buton (Mute / Play-Pause)
Harici LED	10	Bağlantı durumu göstergesi
Dahili LED	8	Bağlantı durumu göstergesi (aktif LOW)
🧠 Kullanılan Kütüphaneler

wakwak-koba / ESP32-NimBLE-Keyboard

NimBLE-Arduino (ESP32 çekirdeği içinde dahili olarak bulunur)

🔧 Kurulum

Arduino IDE > Araçlar > Kart: ESP32C3 Dev Module seçin

Aşağıdaki kütüphaneyi yükleyin:
https://github.com/wakwak-koba/ESP32-NimBLE-Keyboard

Yukarıdaki kodu .ino dosyası olarak yükleyin.

Cihazı bilgisayarınıza bağlayın → Bluetooth ayarlarından ESP32-C3 Media Controller olarak eşleştirin.

🖥️ Kullanım

Encoder’ı saat yönünde çevirin → Ses artar

Encoder’ı saat yönünün tersine çevirin → Ses azalır

Encoder butonuna kısa basın → Mute

Encoder butonuna uzun basın → Play/Pause

LED sabit yanıyorsa → Bluetooth bağlantısı aktif 🔵

LED yanıp sönüyorsa → Cihaz bağlantı bekliyor ⚪

🧑‍💻 Geliştirici Notu

Bu proje, T-vK ve wakwak-koba kütüphanelerinin kararlı kombinasyonunu temel alır.
ESP32-C3 üzerinde düşük bellek kullanımı ve yüksek stabilite sağlar.

🇬🇧 English Description
🎯 Project Summary

This project creates a Bluetooth (BLE) media controller using an ESP32-C3 SuperMini.
It acts as a BLE keyboard device that controls your PC’s volume, mute, and play/pause functions through a rotary encoder.

⚙️ Features

🔊 Volume Up / Down using rotary encoder

🔇 Short press → Mute toggle

⏯️ Long press → Play / Pause

💡 LED Indicator:

Before pairing: LED blinks slowly

After connection: LED stays ON

Internal (active LOW) and external LEDs work in sync

🔋 Low power BLE connection for media key emulation

🧩 Hardware Connections
Component	ESP32-C3 GPIO	Description
Encoder CLK	2	Volume control
Encoder DT	3	Volume control
Encoder SW	4	Button input
External LED	10	Connection indicator
Internal LED	8	Onboard LED (active LOW)
🧠 Libraries Used

wakwak-koba / ESP32-NimBLE-Keyboard

Built-in NimBLE-Arduino library (included in ESP32 core)

🔧 Setup

In Arduino IDE:

Board: ESP32C3 Dev Module

Install library:
https://github.com/wakwak-koba/ESP32-NimBLE-Keyboard

Upload the .ino file to your ESP32-C3.

Pair your computer with ESP32-C3 Media Controller via Bluetooth.

🖥️ Usage

Rotate clockwise → Volume Up

Rotate counterclockwise → Volume Down

Short press → Mute toggle

Long press → Play / Pause

LED ON → Connected 🔵

LED blinking → Waiting for connection ⚪

🧑‍💻 Developer Note

This project is based on the T-vK BLE Keyboard concept with NimBLE optimization, ensuring stable operation and low resource usage on ESP32-C3 boards.
