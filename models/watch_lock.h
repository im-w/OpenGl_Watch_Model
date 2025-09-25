#ifndef WATCH_LOCK_H
#define WATCH_LOCK_H

#include <glad/glad.h>

class WatchLock {
public:
    unsigned int VAO, VBO, EBO;
    int vertexCount;

    WatchLock();
    ~WatchLock();

    void Draw();
};

#endif // WATCH_LOCK_H