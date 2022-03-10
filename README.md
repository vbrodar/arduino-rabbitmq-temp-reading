# Arduino RabbitMQ Data publishing

It is used for publishing temperature data in JSON format from Arduino to RabbitMQ message broker.
Consists of DHT11 sensor and Arduino.

## Arduino wiring 

![Image of how Arduino is wired](https://delightnet.nl/images/arduino/dht11_connection.png)

## Configuration

In order to use it you need to change few variables in the code rest can stay the same.


```
byte mac[] = { 0xXY, 0xXY, 0xXY, 0xXY, 0xXY, 0xXY }; //Arduino's MAC address which should be written on Arduino's sticker

byte ip[] = { 192, 168, x, x }; //Arduino IP address

byte server[] = { 192, 168, x, x }; //Your own dedicated IP address

String host = "192.168.x.x:" + String(port); //IP address of host should be same as server, replace with your own

String auth = ""; //auth should be base64 encoded credentials for example if you base64 encode "guest:guest" you get "Z3Vlc3Q6Z3Vlc3Q=" (dont use square brackets)

```

You can find base64 encoding [here](https://www.base64encode.org/).
