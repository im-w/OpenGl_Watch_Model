#include "watch_body.h"
#include <vector>
#include <cmath>

WatchBody::WatchBody() {
    std::vector<float> vertices;

    const int segments = 64;
    const float innerRadius = 1.0f;
    const float outerRadius = 1.25f;
    const float height = 0.4f;
    const float halfHeight = height / 2.0f;

  
    const float r = 0.064f, g = 0.061f, b = 0.057f;
    


    auto push_vertex = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

    for (int i = 0; i < segments; ++i) {
        float theta1 = 2.0f * M_PI * i / segments;
        float theta2 = 2.0f * M_PI * (i + 1) / segments;

        float xi1 = innerRadius * cos(theta1);
        float yi1 = innerRadius * sin(theta1);
        float xi2 = innerRadius * cos(theta2);
        float yi2 = innerRadius * sin(theta2);

        float xo1 = outerRadius * cos(theta1);
        float yo1 = outerRadius * sin(theta1);
        float xo2 = outerRadius * cos(theta2);
        float yo2 = outerRadius * sin(theta2);

     
        push_vertex(xi1, yi1, +halfHeight);
        push_vertex(xo1, yo1, +halfHeight);
        push_vertex(xo2, yo2, +halfHeight);

        push_vertex(xi1, yi1, +halfHeight);
        push_vertex(xo2, yo2, +halfHeight);
        push_vertex(xi2, yi2, +halfHeight);

      
        push_vertex(xi1, yi1, -halfHeight);
        push_vertex(xo2, yo2, -halfHeight);
        push_vertex(xo1, yo1, -halfHeight);

        push_vertex(xi1, yi1, -halfHeight);
        push_vertex(xi2, yi2, -halfHeight);
        push_vertex(xo2, yo2, -halfHeight);

   
        push_vertex(xo1, yo1, -halfHeight);
        push_vertex(xo2, yo2, -halfHeight);
        push_vertex(xo2, yo2, +halfHeight);

        push_vertex(xo1, yo1, -halfHeight);
        push_vertex(xo2, yo2, +halfHeight);
        push_vertex(xo1, yo1, +halfHeight);

     
        push_vertex(xi1, yi1, -halfHeight);
        push_vertex(xi2, yi2, +halfHeight);
        push_vertex(xi2, yi2, -halfHeight);

        push_vertex(xi1, yi1, -halfHeight);
        push_vertex(xi1, yi1, +halfHeight);
        push_vertex(xi2, yi2, +halfHeight);
    }

    vertexCount = vertices.size() / 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

WatchBody::~WatchBody() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchBody::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
