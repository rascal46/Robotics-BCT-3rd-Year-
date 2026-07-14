#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "XXXX";
const char* password = "xxxx";

String apiKey = "CPQIXBZZYDDZ31W8";    
const char* server = "http://api.thingspeak.com/update";


#define DHTPIN 4
#define DHTTYPE DHT11

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

// -------- DHT11 --------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C  | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = server;
    url += "?api_key=" + apiKey;
    
    url += "&field1=" + String(temperature);
    url += "&field2=" + String(humidity);

    http.begin(url);
    int httpCode = http.GET();
    http.end();

    Serial.println("Data sent to ThingSpeak");
  }

  delay(15000);   // ThingSpeak minimum delay
}
