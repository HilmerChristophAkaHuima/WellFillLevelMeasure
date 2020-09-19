#include <SPI.h>
#include <Ethernet.h>
#include <NewPing.h>
#include <PubSubClient.h>

byte mac[] = {};   // Be sure this address is unique in your network

IPAddress ip();

EthernetClient client;

const char* mqtt_server = "";
PubSubClient pubClient(client);

void reconnect() {
  // Loop until we're reconnected
  while (!pubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (pubClient.connect(1, "", "")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(pubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

int zahl = 1;
void(* resetFunc) (void) = 0;
 
void setup() {     
  Serial.begin(9600);
  delay(200);

  Ethernet.begin(mac, ip);
  Serial.println("Ethernet ready");
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);

  reconnect();
}

void loop() 
{
  if (!pubClient.connected()) {
    reconnect();
  }

  String str = String(zahl+1);
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);

    pubClient.publish("waldBrunnen", char_array, false);
  
  Serial.println(zahl);
  Serial.println("A");
  delay(1000);               
  Serial.println("B");
  delay(1000);               
  Serial.println("Now we are Resetting Arduino Programmatically");
  Serial.println();
  delay(1000);
  resetFunc();
  Serial.println("Arrduino will never reach there.");
 
}
