#include "nodemcu.h"
NodeMcu nodeMcu;

#include "lora.h"
LoRa loraDevice;

#include "mqtt.h"
const char *mqttServerAddress = "192.168.1.43";
uint mqttPort = 1883;
std::vector<std::string> mqttSubscriptions = {};
WiFiClient wifiClient;
PubSubClient pubsub(wifiClient);
Mqtt mqtt{mqttServerAddress, mqttPort, mqttSubscriptions};
void mqttOnMessageReceived(char *rtopic, byte *rpayload, unsigned int length) { return; };

void setup()
{
    Serial.begin(115200);
    Serial.println();
    randomSeed(micros());

    nodeMcu.setup();
    loraDevice.setup();
    mqtt.setup(pubsub, mqttOnMessageReceived, nodeMcu.deviceId);
}

void loop()
{
    delay(100);
    mqtt.loop(pubsub);

    std::string loraMessage = loraDevice.receive();
    if (!loraMessage.length())
        return;

    std::string mqttMessage = "mqtt-gateway " + loraMessage;
    std::string topic = "sensor/gps";
    Serial.printf("Publish message: %s, on topic: %s\n", mqttMessage.c_str(), topic.c_str());
    pubsub.publish(topic.c_str(), mqttMessage.c_str());
}
