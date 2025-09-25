#ifndef WATCH_ANIMATION_H
#define WATCH_ANIMATION_H

class WatchAnimation {
public:
    float hourAngle; 
    float minuteAngle;  
    float hourSpeed; 
    float minuteSpeed; 

    WatchAnimation(float hourSpeedDegPerSec = 6.0f, float minuteSpeedDegPerSec = 72.0f);
    void Update(float deltaTime);
};

#endif // WATCH_ANIMATION_H