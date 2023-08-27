#include "laser-packet-process.h"

ShotPacket shotPacket;
CommandPacket commandPacket;

PacketType parsePacket(uint8_t *packet, uint16_t packetSize) {
    if (packetSize == 0)
        return wrongPacket;

    applyBits(packetSize, packet);
    if (packet[0] & 0b10000000)
        return parseMessage(packet, packetSize);
    else
        return parseShot(packet, packetSize);
}

PacketType parseShot(const uint8_t *packet, uint16_t packetSize) {
    if (packetSize != 14)
        return wrongPacket;

    uint8_t teamCode = packet[1] >> 6;
    if (teamCode > 0x03)
        return wrongPacket;

    Team team = static_cast<Team>(teamCode);

    uint8_t damageCode = packet[1] >> 2;
    damageCode &= 0b00001111;
    uint8_t damage = damageFromDamageKeyCode(damageCode);
    if(damage == 0)
        return wrongPacket;

    uint8_t shooterID = packet[0] & 0b01111111;

    shotPacket = ShotPacket(damage, shooterID, team);
    return shot;
}

PacketType parseMessage(const uint8_t *packet, uint16_t packetSize) {
    if (packetSize != 24)
        return wrongPacket;

    if (packet[2] != 0xE8)
        return wrongPacket;

    uint8_t messageID = packet[0];
    uint8_t messageData = packet[1];

    commandPacket = CommandPacket(messageID, messageData);

    return command;
}

void applyBits(uint16_t length, uint8_t *array) {
    uint16_t addit = 0;
    uint16_t curByte = 0;
    while(true){
        if(addit == length)
            return;
        else if(addit + 8 > length){
            uint8_t res = 0;
            for(int i = 7; i >= ((addit + 8) - length); --i){
                res |= (array[(7 - i) + addit] << i);
            }
            array[curByte] = res;
            return;
        }
        uint8_t res = 0;
        for(int i = 7; i >= 0; --i){
            res |= (array[(7 - i) + addit] << i);
        }
        array[curByte] = res;
        curByte++;
        addit += 8;
    }
}

uint8_t damageFromDamageKeyCode(uint8_t damageKeyCode) {
    switch (damageKeyCode) {
        case 0x00: {
            return 1;
        }

        case 0x01: {
            return 2;
        }

        case 0x02: {
            return 4;
        }

        case 0x03: {
            return 5;
        }

        case 0x04: {
            return 7;
        }

        case 0x05: {
            return 10;
        }

        case 0x06: {
            return 15;
        }

        case 0x07: {
            return 17;
        }

        case 0x08: {
            return 20;
        }

        case 0x09: {
            return 25;
        }

        case 0x0A: {
            return 30;
        }

        case 0x0B: {
            return 35;
        }

        case 0x0C: {
            return 40;
        }

        case 0x0D: {
            return 50;
        }

        case 0x0E: {
            return 75;
        }

        case 0x0F: {
            return 100;
        }

        default:
            return 0;
    }

}

ShotPacket::ShotPacket(uint8_t damage, uint8_t shooterId, Team shooterTeam) : damage(damage), shooterID(shooterId),
                                                                              shooterTeam(shooterTeam) {}

CommandPacket::CommandPacket(uint8_t messageId, uint8_t messageData) : messageID(messageId), messageData(messageData) {}
