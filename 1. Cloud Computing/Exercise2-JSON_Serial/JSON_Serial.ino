#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"
#include "dht.h"
#define dht_apin 5 // GPIO 5 (D1)

dht DHT;
 
void setup(){
  Serial.begin(115200);
  WiFi.begin("WIFI_NAME", "WIFI_PASSWORD");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}
 
void loop(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Serial.println("WiFi connection successful");
    // read from DHT11 if Wifi is connected
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(5000);
  } else {
    Serial.println("Error in WiFi connection");
  }

  Serial.println("——————");
 
  char JSONMessage[] = " {\"SensorType\": \"Temperature\", \"Value\": 10}"; //Original message
  Serial.print("Initial string value: ");
  Serial.println(JSONMessage);
 
  StaticJsonBuffer<300> JSONBuffer;   //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(JSONMessage); //Parse message
 
  if (!parsed.success()) {   //Check for errors in parsing
 
    Serial.println("Parsing failed");
    delay(5000);
    return;
 
  }
 
  const char * sensorType = parsed["SensorType"]; //Get sensor type value
  int value = parsed["Value"];    //Get value of sensor measurement
 
  Serial.println(sensorType);
  Serial.println(value);
 
  Serial.print("Final string value: ");
 
  for (int i = 0; i < 31; i++) { //Print the modified string, after parsing
 
    Serial.print(JSONMessage[i]);
 
  }
 
  Serial.println();
  delay(5000);
 
}
