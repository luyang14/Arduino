#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
extern "C" {
#include "user_interface.h"
}

Adafruit_BME280 bme; // I2C
Ticker ticker;

#define DELAYMS (1000 * 60 * 1)
#define LEDPIN (13)

#define VS 10
static unsigned int upCount = 0L;

static unsigned int counter = 0;
static float vSamples[VS] = {0};
static float voltage = 0.0;

void measureVoltage(){
  unsigned int a;
  float sum = 0.0;
  int adcv =  system_adc_read(); // from TOUT (4.2V - 470K - 150K - GND)
  float v = (float)adcv / (1024/4.2);

  vSamples[counter%VS] = v;
  counter++;
  unsigned int ooo = (counter<VS? counter:VS);
  for(a=0; a<ooo; a++){
    sum += vSamples[a];    
  }
  voltage = sum / ooo;

  String info = "+" + String(v) + "V (avg " + String(voltage) +")";
  Serial.println(info);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start collection");

  pinMode(LEDPIN, OUTPUT);

  char *ssid = "ms101";
  char *password = "sekitakovich";

  wifi_set_sleep_type(LIGHT_SLEEP_T);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000 * 1);
    Serial.print(".");
  }
  Serial.println("");

  bme.begin(0x76);

  ticker.attach(1.0 * 5, measureVoltage);
}

void loop() {
  delay(DELAYMS);

  float t = bme.readTemperature();
  float p = bme.readPressure() / 100.0F;
  float h = bme.readHumidity();
//  float v = 0.0;
//
//  int adcv =  system_adc_read(); // from TOUT (4.2V - 470K - 150K - GND)
//  v = (float)adcv / (1024/4.2);

  float v = voltage;
  
  digitalWrite(LEDPIN, HIGH);

  String nickname = "sekitakovich";
  String info = "t=" + String(t) + "&h=" +  String(h) + "&p=" + String(p) + "&v=" + String(v) + "&nickname=" + nickname + "&up="+ upCount++;
  Serial.println(info);

  char *host = "www.klabo.co.jp";
  WiFiClient client;
  int httpPort = 80;
  if (client.connect(host, httpPort)) {
    String url = String("/tph.php?")  + info;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

    delay(1000);

    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }

  digitalWrite(LEDPIN, LOW);
}
