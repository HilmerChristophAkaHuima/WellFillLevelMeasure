#include <Arduino.h>
#ifndef CONFIG_H
#define CONFIG_H

struct Config{
  byte mac[6];
  byte ip[4];
  byte mqttServerIp[4];
  char mqttUsername[50];
  char mqttPassword[50];
};

extern struct Config config;
#endif
