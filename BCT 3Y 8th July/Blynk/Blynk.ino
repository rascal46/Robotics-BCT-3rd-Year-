#define BLYNK_TEMPLATE_ID "TMPL3gnmyPBjp"
#define BLYNK_TEMPLATE_NAME "BCT 2"
#define BLYNK_AUTH_TOKEN "_oJHQNAzJaVBOIGUNicQGeOuNs8W51hN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "Galaxy A12 A2AA";
char pass[] = "yapn8271";
#define LED 2

BLYNK_WRITE(V0)   // When button pressed in app
{
  int value1 = param.asInt(); 
  digitalWrite(LED, value1);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
void loop()
{
  Blynk.run();
}