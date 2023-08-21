#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//#include <Arduino_JSON.h>
#include <FirebaseArduino.h>
// Network SSID
const char* ssid = "hamodi";
const char* password = "momen45321";
const char* Firebase_Host = "braille-printer-b923b-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* Firebase_Auth = "4V7O6OimmFsUue4h6RNUsVtaWY3S3rSdZsjdbaqd"; 
unsigned long timerDelay = 10000;
unsigned long lastTime = 0;
String jsonBuffer;

void connectToWiFi()
{
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}

/************************************************************/
 String httpGETRequest(const char* serverName)
 {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  
  return payload;
}

/************************************************************/
void setup() {
  
  Serial.begin(9600);
  connectToWiFi();
  Firebase.begin(Firebase_Host, Firebase_Auth);
  delay(10);
  
}
int pId=1;
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Declare an object of class HTTPClient
//    HTTPClient http;
//    WiFiClient client;
//    // Specify request destination
//    String url = "http://jsonplaceholder.typicode.com/users/"+pId;
//    http.begin(client,url);
//    
//    // Send the request
//    pId+=1;
//    Serial.println("Request URL:" + url);
//    int httpCode = http.GET();
//    
//    // Check the returning code
//    if (httpCode > 0) {
//      // Get the request response payload
//      String payload = http.getString();
//      // Print the response payload
//      Serial.println(payload);
//
//    } else {
//      Serial.print("Error: status code ");
//      Serial.println(httpCode);
//    }
//    
//    // Close connection
//    http.end();
//  }
//
//  // Send a request every 30 seconds
//  delay(30000);

Serial.print(Firebase.getString("msg") + "\n");
delay(1000);
  }
}
