# WellFillLevelMeasure
WellFillMeasureDevice measures the distance between the water level in the well and the ultrasonic sensors and passes it on to the mqtt server.

Hardware: 
    Ultrasonic-Sensor: JSN-SR04T 2.0,
    Ethernetshield: W5100 Ethernet-Shield 5100,
    Arduino: Arduino Uno R3

External Libraries:
    NewPing
    PubSubClient

Usage: 
    Change the name of config.template.cpp to config.cpp.
    Add mac and ip of the arduino and the ip and credentials of the mqtt server to the config.cpp.
    Change mqtt topic in the WellFillLevelMeasuringDevice.
