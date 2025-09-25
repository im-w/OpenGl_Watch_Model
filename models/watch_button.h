#ifndef WATCH_BUTTON_H
#define WATCH_BUTTON_H

class WatchButton {
public:
    WatchButton();
    ~WatchButton();
    void Draw();

private:
    unsigned int VAO, VBO;
    int vertexCount;
};

#endif
