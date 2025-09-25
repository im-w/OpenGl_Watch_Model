#ifndef WATCH_FACE_H
#define WATCH_FACE_H

#include <glad/glad.h>

class WatchFace {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchFace();
    ~WatchFace();

    void Draw();
};

#endif
