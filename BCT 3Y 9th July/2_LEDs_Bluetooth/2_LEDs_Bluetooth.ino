#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define LED_PIN1 2
#define LED_PIN2 4

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN1, OUTPUT);
  digitalWrite(LED_PIN1, LOW);

   pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN2, LOW);

  // Bluetooth device name
  SerialBT.begin("ESP32_LED2");

  Serial.println("Bluetooth Started!");
  Serial.println("Device Name: ESP32_LED2");
}

void loop() {

  if (SerialBT.available()) {

    char cmd = SerialBT.read();

    Serial.print("Received: ");
    Serial.println(cmd);

    if (cmd == '1') {
      digitalWrite(LED_PIN1, HIGH);
      SerialBT.println("LED ON");
    }

    else if (cmd == '0') {
      digitalWrite(LED_PIN1, LOW);
      SerialBT.println("LED OFF");
    }

    else if (cmd == '2') {
      digitalWrite(LED_PIN2, HIGH);
      SerialBT.println("LED ON");
    }

    else if (cmd == '3') {
      digitalWrite(LED_PIN2, LOW);
      SerialBT.println("LED OFF");
    } 
  }
}