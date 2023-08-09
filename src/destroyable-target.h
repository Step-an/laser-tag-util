#ifndef LASER_TAG_UTIL_DESTROYABLE_TARGET_H
#define LASER_TAG_UTIL_DESTROYABLE_TARGET_H

#include <stdint.h>

namespace DestroyableTarget{
    struct Settings{
        uint16_t hitPoints;
    };

    void handleIRSignal();
    void setup();
    void update();
    void processSettings();
    void executeDeadActions();
}
#endif //LASER_TAG_UTIL_DESTROYABLE_TARGET_H
