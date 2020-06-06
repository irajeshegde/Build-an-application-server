#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "dht.h" // Library
#define dht_apin 5 // GPIO 5 (D1)

dht DHT;

void setup() {
  Serial.begin(115200); // serial monitor
  WiFi.begin("Brahma3", "Plutonine");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  delay(500);// Delay system boot
  Serial.println("ESP8266 with DHT11");
  delay(1000);//Wait before accessing sensors
}

void loop() {
  //DH11 - Read and Print
  DHT.read11(dht_apin);
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println("%");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");

  String url;
  url = "http://192.168.0.127:3000/" + String(DHT.temperature) + "/" + String(DHT.humidity);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient
    http.begin(url);      //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    int httpCode = http.POST("");   //Send the request
    String payload = http.getString();                  //Get the response payload
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(30000);  //Send a request with required delay

}
