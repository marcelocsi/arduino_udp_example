#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "this is your wifi network name";
const char * password = "this is your wifi password";

AsyncUDP udp;

unsigned long contador;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
    if(udp.listen(1234)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());

            while(1)
            {
               contador++;

               // I suggest you handle two buffers in the RAM, like buffer1 and buffer2
               // when you packet.printf(buffer1) you load data to buffer2; when packet.printf(buffer2) you load data to buffer1
               // This shall prevent data corruption when sending or reading from your sensors.
               packet.printf("Contador = %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u", contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador, contador);

               // this timer shall be longer than the one set in the python script.
               delay(2000);
            }
        });
    }
}

void loop()
{
    delay(1000);
    //Send broadcast
    udp.broadcast("Anyone here?");
}
