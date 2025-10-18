#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 worldPosition;
out vec3 worldNormal;


void main(void){
    gl_Position = (projection * view * model) * vec4(vp,1.0f);
    worldPosition = model * vec4(vp,1.0f);
    worldNormal = vn; //next lesson
}
