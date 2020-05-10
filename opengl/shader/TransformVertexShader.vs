#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec3 Color;
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	
	Color = vertexColor;
	UV = vertexUV;
}

