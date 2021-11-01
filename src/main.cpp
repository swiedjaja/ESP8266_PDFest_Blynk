#include <Arduino.h>
#include <DHTesp.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

char auth[] = "tta2QKEl6B8w064iGIfgSUwHL2vLtwJS";
char ssid[] = "Steff-IoT";
char pass[] = "steffiot123";

/*
  #define D0 16
  #define D1 5 // I2C Bus SCL (clock)
  #define D2 4 // I2C Bus SDA (data)
  #define D3 0
  #define D4 2 // Same as "LED_BUILTIN", but inverted logic
  #define D5 14 // SPI Bus SCK (clock)
  #define D6 12 // SPI Bus MISO
  #define D7 13 // SPI Bus MOSI
  #define D8 15 // SPI Bus SS (CS)
  #define D9 3 // RX0 (Serial console)
  #define D10 1 // TX0 (Serial console)

  #define S3 10
  #define RX0 D9
  #define TX0 D10
*/
#define MAX_CHANNEL 4
#define PIN_DHT11 D3

const uint8 g_arChannel[MAX_CHANNEL] = {D5, D6, D7, D8};
DHTesp dht;
void OnReadSensor();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  for (byte i=0; i<4; i++)
  {
    pinMode(g_arChannel[i], OUTPUT);
    digitalWrite(g_arChannel[i], LOW);    
  }
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
    continue;
  }
  Serial.println("Booting...");
  dht.setup(PIN_DHT11, DHTesp::DHT22);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  OnReadSensor();
  delay(1000);
}

void OnReadSensor()
{
  digitalWrite(LED_BUILTIN, LOW);
   // float h= 50, t= 27;

   float h = dht.getHumidity();
   float t = dht.getTemperature();
   if (dht.getStatus() == DHTesp::ERROR_NONE)
   {
      Serial.printf("Temp: %.2f, Humidity: %.2f\n", t, h);
      Blynk.virtualWrite(V0, h);
      Blynk.virtualWrite(V1, t);
   }
  digitalWrite(LED_BUILTIN, HIGH);
}