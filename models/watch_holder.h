#ifndef WATCH_HOLDER_H
#define WATCH_HOLDER_H

#include <glad/glad.h>

class WatchHolder {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchHolder();
    ~WatchHolder();

    void Draw();
};

#endif // WATCH_HOLDER_H