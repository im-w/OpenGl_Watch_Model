#ifndef WATCH_HOURMARKER_H
#define WATCH_HOURMARKER_H

class WatchHourMarker {
public:
    WatchHourMarker();
    ~WatchHourMarker();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif // WATCH_HOURMARKER_H
