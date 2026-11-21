#include "w5500.h"
#include <Wire.h>

// Ethernet MAC addresses
const uint8_t MAC_COMP[6] = {
    0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF
}; // Broadcast destination

const uint8_t MAC_BOARD[6] = {
    0x02, 0x53, 0x49,
    0x00, 0x00, 0x04
};

uint32_t send_count = 0;
Wiznet5500 w5500;

// 60-byte Ethernet frame
uint8_t pkt[60] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination
    0x02, 0x53, 0x49, 0x00, 0x00, 0x04, // Source
    0x63, 0xE4,                         // EtherType
    0x0F                                // Payload
};

// Send packets
void sendPacket()
{
    pkt[14] = 0b00001111;

    memcpy(pkt, MAC_COMP, 6);
    memcpy(pkt + 6, MAC_BOARD, 6);

    if (w5500.sendFrame(pkt, sizeof(pkt)) != sizeof(pkt))
    {
        Serial.println("Ethernet send error");
    }
    else
    {
        send_count++;
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup");

    Serial.println("Board Ethernet Module Starting...");

    if (!w5500.begin(MAC_BOARD))
    {
        Serial.println("Ethernet initialization FAILED");
        while (true)
        {
            delay(1000);
        }
    }

    Serial.println("Ethernet Start Success...");

    delay(500);
}

void loop()
{
    sendPacket();

    Serial.print("Send count: ");
    Serial.println(send_count);

    delay(500);
}