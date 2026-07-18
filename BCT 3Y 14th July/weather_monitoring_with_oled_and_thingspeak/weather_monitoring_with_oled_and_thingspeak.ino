#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
//#include <Adafruit_SSD1306.h>

// ------------ OLED ------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ------------ WiFi ------------
const char* ssid = "moupia";
const char* password = "abcdefgh";

// ------------ ThingSpeak ------------
String apiKey = "YOUR_WRITE_API_KEY";
const char* server = "http://api.thingspeak.com/update";

// ------------ DHT11 ------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ------------ Sensors ------------
#define RAIN_SENSOR 34
#define SMOKE_SENSOR 35

void setup()
{
  Serial.begin(115200);

  dht.begin();

  Wire.begin(22,21);

  if(!display.begin(0x3C, true))
  {
    Serial.println("SH1106 OLED Not Found");
    while(1);
  }

  display.clearDisplay();
  display.display();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
}

void loop()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int rain = analogRead(RAIN_SENSOR);
  int smoke = analogRead(SMOKE_SENSOR);

  String rainStatus;

  if(rain < 2000)
    rainStatus = "RAIN";
  else
    rainStatus = "NO RAIN";

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
//display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.print("Temp : ");
  display.print(temp);
  display.println(" C");

  display.print("Humidity : ");
  display.print(hum);
  display.println(" %");

  display.print("Rain : ");
  display.println(rainStatus);

  display.print("Rain Val : ");
  display.println(rain);

  display.print("Smoke : ");
  display.println(smoke);

  display.display();

  // Serial Monitor
  Serial.println("----------------------");
  Serial.print("Temperature : ");
  Serial.println(temp);

  Serial.print("Humidity : ");
  Serial.println(hum);

  Serial.print("Rain : ");
  Serial.println(rain);

  Serial.print("Smoke : ");
  Serial.println(smoke);

  // ThingSpeak
  if(WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;

    String url = String(server);
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(temp);
    url += "&field2=" + String(hum);
    url += "&field3=" + String(rain);
    url += "&field4=" + String(smoke);

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("ThingSpeak Response : ");
    Serial.println(httpCode);

    http.end();
  }

  delay(20000);
}