#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
void setup(){
  Serial.begin(115200);
  WiFi.begin("WIFI_NAME", "WIFI_PASSWORD");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}
 
void loop(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Serial.println("WiFi connection successful");
  } else {
    Serial.println("Error in WiFi connection");
  }
 
}
