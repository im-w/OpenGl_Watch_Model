#ifndef WATCH_MINISCREW_H
#define WATCH_MINISCREW_H

class WatchMiniScrew {
public:
    WatchMiniScrew();
    ~WatchMiniScrew();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif
