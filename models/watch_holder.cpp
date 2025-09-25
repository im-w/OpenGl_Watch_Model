#include "watch_holder.h"
#include <vector>

WatchHolder::WatchHolder() {
    std::vector<float> vertices;
    const float r = 0.235f, g = 0.094f, b = 0.040f;

    constexpr int SIDES = 8;
    float xy[SIDES][2] = {
        {  0.6f,  1.5f},
        {  1.3f,  0.7f},
        {  1.3f, -0.7f},
        {  0.6f, -1.5f},
        { -0.6f, -1.5f},
        { -1.3f, -0.7f},
        { -1.3f,  0.7f},
        { -0.6f,  1.5f}
    };
    const float zFront =  0.05f;
    const float zBack  = -0.05f;

    auto push_vertex = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

    float cx = 0.0f, cy = 0.0f;
    for (int i = 0; i < SIDES; ++i) { cx += xy[i][0]; cy += xy[i][1]; }
    cx /= SIDES; cy /= SIDES;

    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;
        push_vertex(cx,       cy,       zFront);
        push_vertex(xy[i][0], xy[i][1], zFront);
        push_vertex(xy[ni][0], xy[ni][1], zFront);
    }


    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;
        push_vertex(cx,        cy,        zBack);
        push_vertex(xy[ni][0], xy[ni][1], zBack);
        push_vertex(xy[i][0],  xy[i][1],  zBack);
    }


    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;

        push_vertex(xy[i][0],  xy[i][1],  zBack);
        push_vertex(xy[i][0],  xy[i][1],  zFront);
        push_vertex(xy[ni][0], xy[ni][1], zFront);

        push_vertex(xy[i][0],  xy[i][1],  zBack);
        push_vertex(xy[ni][0], xy[ni][1], zFront);
        push_vertex(xy[ni][0], xy[ni][1], zBack);
    }

    vertexCount = vertices.size() / 6;


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

WatchHolder::~WatchHolder() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchHolder::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
