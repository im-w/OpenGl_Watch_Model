#ifndef WATCH_BODY_H
#define WATCH_BODY_H

#include <glad/glad.h>

class WatchBody {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchBody();
    ~WatchBody();

    void Draw();
};

#endif
