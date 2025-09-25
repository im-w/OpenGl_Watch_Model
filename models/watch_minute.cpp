#include "watch_minute.h"
#include <vector>

WatchMinute::WatchMinute() {
    std::vector<float> vertices;
  
    const float r = 0.235f, g = 0.094f, b = 0.040f;

  
    constexpr int SIDES = 5;
    float xy[SIDES][2] = {
        { -0.05f, 0.85f },  // 0
        { -0.1f,  -0.2f },  // 1
        {  0.1f,  -0.2f },  // 2
        {  0.05f, 0.85f },  // 3
        {  0.0f,  0.9f }   // 4
    };
    const float zFront =  0.005f;
    const float zBack  = -0.005f;

    auto push_vertex = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

 
    float cx = 0.0f, cy = 0.0f;
    for (int i = 0; i < SIDES; ++i) {
        cx += xy[i][0];
        cy += xy[i][1];
    }
    cx /= SIDES; cy /= SIDES;

    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;
        push_vertex(cx,        cy,        zFront);
        push_vertex(xy[i][0],  xy[i][1],  zFront);
        push_vertex(xy[ni][0], xy[ni][1], zFront);
    }


    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;
        push_vertex(cx,         cy,        zBack);
        push_vertex(xy[ni][0],  xy[ni][1], zBack);
        push_vertex(xy[i][0],   xy[i][1],  zBack);
    }

 
    for (int i = 0; i < SIDES; ++i) {
        int ni = (i + 1) % SIDES;
        
        push_vertex(xy[i][0],   xy[i][1],   zBack);
        push_vertex(xy[i][0],   xy[i][1],   zFront);
        push_vertex(xy[ni][0],  xy[ni][1],  zFront);
       
        push_vertex(xy[i][0],   xy[i][1],   zBack);
        push_vertex(xy[ni][0],  xy[ni][1],  zFront);
        push_vertex(xy[ni][0],  xy[ni][1],  zBack);
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

WatchMinute::~WatchMinute() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchMinute::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}