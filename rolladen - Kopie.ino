#include <HomeSpan.h>
#include <WiFi.h>

// WLAN-Zugangsdaten (hier anpassen!)
#define WIFI_SSID "XXXXXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXXXXXXXXXXXX"
#define SETUP_CODE "8-digit-code"

// GPIO-Pins für die Relais
#define PIN_UP 12   // GPIO für Hoch
#define PIN_DOWN 32 // GPIO für Runter
#define PIN_STOP 22 // GPIO für Stopp (Hinweis: GPIO 36 ist oft nur Eingang, ggf. zu z. B. 33 ändern)

// Schalter-Dienst für Hoch, Runter, Stopp
struct ControlSwitch : Service::Switch {
  SpanCharacteristic *on;
  int type; // 1 = Hoch, 2 = Runter, 3 = Stopp

  ControlSwitch(int t) : type(t) {
    on = new Characteristic::On();
    new Characteristic::Name(type == 1 ? "Rollladen Hoch" : type == 2 ? "Rollladen Runter" : "Rollladen Stopp");
  }

  boolean update() {
    if (on->getNewVal()) {
      // Alle Pins zunächst ausschalten
      digitalWrite(PIN_UP, LOW);
      digitalWrite(PIN_DOWN, LOW);
      digitalWrite(PIN_STOP, LOW);

      // 1-Sekunden-Impuls auf dem entsprechenden Pin
      if (type == 1) {
        // Hoch
        digitalWrite(PIN_UP, HIGH);
        delay(1000); // 1 Sekunde warten
        digitalWrite(PIN_UP, LOW);
      } else if (type == 2) {
        // Runter
        digitalWrite(PIN_DOWN, HIGH);
        delay(1000); // 1 Sekunde warten
        digitalWrite(PIN_DOWN, LOW);
      } else if (type == 3) {
        // Stopp
        digitalWrite(PIN_STOP, HIGH);
        delay(1000); // 1 Sekunde warten
        digitalWrite(PIN_STOP, LOW);
      }

      // Schalter zurücksetzen (Taster-Verhalten)
      on->setVal(false);
    }
    return true;
  }
};

void setup() {
  Serial.begin(115200);

  // WLAN-Verbindung herstellen
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Verbinde mit WLAN...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWLAN verbunden!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());

  // GPIO-Pins initialisieren
  pinMode(PIN_UP, OUTPUT);
  pinMode(PIN_DOWN, OUTPUT);
  pinMode(PIN_STOP, OUTPUT); // Hinweis: Prüfen, ob GPIO 36 Ausgabe unterstützt
  digitalWrite(PIN_UP, LOW);   // Start: Alle aus
  digitalWrite(PIN_DOWN, LOW);
  digitalWrite(PIN_STOP, LOW);

  // HomeSpan initialisieren
  homeSpan.begin(Category::Switches, "Rollladen Steuerung");

  // HomeSpan mit WLAN-Zugangsdaten informieren
  homeSpan.setWifiCredentials(WIFI_SSID, WIFI_PASSWORD);
  homeSpan.setPairingCode(SETUP_CODE);

  // Schalter Hoch
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Name("Hoch Schalter");
  new Characteristic::Manufacturer("DIY");
  new Characteristic::SerialNumber("0001");
  new Characteristic::Model("Rollladen V1");
  new Characteristic::FirmwareRevision("1.0");
  new Characteristic::Identify(); // Identify hinzufügen, um Warnung zu beheben
  new ControlSwitch(1);

  // Schalter Runter
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Name("Runter Schalter");
  new Characteristic::Manufacturer("DIY");
  new Characteristic::SerialNumber("0002");
  new Characteristic::Model("Rollladen V1");
  new Characteristic::FirmwareRevision("1.0");
  new Characteristic::Identify(); // Identify hinzufügen
  new ControlSwitch(2);

  // Schalter Stopp
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Name("Stopp Schalter");
  new Characteristic::Manufacturer("DIY");
  new Characteristic::SerialNumber("0003");
  new Characteristic::Model("Rollladen V1");
  new Characteristic::FirmwareRevision("1.0");
  new Characteristic::Identify(); // Identify hinzufügen
  new ControlSwitch(3);
}

void loop() {
  homeSpan.poll();
}