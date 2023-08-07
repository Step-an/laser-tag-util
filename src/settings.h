#ifndef LASER_TAG_UTIL_SETTINGS_H
#define LASER_TAG_UTIL_SETTINGS_H

#include <stdint.h>
#include "checkpoint.h"
#include "base.h"

constexpr int checkpointSettingsAddress = 5;
constexpr int baseSettingsAddress = checkpointSettingsAddress + sizeof(checkpoint::Settings);
constexpr int destroyableTargetSettingsAddress = baseSettingsAddress + sizeof(base::Settings);


#endif //LASER_TAG_UTIL_SETTINGS_H
