#include <SPI.h>
#include <WiFi.h>
//#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {0x90, 0xA2, 0xDA, 0x0D, 0x1D, 0xB5};
IPAddress ip(10, 26, 101, 153);
char server[] = "influx.itu.dk";

char ssid[] = "NETWORK_NAME";
char pass[] = "NETWORK_PASSWORD";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned long lastMillis = 0;



// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Recieved Message!");

} // void callback



void setup()
{

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

 while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 7 seconds for connection:
    delay(7000);
  }

  if (client.connect("arduino","USER_NAME", "PASSWORD")) {
    Serial.println("MQTT Connected");
    client.subscribe("topic/test");
  }else{
    Serial.println(client.state());
  }
}
void loop()
{
   client.loop();

   if (millis() - lastMillis > 6000) {
    lastMillis = millis();
    client.publish("topic/test", "hello World");
   }
}
