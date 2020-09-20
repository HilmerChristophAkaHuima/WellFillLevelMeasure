#include <NewPing.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "config.h"

#define TRIGGER_PIN  5
#define ECHO_PIN     6
#define MAX_DISTANCE 500

char topic[] = "waldBrunnen";

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
EthernetClient client;
PubSubClient pubClient(config.mqttServerIp, 1883, client);

void reconnect() {
  // Loop until we're reconnected
  while (!pubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (pubClient.connect(1, config.mqttUsername, config.mqttPassword)) {
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

void(* resetFunc) (void) = 0;
 
void setup() {     
  Serial.begin(9600);
  delay(200);

  Ethernet.begin(config.mac, config.ip);
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
  
  int distance = sonar.ping_cm();
  if(distance > 0){
    String str = String(distance);
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
  
    pubClient.publish(topic, char_array, false);
  }
  
  Serial.println(distance);
  delay(100);
  resetFunc(); 
}
