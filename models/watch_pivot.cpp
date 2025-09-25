#include "watch_pivot.h"
#include <vector>
#include <cmath>
#include <glad/glad.h>

WatchPivot::WatchPivot() {
    std::vector<float> vertices;

    const int segments = 32;
    const float radius = 0.08f;
    const float height = 0.32f;
    const float halfHeight = height / 2.0f;
    const float r = 0.064f, g = 0.061f, b = 0.057f;

    auto push_vertex = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

    for (int i = 0; i < segments; ++i) {
        float theta1 = 2.0f * M_PI * i / segments;
        float theta2 = 2.0f * M_PI * (i + 1) / segments;

        float x1 = radius * cos(theta1);
        float y1 = radius * sin(theta1);
        float x2 = radius * cos(theta2);
        float y2 = radius * sin(theta2);

 
        push_vertex(0.0f, 0.0f, +halfHeight);
        push_vertex(x1, y1, +halfHeight);
        push_vertex(x2, y2, +halfHeight);

     
        push_vertex(0.0f, 0.0f, -halfHeight);
        push_vertex(x2, y2, -halfHeight);
        push_vertex(x1, y1, -halfHeight);

       
        push_vertex(x1, y1, -halfHeight);
        push_vertex(x1, y1, +halfHeight);
        push_vertex(x2, y2, +halfHeight);

        push_vertex(x1, y1, -halfHeight);
        push_vertex(x2, y2, +halfHeight);
        push_vertex(x2, y2, -halfHeight);
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

WatchPivot::~WatchPivot() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchPivot::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
