#include <ESP8266WiFi.h>

const char* ssid = "Unspecified";
const char* wifiPassword= "Unspecified";

void setup() 
{
  Serial.begin(115200);
  
  Serial.print("Wifi connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,wifiPassword);

  Serial.println();
  Serial.print("Connecting");
  while( WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Wifi Connected!!");
  Serial.println("NodeMCU IP Adress:");
  Serial.println(WiFi.localIP());
  
}

void loop() 
{


}
