#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 apos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 anormal;
out vec3 vs_position;

// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
out vec3 normal;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	vs_position=vec4(model*vec4(apos,1.0)).xyz;
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix*model* vec4(apos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	normal =anormal;
}