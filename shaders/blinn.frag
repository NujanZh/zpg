#version 330

in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPos;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 outColor;

void main(void){
    vec3 objectColor = vec3(0.385, 0.647, 0.812);

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition.xyz);
    vec3 viewDir = normalize(cameraPos - worldPosition.xyz);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float shininess = 32.0;
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    float specularStrength = 0.5;
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    outColor = vec4(result, 1.0);
}
