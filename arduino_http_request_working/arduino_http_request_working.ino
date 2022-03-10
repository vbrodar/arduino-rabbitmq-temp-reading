#include <Ethernet.h>
#include <SPI.h>
//#include <ArduinoJson.h> //Arduino json library
#include <DHT.h> //Including temp sensor library

#define DHTPIN 2 //Defining Arduino digital pin being used for data reading


byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xF2, 0xE4 };  //Arduino MAC address
byte ip[] = { 192, 168, 137, 111 }; //Arduino IP address
byte server[] = { 192, 168, 137, 194 }; // Local ip address
String postEndpoint = "/api/exchanges/%2f/arduinoTemperature/publish/";
String protocolVersion = "HTTP/1.1";
int port = 15672; //Port 8888 for Netcat, port 15672 for RabbitMQ
String host = "192.168.137.194:" + String(port);
//base64 encoded noviuser:noviuser123
String auth = "bm92aXVzZXI6bm92aXVzZXIxMjM=";

DHT dht(DHTPIN,DHT11);
//StaticJsonDocument<200> doc;
EthernetClient client;


void setup()
{
  Serial.begin(9600);
  dht.begin(); //beginning of dht sensor
  Ethernet.begin(mac, ip);
  Serial.println("Connecting...");
  delay(1000);

}

void loop()
{
  float temp = dht.readTemperature(); //measure temperature
  String stringTemp = String(temp); //Converting temperature to string
  String queryString = "{\"properties\":{}, \"routing_key\":\"sensorQueue\",\"payload\":'{\"temperature\": ";
  queryString += temp;
  queryString += ",\"ID\":\"ee1e0a0d-8fcb-4670-8dad-6bb8be846411\"}',\"payload_encoding\":\"string\"}}}";
   
  if(isnan(temp)){ //Checking if reading data fails
    Serial.println("Unable to read data from sensor!");
    return;
  } 
  
  
  if (client.connect(server, port)) {
    Serial.println("Connected");
    Serial.print("Temperature is: ");
    Serial.println(temp);
   
    Serial.println(queryString.length());
    client.println("POST " + postEndpoint + " " + protocolVersion + "\r\n" + "Host: " + host + "\r\n" + "Authorization: Basic " + auth + "\r\n" + "Content-Type: application/json" + "\r\n" + "Content-Length: " + queryString.length() +"\r\n");
    client.println();
    client.print(queryString);
    Serial.println("Posted sensor JSON data: " + queryString);
  } else {
    Serial.println("Connection failed!");
  }
 /* if (client.available()) {
    char c = client.read();
    Serial.print(c);
  } */

  if (!client.connected()) {
    Serial.println("\r");
    Serial.println("disconnecting.");
    client.stop();
    for(;;);
  }
  delay(5000);
}
