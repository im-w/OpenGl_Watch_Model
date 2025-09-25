#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 FragPos;
out vec3 VertexColor;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * normalize(aPos); 
    VertexColor = aColor;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}