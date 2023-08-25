#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
const char* ssid = "hamodi";
const char* password = "momen45321";
const char* Firebase_Host = "braille-printer-b923b-default-rtdb.asia-southeast1.firebasedatabase.app";
const char* Firebase_Auth = "4V7O6OimmFsUue4h6RNUsVtaWY3S3rSdZsjdbaqd";
FirebaseData firebaseData;

#define RXPin        D7  // Serial Receive pin
#define TXPin        D8   // Serial Transmit pin
//RS485 control

SoftwareSerial RS485Serial(RXPin, TXPin); // RX, TX

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
  RS485Serial.write("WiFi connected");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(9600);
  RS485Serial.begin(9600);   // set the data rate
  connectToWiFi();
  Firebase.begin(Firebase_Host, Firebase_Auth);
  
}

String getDataFirebase(String node)
{
  if (Firebase.getString(firebaseData, node)) {
    // Check for success
    if (firebaseData.dataType() == "string") {
      Serial.print("Read data: ");
      Serial.println(firebaseData.stringData());
      return firebaseData.stringData();
    }
    else {
      Serial.println("Failed to read data");

    }
  } else {
    Serial.println("Error fetching data");
  }
  return "";
}

void setDataFirebase(String node, String newValue)
{
  if (Firebase.setString(firebaseData, node, newValue)) {
    Serial.println("Value updated successfully");
  } else {
    Serial.println("Error updating value");
  }
}
bool sentMsg = true; 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String msg = getDataFirebase("/msg")+"\n";
    String statusMsg = getDataFirebase("/status");

    if(statusMsg == "new" && sentMsg)
    {
      RS485Serial.write(msg.c_str());
      sentMsg=false; 
    }
    if (RS485Serial.available())
    {
      String incoming =  RS485Serial.readString();
      Serial.print(incoming.c_str());
      if(strcmp(incoming.c_str(),"recived")==0)
      {
        setDataFirebase("/status", "in progress");
      }
      else if(strcmp(incoming.c_str(),"not recived")==0)
      {
        sentMsg=true;
      }
      else if(strcmp(incoming.c_str(),"finished")==0)
      {
        setDataFirebase("/status", "finished");
        sentMsg=true;
      }
      
    }
  }
  else
  {
    Serial.println("No WiFi connection Reconnect");
    connectToWiFi();
  }
}
//
//  delay(100);
  //***********************************************************************************
 
//if (Serial.available()) { // Check if there is any data available from the serial port
//    String outgoing =  Serial.readString(); // Read the outgoing string from the serial port
//    Serial.print(outgoing); // Print the outgoing string to the serial port for debugging
//    RS485Serial.write(outgoing.c_str()); // Send a response back to the Bluetooth module
//  }
//
//  if (RS485Serial.available()) { // Check if there is any data available from the Bluetooth module
//    String incoming =  RS485Serial.readString(); // Read the incoming string from the Bluetooth module
//    Serial.print(incoming.c_str()); // Print the received string to the serial port for debugging
//  }
