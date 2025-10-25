#version 330

#define MAX_LIGHTS 4

struct Light {
    vec3 position;
    vec3 color;
};

in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPos;
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

out vec4 outColor;

void main(void){
    vec3 objectColor = vec3(0.385, 0.647, 0.812);
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPos - worldPosition.xyz);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0);

    vec3 diffuseTotal = vec3(0.0);
    vec3 specularTotal = vec3(0.0);

    for(int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(lights[i].position - worldPosition.xyz);

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;
        diffuseTotal += diffuse;

        vec3 reflectDir = reflect(-lightDir, normal);
        float shininess = 32.0;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        float specularStrength = 0.5;
        vec3 specular = specularStrength * spec * lights[i].color;
        specularTotal += specular;
    }

    vec3 result = (ambient + diffuseTotal + specularTotal) * objectColor;
    outColor = vec4(result, 1.0);
}
