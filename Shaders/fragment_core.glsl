#version 330 core
out vec4 FragColor;

uniform vec4 customColour;

void main() {
    FragColor = customColour;
}