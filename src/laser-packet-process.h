#ifndef CHECKPOINT_LASER_PACKET_PROCESS_H
#define CHECKPOINT_LASER_PACKET_PROCESS_H

#include <stdint.h>

enum PacketType{
    shot,
    command,
    wrongPacket,
};

PacketType parsePacket(uint8_t *packet, uint16_t packetSize);
PacketType parseMessage(const uint8_t *packet, uint16_t packetSize);
PacketType parseShot(const uint8_t *packet, uint16_t packetSize);

uint8_t damageFromDamageKeyCode(uint8_t damageKeyCode);

void applyBits(uint16_t length, uint8_t *array);

enum Team : uint8_t {
    red = 0x00,
    blue = 0x01,
    yellow = 0x02,
    green = 0x03,
};

class ShotPacket{
public:
    uint8_t damage;
    uint8_t shooterID;
    Team shooterTeam;

    ShotPacket(uint8_t damage, uint8_t shooterId, Team shooterTeam);
    ShotPacket() = default;
};

class CommandPacket{
public:
    uint8_t messageID;
    uint8_t messageData;

    CommandPacket(uint8_t messageId, uint8_t messageData);
    CommandPacket() = default;
};

extern ShotPacket shotPacket;
extern CommandPacket commandPacket;

#endif //CHECKPOINT_LASER_PACKET_PROCESS_H
