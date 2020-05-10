#version 330 core

// Interpolated values from the vertex shaders
in vec3 Color;
in vec2 UV;

// Ouput data
out vec4 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D Texture;

void main(){
	outColor = texture( Texture, UV );
}