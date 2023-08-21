#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

const char* ssid = "hamodi";
const char* password = "momen45321";
const char* Firebase_Host = "braille-printer-b923b-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* Firebase_Auth = "4V7O6OimmFsUue4h6RNUsVtaWY3S3rSdZsjdbaqd";
FirebaseData firebaseData;

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
  Serial.println(WiFi.localIP());
}


void setup() {
  
  Serial.begin(9600);
  connectToWiFi();
  delay(10);
  Firebase.begin(Firebase_Host, Firebase_Auth);
  
}

void getDataFirebase(String node)
{
  if (Firebase.getString(firebaseData, node)) {
    // Check for success
    if (firebaseData.dataType() == "string") {
      Serial.print("Read data: ");
      Serial.println(firebaseData.stringData());
    } else {
      Serial.println("Failed to read data");
    }
  } else {
    Serial.println("Error fetching data");
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    getDataFirebase("/msg");
  }
  delay(1000); 
  //***********************************************************************************
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

void getDataHTTP()
{
  if (WiFi.status() == WL_CONNECTED) {
    // Declare an object of class HTTPClient
    HTTPClient http;
    WiFiClient client;
    // Specify request destination
    String url = "http://jsonplaceholder.typicode.com/users/1";
    http.begin(client,url);
    
    // Send the request
    Serial.println("Request URL:" + url);
    int httpCode = http.GET();
    
    // Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      // Print the response payload
      Serial.println(payload);

    } else {
      Serial.print("Error: status code ");
      Serial.println(httpCode);
    }
    
    // Close connection
    http.end();
  }
}
/************************************************************/
