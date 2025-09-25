#include "watch_animation.h"

WatchAnimation::WatchAnimation(float hourSpeedDegPerSec, float minuteSpeedDegPerSec)
    : hourAngle(0.0f), minuteAngle(0.0f),
      hourSpeed(hourSpeedDegPerSec), minuteSpeed(minuteSpeedDegPerSec) {
}

void WatchAnimation::Update(float deltaTime) {
    hourAngle   -= hourSpeed   * deltaTime;
    minuteAngle -= minuteSpeed * deltaTime;

    if (hourAngle   >= 360.0f) hourAngle   -= 360.0f;
    if (minuteAngle >= 360.0f) minuteAngle -= 360.0f;
}