#ifndef WATCH_PIVOT_H
#define WATCH_PIVOT_H

class WatchPivot {
public:
    WatchPivot();
    ~WatchPivot();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif
