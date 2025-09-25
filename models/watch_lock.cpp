#include "watch_lock.h"
#include <vector>

WatchLock::WatchLock() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float x = 1.7f, y = 1.0f, h = 0.5f;
    const float r = 0.235f, g = 0.094f, b = 0.040f;


    float verts[8][6] = {
        { -x/2, -y/2, -h/2, r, g, b },
        {  x/2, -y/2, -h/2, r, g, b },
        {  x/2,  y/2, -h/2, r, g, b },
        { -x/2,  y/2, -h/2, r, g, b },
        { -x/2, -y/2,  h/2, r, g, b },
        {  x/2, -y/2,  h/2, r, g, b },
        {  x/2,  y/2,  h/2, r, g, b },
        { -x/2,  y/2,  h/2, r, g, b }
    };


    for (int i = 0; i < 8; ++i) {
        vertices.insert(vertices.end(), verts[i], verts[i] + 6);
    }


    unsigned int idx[] = {
        0,1,2, 2,3,0, 
        4,5,6, 6,7,4,
        0,1,5, 5,4,0,  
        3,2,6, 6,7,3,
        1,2,6, 6,5,1, 
        0,3,7, 7,4,0 
    };
    indices.insert(indices.end(), idx, idx + 36);

    vertexCount = indices.size();


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

WatchLock::~WatchLock() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void WatchLock::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
