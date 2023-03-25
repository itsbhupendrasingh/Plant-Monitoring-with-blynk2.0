

#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_TEMPLATE_NAME "Template ID"
#define BLYNK_AUTH_TOKEN "Auth Token"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "**********";
char pass[] = "**********";

BlynkTimer timer;

#define soil 13
#define waterPump 12
WidgetLED pump(V1);

float soilLevel, soilR;
WidgetLCD vLcd(V2);
void SMESensor()
{
  readSoil();
  if(soilLevel>=80)
  {    
    digitalWrite(waterPump, LOW);
    vLcd.print(0,0,"Water Pump OFF");
    pump.off();
  }
  
 if(soilLevel<20)
  {    
    digitalWrite(waterPump, HIGH);
    vLcd.print(0,0, "Water Pump ON ");
    pump.on();
  }
}
void readSoil()
{
  soilR=analogRead(soil);  
  Serial.println(soilR);
  soilLevel=map(soilR, 0, 1024, 200,0); // adjust soil level here
  Serial.println(soilLevel);
  Blynk.virtualWrite(V0, soilLevel);
  delay(1000);
}
void setup()
{
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, LOW);
  delay(100);

  Blynk.begin(auth, ssid, pass);
  delay(1000);
  timer.setInterval(1000L, SMESensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
