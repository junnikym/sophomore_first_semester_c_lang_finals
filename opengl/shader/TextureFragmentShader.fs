#version 330 core

// Interpolated values from the vertex shaders
in vec3 Color;
in vec2 UV;

// Ouput data
out vec4 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D Texture;
uniform vec3 spriteColor;
uniform vec2 texturePos;

void main(){
	//outColor = vec4(spriteColor, 1.0) * texture(Texture, UV + texturePos);
	outColor = texture(Texture, UV + texturePos);
}
