#include "watch_band.h"
#include <vector>
#include <cmath>

WatchBand::WatchBand() {
    std::vector<float> vertices;
    const float r = 0.037f, g = 0.036f, b = 0.034f;

    const int segments = 64;
    const float outerRadius = 3.2f;
    const float innerRadius = 2.9f; 
    const float zFront =  0.7f;
    const float zBack  = -0.7f;

    auto push_vertex = [&](float x, float y, float z) {
        vertices.insert(vertices.end(), { x, y, z, r, g, b });
    };

    
    for (int i = 0; i < segments; ++i) {
        int ni = (i + 1) % segments;
        float theta  = 2.0f * M_PI * i / segments;
        float thetaN = 2.0f * M_PI * ni / segments;

        float x0 = outerRadius * cos(theta);
        float y0 = outerRadius * sin(theta);
        float x1 = outerRadius * cos(thetaN);
        float y1 = outerRadius * sin(thetaN);

        
        push_vertex(x0, y0, zBack);
        push_vertex(x0, y0, zFront);
        push_vertex(x1, y1, zFront);

        
        push_vertex(x0, y0, zBack);
        push_vertex(x1, y1, zFront);
        push_vertex(x1, y1, zBack);
    }


    for (int i = 0; i < segments; ++i) {
        int ni = (i + 1) % segments;
        float theta  = 2.0f * M_PI * i / segments;
        float thetaN = 2.0f * M_PI * ni / segments;

        float x0 = innerRadius * cos(theta);
        float y0 = innerRadius * sin(theta);
        float x1 = innerRadius * cos(thetaN);
        float y1 = innerRadius * sin(thetaN);


        push_vertex(x1, y1, zBack);
        push_vertex(x1, y1, zFront);
        push_vertex(x0, y0, zFront);

   
        push_vertex(x1, y1, zBack);
        push_vertex(x0, y0, zFront);
        push_vertex(x0, y0, zBack);
    }

   
    for (int i = 0; i < segments; ++i) {
        int ni = (i + 1) % segments;
        float theta  = 2.0f * M_PI * i / segments;
        float thetaN = 2.0f * M_PI * ni / segments;

        float xo0 = outerRadius * cos(theta);
        float yo0 = outerRadius * sin(theta);
        float xo1 = outerRadius * cos(thetaN);
        float yo1 = outerRadius * sin(thetaN);

        float xi0 = innerRadius * cos(theta);
        float yi0 = innerRadius * sin(theta);
        float xi1 = innerRadius * cos(thetaN);
        float yi1 = innerRadius * sin(thetaN);

      
        push_vertex(xo0, yo0, zFront);
        push_vertex(xi0, yi0, zFront);
        push_vertex(xi1, yi1, zFront);

     
        push_vertex(xo0, yo0, zFront);
        push_vertex(xi1, yi1, zFront);
        push_vertex(xo1, yo1, zFront);
    }

   
    for (int i = 0; i < segments; ++i) {
        int ni = (i + 1) % segments;
        float theta  = 2.0f * M_PI * i / segments;
        float thetaN = 2.0f * M_PI * ni / segments;

        float xo0 = outerRadius * cos(theta);
        float yo0 = outerRadius * sin(theta);
        float xo1 = outerRadius * cos(thetaN);
        float yo1 = outerRadius * sin(thetaN);

        float xi0 = innerRadius * cos(theta);
        float yi0 = innerRadius * sin(theta);
        float xi1 = innerRadius * cos(thetaN);
        float yi1 = innerRadius * sin(thetaN);

        
        push_vertex(xi0, yi0, zBack);
        push_vertex(xo0, yo0, zBack);
        push_vertex(xo1, yo1, zBack);

        
        push_vertex(xi0, yi0, zBack);
        push_vertex(xo1, yo1, zBack);
        push_vertex(xi1, yi1, zBack);
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

WatchBand::~WatchBand() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void WatchBand::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}