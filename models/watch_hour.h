#ifndef WATCH_HOUR_H
#define WATCH_HOUR_H

#include <glad/glad.h>

class WatchHour {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchHour();
    ~WatchHour();

    void Draw();
};

#endif // WATCH_HOUR_H