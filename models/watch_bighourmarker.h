#ifndef WATCH_BIGHOURMARKER_H
#define WATCH_BIGHOURMARKER_H

class WatchBigHourMarker {
public:
    WatchBigHourMarker();
    ~WatchBigHourMarker();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif // WATCH_BIGHOURMARKER_H
