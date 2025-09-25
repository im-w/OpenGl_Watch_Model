#ifndef WATCH_MINUTE_H
#define WATCH_MINUTE_H

#include <glad/glad.h>

class WatchMinute {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchMinute();
    ~WatchMinute();

    void Draw();
};

#endif // WATCH_MINUTE_H