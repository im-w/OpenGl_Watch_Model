#ifndef WATCH_BAND_H
#define WATCH_BAND_H

#include <glad/glad.h>

class WatchBand {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    WatchBand();
    ~WatchBand();

    void Draw();
};

#endif // WATCH_BAND_H