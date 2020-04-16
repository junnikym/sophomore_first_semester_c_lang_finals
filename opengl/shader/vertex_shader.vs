#version 330 core
in vec3 positionAttribute;
in vec3 colorAttribute;
out vec3 passColorAttribute;

uniform vec4 transform;

void main() {
	gl_Position = transform + vec4(positionAttribute, 1.0f);
	passColorAttribute = colorAttribute;
}