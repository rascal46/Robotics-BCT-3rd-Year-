#define BLYNK_TEMPLATE_ID "TMPL3JdPPV2ea"
#define BLYNK_TEMPLATE_NAME "BCT 14th"
#define BLYNK_AUTH_TOKEN "jQXaQgMGYLf4XcFtMHEh3QeDK3KGo2UI"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "XXXXX";
const char* pass = "xxxxxx"; 

#define MQ2_PIN 34

BlynkTimer timer;
bool alertSent = false;

void sendGasData()
{
  int gasValue = analogRead(MQ2_PIN);

  // Convert to percentage
  int gasPercent = map(gasValue, 0, 4095, 0, 100);
  gasPercent = constrain(gasPercent, 0, 100);

  Serial.print("Gas Percentage: ");
  Serial.println(gasPercent);

  Blynk.virtualWrite(V0, gasPercent);

  // Alert if gas > 60%
  if (gasPercent > 10 && !alertSent)
  {
    Blynk.logEvent("gas_alert", "⚠ High Gas Level Detected!");
    alertSent = true;
  }

  if (gasPercent < 10)
  {
    alertSent = false;   // Reset alert
  }
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendGasData);  // Send every 2 sec
}
void loop()
{
  Blynk.run();
  timer.run();
}
