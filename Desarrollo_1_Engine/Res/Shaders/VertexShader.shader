#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

out vec3 outColor;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
void main() {
    gl_Position = proj * view * model * vec4(inPosition, 1.0);
    outColor = inColor;
}