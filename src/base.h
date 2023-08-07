#ifndef CHECKPOINT_BASE_H
#define CHECKPOINT_BASE_H

namespace base {
    void createImpulse();
    void setReadyState(bool state);
    void setup();

    void update();

    void syncTime();
}
#endif //CHECKPOINT_BASE_H
