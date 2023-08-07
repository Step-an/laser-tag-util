#ifndef CHECKPOINT_BASE_H
#define CHECKPOINT_BASE_H

namespace base {
    enum BaseMode {
        ammo,
        life,
    };

    struct Settings{
        BaseMode mode;
        uint32_t triggerTimeMs;
    };


    void createImpulse();
    void setReadyState(bool state);
    void setup();

    void update();

    void syncTime();
}
#endif //CHECKPOINT_BASE_H
