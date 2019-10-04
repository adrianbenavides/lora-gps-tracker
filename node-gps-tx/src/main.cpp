#include "nodemcu.h"
NodeMcu nodeMcu;

#include "lora.h"
LoRa loraDevice;

#include "neo6m.h"
Neo6m neo6m;
TinyGPSPlus gpsParser;

void setup()
{
    Serial.begin(9600);
    Serial.println();
    randomSeed(micros());

    nodeMcu.setup();
    loraDevice.setup();
    neo6m.setup();
}

void loop()
{
    delay(100);
    gpsParser = neo6m.read();

    if (!gpsParser.location.isValid())
        return;

    neo6m.print(gpsParser);

    char lat[8];
    snprintf(lat, 8, "%g", gpsParser.location.lat());

    char lng[8];
    snprintf(lng, 8, "%g", gpsParser.location.lng());

    char temp[255];
    snprintf(temp, 255, "lat=%s,lng=%s", lat, lng);
    std::string loraMessage = std::string(temp);
    loraDevice.send(loraMessage);
}
