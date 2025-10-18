#version 330

in vec4 worldPosition;
in vec3 worldNormal;

out vec4 outColor;

uniform vec3 cameraPos;

void main(void){
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 ambient = vec3(0.1, 0.1, 0.1);

    vec3 lightToVector = normalize(lightPosition - worldPosition.xyz);
    vec3 normal = normalize(worldNormal);
    float diff = max(dot(lightToVector, normal), 0.0);
    vec3 diffuse = diff * vec3(0.385, 0.647, 0.812);

    vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
    vec3 halfwayDir = normalize(lightToVector + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * lightColor * 0.5;

    vec3 result = ambient + diffuse + specular;
    outColor = vec4(result, 1.0);
}
