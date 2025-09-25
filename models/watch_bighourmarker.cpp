#include "watch_bighourmarker.h"
#include <vector>
#include <glad/glad.h>

WatchBigHourMarker::WatchBigHourMarker() {
    std::vector<float> vertices;

    const float r = 0.235f, g = 0.094f, b = 0.040f;
    const float w = 0.12f / 2.0f;   
    const float d = 0.15f / 2.0f; 
    const float h = 0.25f / 2.0f;  

    auto push = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

    float x[] = { -w, w };
    float y[] = { -d, d };
    float z[] = { -h, h };

    
    
    push(x[0], y[0], z[1]); push(x[1], y[0], z[1]); push(x[1], y[1], z[1]);
    push(x[0], y[0], z[1]); push(x[1], y[1], z[1]); push(x[0], y[1], z[1]);
    
    push(x[0], y[0], z[0]); push(x[1], y[1], z[0]); push(x[1], y[0], z[0]);
    push(x[0], y[0], z[0]); push(x[0], y[1], z[0]); push(x[1], y[1], z[0]);
    
    push(x[0], y[0], z[0]); push(x[0], y[0], z[1]); push(x[0], y[1], z[1]);
    push(x[0], y[0], z[0]); push(x[0], y[1], z[1]); push(x[0], y[1], z[0]);
    
    push(x[1], y[0], z[0]); push(x[1], y[1], z[1]); push(x[1], y[0], z[1]);
    push(x[1], y[0], z[0]); push(x[1], y[1], z[0]); push(x[1], y[1], z[1]);
    
    push(x[0], y[1], z[0]); push(x[0], y[1], z[1]); push(x[1], y[1], z[1]);
    push(x[0], y[1], z[0]); push(x[1], y[1], z[1]); push(x[1], y[1], z[0]);
    
    push(x[0], y[0], z[0]); push(x[1], y[0], z[1]); push(x[0], y[0], z[1]);
    push(x[0], y[0], z[0]); push(x[1], y[0], z[0]); push(x[1], y[0], z[1]);

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

WatchBigHourMarker::~WatchBigHourMarker() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchBigHourMarker::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
