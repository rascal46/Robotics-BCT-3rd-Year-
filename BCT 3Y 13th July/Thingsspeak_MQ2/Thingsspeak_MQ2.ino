#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "XXXX";
const char* password = "xxxx";

String apiKey = "3LRZNA5T4TPXGLDL";    
const char* server = "http://api.thingspeak.com/update";

#define MQ2_PIN 34
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {

  // -------- MQ2 --------
  int gasValue = analogRead(MQ2_PIN);

 // Convert raw value (0–4095) to percentage (0–100)
  int gasPercent = map(gasValue, 0, 4095, 0, 100);

  // Limit between 0 and 100
  gasPercent = constrain(gasPercent, 0, 100);


  // -------- DHT11 --------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Gas: ");
  Serial.print(gasPercent);
  Serial.print("%  | Temp: ");
  Serial.print(temperature);
  Serial.print("°C  | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = server;
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(gasPercent);
    url += "&field2=" + String(temperature);
    url += "&field3=" + String(humidity);

    http.begin(url);
    int httpCode = http.GET();
    http.end();

    Serial.println("Data sent to ThingSpeak");
  }

  delay(15000);   // ThingSpeak minimum delay
}
