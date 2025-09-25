#version 330 core

in vec3 FragPos;
in vec3 VertexColor;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform bool lightEnabled;

void main()
{
    vec3 norm = normalize(Normal);

   
    vec3 baseAmbient = 0.6 * VertexColor;

  
    vec3 softLightDir = normalize(vec3(0.5, 1.0, 0.3));
    float softDiff = max(dot(norm, softLightDir), 0.0);
    vec3 baseDiffuse = 0.6 * softDiff * VertexColor;

    vec3 result = baseAmbient + baseDiffuse;

    if (lightEnabled) {
        
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * VertexColor;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * vec3(1.0); 

        result += diffuse + specular;
    }

    FragColor = vec4(result, 1.0);
}
