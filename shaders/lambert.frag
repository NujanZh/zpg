#version 330

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 outColor;

void main() {
    vec3 objectColor = vec3(0.385, 0.647, 0.812);

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition.xyz);

    float ambietStrengh = 0.3f;
    vec3 ambiet = ambietStrengh * lightColor;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse =  diff * lightColor;

    vec3 result = (ambiet * diffuse) * objectColor;
    outColor = vec4(result, 1.0);
}