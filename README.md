# Apple-Home-Roller-shutter-control

## Deutsch

Dieses Projekt ermöglicht die Steuerung eines Rollladens über Apple HomeKit mithilfe eines ESP32 und der HomeSpan-Bibliothek.  
Der ESP32 verbindet sich mit dem WLAN und stellt drei HomeKit-Schalter bereit:

- **Rollladen Hoch**
- **Rollladen Runter**
- **Rollladen Stopp**

Jeder Schalter arbeitet wie ein Taster: Beim Aktivieren wird das jeweilige Relais bzw. der jeweilige Transistorausgang für eine Sekunde geschaltet und anschließend automatisch wieder deaktiviert. Dadurch können vorhandene Rollladensteuerungen mit separaten Eingängen für Hoch, Runter und Stopp angesteuert werden.

## Hardware-Aufbau

Für die Hardware wurde eine vorhandene **Elero-Fernbedienung** verwendet. Diese besitzt drei Tasten für **Hoch**, **Runter** und **Stopp**.  
Die Tasten melden dem internen IC der Fernbedienung ein Signal, sobald der jeweilige Eingang gegen **GND** geschlossen wird.

Diese Tastensignale wurden parallel abgegriffen und jeweils über einen **2N2222-Transistor** geschaltet.  
Der ESP32 steuert die Transistoren an. Sobald ein Transistor aktiviert wird, zieht er das entsprechende Tastensignal auf **GND**. Dadurch erkennt die Fernbedienung einen Tastendruck und fährt den Rollladen hoch, runter oder stoppt die Bewegung.

Somit kann die originale Fernbedienung weiterhin genutzt werden, während die Steuerung zusätzlich über Apple HomeKit möglich ist.

### Verwendete GPIOs

- GPIO 12: Hoch
- GPIO 32: Runter
- GPIO 22: Stopp

Vor der Verwendung müssen WLAN-SSID, WLAN-Passwort und der HomeKit-Setup-Code im Code angepasst werden.

---

## English

This project provides a roller shutter control system using an ESP32 and the HomeSpan library for Apple HomeKit integration.  
The ESP32 connects to Wi-Fi and creates three HomeKit switches:

- **Roller Shutter Up**
- **Roller Shutter Down**
- **Roller Shutter Stop**

Each switch works like a push button: when activated, the corresponding relay or transistor output is switched for one second and then automatically turned off again. This makes it suitable for controlling existing roller shutter systems with separate inputs for up, down and stop.

## Hardware Setup

For the hardware, an existing **Elero remote control** was used. The remote has three buttons for **up**, **down** and **stop**.  
Each button sends a signal to the internal IC of the remote control as soon as the corresponding input is connected to **GND**.

These button signals were tapped in parallel and connected to **2N2222 transistors**.  
The ESP32 controls these transistors. When a transistor is activated, it pulls the corresponding button signal to **GND**. As a result, the remote control detects a button press and moves the roller shutter up, down or stops it.

This allows the original remote control to remain fully usable, while also enabling control through Apple HomeKit.

### Used GPIOs

- GPIO 12: Up
- GPIO 32: Down
- GPIO 22: Stop

Before uploading the code, the Wi-Fi SSID, Wi-Fi password and HomeKit setup code must be configured in the source code.
