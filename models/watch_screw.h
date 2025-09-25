#ifndef WATCH_SCREW_H
#define WATCH_SCREW_H

class WatchScrew {
public:
    WatchScrew();
    ~WatchScrew();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif
