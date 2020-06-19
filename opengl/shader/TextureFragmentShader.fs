#version 330 core

// Interpolated values from the vertex shaders
in vec3 Color;
in vec2 UV;

// Ouput data
out vec4 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D Texture;
uniform vec4 spriteColor;
uniform vec2 texturePos;

void main(){
	vec4 texColor = spriteColor * texture(Texture, UV + texturePos);
	if(texColor.a < 0.1)
		discard;
	outColor = texColor;
}
