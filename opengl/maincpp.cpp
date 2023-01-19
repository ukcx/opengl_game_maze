#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<gl/GL.h>
#include <fstream>
#include <string> 
#include <iostream>
#include <chrono>
#include<GLFW/glfw3native.h>

#include"AIObject.h"
#include"MazeGenerator.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Mesh.h"
#include"Camera.h"
#include"Material.h"
#include"model.h"
#include"Light.h"
#include"TextRenderer.h"
const float MINIMAP_SIZE = 100.0f; // size of the minimap in world units
glm::mat4 minimapProjection = glm::ortho(-MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	-MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	10.1f, 1000.0f);

// Set up the minimap view matrix
const float MINIMAP_ALTITUDE = 500.0f; // altitude of the camera in world units
glm::mat4 minimapView = glm::lookAt(glm::vec3(0.0f, MINIMAP_ALTITUDE, 0.0f), // camera position
	glm::vec3(0.0f, 0.0f, 0.0f), // camera target
	glm::vec3(0.0f, 0.0f, -1.0f)); // camera up vector
unsigned int fbo, rbo;
GLuint minimapTexture;
void createMinimapTexture()
{

	// Create the FBO and RBO
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	// Bind the FBO and RBO
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	// Set the renderbuffer storage to a texture
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, MINIMAP_SIZE, MINIMAP_SIZE);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);

	// Create the minimap texture

	glGenTextures(1, &minimapTexture);
	glBindTexture(GL_TEXTURE_2D, minimapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MINIMAP_SIZE, MINIMAP_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, minimapTexture, 0);
}
void renderMinimap_2()
{
	// Set the projection and view matrices for the minimap
	/*glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(minimapProjection));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(minimapView));*/

	// Bind the FBO and RBO

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	// Set the viewport to the size of the minimap texture
	glViewport(0, 0, MINIMAP_SIZE, MINIMAP_SIZE);

	// Clear the FBO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the 3D world to the FBO
	//renderWorld();

	// Unbind the FBO and RBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Set the viewport to the window dimensions
	int windowWidth, windowHeight;
	glViewport(0, 0, 1600, 1600);

	// Draw the minimap texture on the screen using a quad or other primitive
	//GLuint minimapTexture;
	glBindTexture(GL_TEXTURE_2D, minimapTexture);
	//drawQuad();
}
// Set up the FBO and RBO for rendering the 3D world to a texture

const unsigned int width = 1600;
const unsigned int height = 1600;
GLfloat vertices_not[] =
{ //     COORDINATES     /        COLORS            /       NORMALS  /    TexCoord   //
	-1.0f, 0.0f,  1.0f,		0.83f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f   , 0.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f    ,0.0f, 1.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices_not[] =
{
	0, 1, 2,
	0, 2, 3
};
void obj_creation(GLfloat* vertices, GLuint* indices, VAO& VAO1) {
	// Generates Vertex Array Object and binds it
	//std::cout << vertices << "\n";
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));

	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

}
// Vertex array object and vertex buffer objects for the minimap quad
GLuint minimapVAO, minimapVBO, minimapEBO;

// Vertex buffer object for the player location
GLuint playerVBO;

// Minimap scale factor (used to convert world coordinates to minimap coordinates)
float minimapScale = 0.1f;
void InitMinimap()
{
	// Create the minimap quad vertices
	float minimapVertices[] = {
	  -1.0f, 1.0f, 0.0f, // Top left
	  -1.0f, -1.0f, 0.0f, // Bottom left
	  1.0f, -1.0f, 0.0f, // Bottom right
	  1.0f, 1.0f, 0.0f // Top right
	};

	// Create the minimap quad indices
	unsigned int minimapIndices[] = {
	  0, 1, 3, // First triangle
	  1, 2, 3 // Second triangle
	};

	// Create the player location vertices
	float playerVertices[] = {
	  0.0f, 0.0f, 0.0f // Center of the player location quad
	};
	VAO X, y, z;
	// Generate a VAO and a VBO for the minimap quad
	glGenVertexArrays(1, &minimapVAO);
	glGenBuffers(1, &minimapVBO);
	glGenBuffers(1, &minimapEBO);

	// Bind the VAO and VBO, and upload the minimap quad data
	glBindVertexArray(minimapVAO);
	glBindBuffer(GL_ARRAY_BUFFER, minimapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(minimapVertices), minimapVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, minimapEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(minimapIndices), minimapIndices, GL_STATIC_DRAW);

	// Set up vertex attributes for the minimap quad
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Generate a VBO for the player location
	glGenBuffers(1, &playerVBO);

	// Bind the VBO and upload the player location data
	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_DYNAMIC_DRAW);

	// Set up a vertex attribute for the player location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}
void RenderMinimap(Shader shader, Camera camera)
{
	float minimapX = -0.0f;
	float minimapY = 0.3f;
	float minimapWidth = 1.0f, minimapHeight = 1.0f;

	// Set up the vertex data for the minimap quad
	float vertices[] = {
		minimapX, minimapY, 0.0f, 0.0f,
		minimapX + minimapWidth * 0.4f, minimapY, 1.0f, 0.0f,
		minimapX + minimapWidth * 0.4f, minimapY + minimapHeight * 0.2f, 1.0f, 1.0f,
		minimapX, minimapY + minimapHeight * 0.2f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);

	//glm::mat4 projection = glm::ortho(-1.0f, 1200.0f, -1.0f, 10.0f, -1.0f, 100.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 3) + glm::vec3(0, 0, -1), glm::vec3(0) + glm::vec3(0, 1, 0));
	//camera.updateDirectly(view, projection);
	/*unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);*/
	//Texture mini_texture("white.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//mini_texture.Bind();
	//unsigned int FBO, texture;
	//glGenFramebuffers(1, &FBO);
	//glGenTextures(1, &texture);

	//// Bind the FBO and set the viewport to the size of the camera view
	//glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//glViewport(0, 0, 1600, 1600);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 1600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	//// Unbind the FBO and restore the default framebuffer
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//unsigned int framebuffer;
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//// generate texture
	//unsigned int textureColorbuffer;
	//glGenTextures(1, &textureColorbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 1600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//// attach it to currently bound framebuffer object
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//unsigned int rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glm::mat4 map_View = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	shader.Activate();
	shader.SetVector2f("mapSize", glm::vec2(1600.0f, 1600.0f));
	shader.SetVector2f("minimapSize", glm::vec2(1.0f, 1.0f));
	shader.SetVector2f("minimapPosition", glm::vec2(1.0f, 1.0f));
	shader.SetVector2f("playerPosition", glm::vec2(camera.Position.x, camera.Position.z));
	glUniform1i(glGetUniformLocation(shader.ID, "mapTexture"), 0);
	// Set up an orthographic projection
	createMinimapTexture();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glm::mat4 projection = glm::ortho(0.0f, (float)minimapWidth, 0.0f, (float)minimapHeight);
	unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	shader.SetMatrix4("view", map_View);

	// Bind the VAO and use a drawing command to draw the minimap quad
	//glBindVertexArray(minimapVAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//// Bind the VBO and use a drawing command to draw the player location
	//glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
	//glDrawArrays(GL_POINTS, 0, 1);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glPushAttrib(GL_VIEWPORT_BIT);

	// Set the viewport to the size of the minimap texture
	glViewport(0, 0, MINIMAP_SIZE, MINIMAP_SIZE);

	// Clear the FBO

	// Render the 3D world to the FBO
	//renderWorld();

	// Unbind the FBO and RBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Set the viewport to the window dimensions
	int windowWidth, windowHeight;

	//glViewport(0, 0, 1600, 1600);

	// Draw the minimap texture on the screen using a quad or other primitive
	//GLuint minimapTexture;
	glBindTexture(GL_TEXTURE_2D, minimapTexture);



	glGenerateMipmap(GL_TEXTURE_2D);
	glGenTextures(1, &minimapTexture);
	glBindTexture(GL_TEXTURE_2D, minimapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, minimapWidth, minimapHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);




	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);

}
/*
void obj_creation_main(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, VAO& VAO) {
	// Generates Vertex Array Object and binds it
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

}*/
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /         NORMALS           /     TexCoord           //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(0.0f, 0.0f) },
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex vertices_x[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TexCoord         //
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.0f, 0.0f) },
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)},



	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(-0.8f, 0.5f,  0.0f),glm::vec2(0.0f, 0.0f) },
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(2.5f, 5.0f)},


	Vertex{glm::vec3(-0.5f, 0.0f,  -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f, -0.8),glm::vec2(5.0f, 0.0f) },
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(0.5f, 0.0f,  -0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.8f, 0.5f,  0.0f),glm::vec2(0.0f, 0.0f) },
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.5f,  0.8f),glm::vec2(5.0f, 0.0f) },
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 0.5f,  0.8f), glm::vec2(2.5f, 5.0f)}


};

GLfloat vertices_2d[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices_2d[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

std::vector<Vertex> vertices_square =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TexCoord         //
	Vertex{glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.0f, 0.0f) },
	Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, 0.5f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(5.0f, 0.0f)},
};

std::vector<GLuint> indicesSquare = {
	0, 1, 2,
	1, 2, 3
};
using namespace std;
int main()
{

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	srand(time(0));
	//maze parameters
	int seeds[8] = { 42, 24, 68, 11, 52, 35, 76, 18 };
	int mWidth = 15, mHeight = 15, scaleXZ = 40, scaleY = 32, seedIndex = (rand() % 8);

	//Paths
	const char* path_2_ = "s.obj";
	const char* path___2 = "s.obj";
	const char* path2 = "Sphere_mit.obj";
	const char* path = "stall.obj";
	const char* path_arrow = "arrow.obj";
	//Vertices and Indices
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Vertex> vert_pry(vertices_x, vertices_x + sizeof(vertices_x) / sizeof(Vertex));
	std::vector <GLuint> ind_pry(indices_2d, indices_2d + sizeof(indices_2d) / sizeof(GLuint));

	//Shaders
	Shader shaderProgram("model.vert", "model.frag");
	Shader shaderProgram_obj("model.vert", "model.frag");
	Shader shaderProgram_kup("model.vert", "model.frag");
	Shader shaderProgram_tree("model.vert", "default.frag");
	Shader shaderProgram_box("model.vert", "model.frag");
	Shader lightShader("light.vert", "light.frag");
	Shader shaderNew("model.vert", "model.frag");


	for (int i = 0; i < verts.size(); i++) {
		verts[i].position.x *= 1000;// scaleXZ * 10;
		verts[i].position.z *= 1000;// scaleXZ*10;
	}

	//Models
	Mesh object(verts, ind, width, height);
	Model stall(path);
	Model kup(path___2);
	Model sphere(path2);
	Model tree("x.obj", true);
	Model AIsphere(path2);
	Mesh piramid(vert_pry, ind_pry, width, height);
	Model heart("heart.obj");
	Model sphere2 = sphere.ScaleModel(1.0f, 1.0f, 1.0f);
	Model mylight(path___2, 1);
	Model square(vertices_square, indicesSquare);


	//Materials
	Material mat_pry(0.9f, 0.8f, 0.8f);
	Material mat_maze(0.5f, 0.5f, 0.5f);
	Material mat_2(0.1f, 0.1f, 0.1f);
	Material mat_3(0.9f, 0.9f, 0.9f);
	mat_maze.sendToShader(shaderProgram_box);
	mat_2.sendToShader(shaderProgram);
	mat_pry.sendToShader(shaderProgram_obj);
	mat_3.sendToShader(shaderProgram_kup);
	mat_maze.sendToShader(shaderProgram_tree);


	//Light
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 20.0f, 0.0f);
	Light only_light(lightColor, lightPos);

	only_light.light_conf(lightShader);
	only_light.light_conf(shaderProgram, 1);
	only_light.light_conf(shaderProgram_tree, 1);
	only_light.light_conf(shaderProgram_box, 1);
	only_light.light_conf(shaderProgram_kup, 1);
	only_light.light_conf(shaderProgram_obj, 1);
	only_light.light_conf(shaderNew, 1);
	shaderProgram.Activate();


	//Textures
	Texture	textures[] = { Texture("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) };
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Texture brickTex("newBrick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram_obj, "tex0", 0);
	brickTex.texUnit(shaderProgram_kup, "tex0", 0);
	Texture boxTex("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	boxTex.texUnit(shaderProgram_box, "tex0", 0);
	tex[0].texUnit(shaderProgram_box, "tex0", 0);
	tex[0].Bind();

	Texture whiteTex("white.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture thunderTex("thunder.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	thunderTex.texUnit(shaderProgram_obj, "tex0", 0);
	//Texture flashTex("flash.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//flashTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture blackTex("black.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture redTex("red.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture blueTex("blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blueTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture grayTex("darkgray.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grayTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture greenTex("green.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	greenTex.texUnit(shaderProgram_obj, "tex0", 0);

	//glEnable(GL_DEPTH_CLAMP);
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);



	// Maze Generation
	MazeGenerator maze(mHeight, mWidth, seeds[seedIndex], scaleXZ, scaleY);
	maze.CreateModels(path_2_);
	std::vector<Model*> cubes = maze.getModels();
	std::vector<glm::vec3> transfers = maze.getTranslates();
	std::vector<Model> coins = maze.getModels_coins();
	std::vector<Model> low_trees = maze.getModels_low_tree();
	std::vector<Model> middle_trees = maze.getModels_middle_tree();

	std::vector<glm::vec3> coin_transfers = maze.coin_getTranslates();
	std::vector<glm::vec3> tree_transfers = maze.tree_getTranslates();
	// Creates camera object
	glm::vec3 translateCameraToEntrance = glm::vec3(-0.4f * scaleXZ * mWidth, 2.5f, -0.4f * scaleXZ * (mHeight - 1));
	Camera camera(width, height, translateCameraToEntrance);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	glm::vec3 position(0.f);
	glm::vec3 position2(0.f);


	//Text Renderer
	TextRenderer Text(width, height);
	Text.Load("arial.ttf", 60);

	//Translates
	glm::vec3 translateToEntrance = glm::vec3(-0.4f * scaleXZ * mWidth, 0.6f, -0.4f * scaleXZ * (mHeight - 1));
	glm::vec3 translate = glm::vec3(0.5f, 0.0f, 0.0f);
	glm::vec3 translate2 = glm::vec3(0.0f, -0.001f, 0.0f);
	glm::vec3 translate3 = glm::vec3(1.5f, 0.3f, 0.0f);
	glm::vec3 translateAI = maze.MazeToWorldCoordinate(maze.GetRandomEmptyCoordinates(glm::vec2(10, 10), glm::vec2(mWidth * 2, mHeight * 2)));
	std::cout << "AI coordinates: (" << maze.GetMyCoordinate(translateAI).x << ", " << maze.GetMyCoordinate(translateAI).y << ")\n";

	sphere.translation = translateToEntrance;
	//AI Objects
	//Object playerObject(&sphere, translateToEntrance, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, true);
	AIObject AI(&AIsphere, translateAI, glm::vec3(4.0f), 0.0f, true, &maze, &sphere);


	//Initialize visited coords matrix for the minimap
	std::vector<std::string> visitedCoords;
	for (int i = 0; i < (2 * mHeight + 1); i++) {
		std::string line((mWidth * 2 + 1), 'O');
		visitedCoords.push_back(line);
	}
	//InitMinimap();
	chrono::steady_clock sc;   // create an object of `steady_clock` class
	auto start = sc.now();
	Shader shader_minimap("minimap.vert", "minimap.frag");

	int frameCount = 0, incrmnt = 1;
	bool arrows = true;
	bool first = true;
	vector<Model*> bone_of_my_sword;
	//Model  bone_of_my_sword[10];
	vector<glm::vec3> bone_of_my_sword_translation;
	vector<glm::vec3> bone_of_my_sword_position;
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.529f, 0.808f, 0.922f, 0.08f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//RenderMinimap(shader_minimap, camera);
		camera.Inputs(window, sphere.position + sphere.translation);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 5000.0f);
		//Text.RenderText("Remaing time \n 4:36", 50.0f, 600.0f, 1.0f);

		rotation += 0.35f;
		//obj.moving_obj_draw(shaderProgram, camera, brickTex, sizeof(indices),window,position, 0);
		//piramid.Draw(shaderProgram_obj, camera, boxTex, 0.0f, glm::vec3(3.0f));
		Model scaledLight = mylight.ScaleModel(10.0f, 10.0f, 10.0f);
		scaledLight.Draw(lightShader, camera, boxTex, 0.0f, lightPos);
		//Draw(shaderProgram_box, camera, VAObox, boxTex, sizeof(indices_2d));
		glm::vec3 translate = glm::vec3(0.5f, 0.0f, 0.0f);
		glm::vec3 translate2 = glm::vec3(0.0f, -0.001f, 0.0f);
		glm::vec3 translate3 = glm::vec3(1.5f, 0.3f, 0.0f);


		/*for (int i = 0; i < cubes.size(); i++) {
			glm::vec3 translate_L = transfers[i];
			cubes[i].Draw(shaderProgram_box, camera, brickTex, 0.0f, translate_L);
		}*/
		glm::vec3 translateToEntrance = glm::vec3(-0.4f * scaleXZ * mWidth, 0.2f, -0.4f * scaleXZ * (mHeight - 1));
		sphere.moving_obj_draw(shaderProgram_kup, camera, brickTex, window, position, 0, translateToEntrance);
		sphere.sphere_bounding_box();
		for (int i = 0; i < coins.size(); i++) {
			glm::vec3 translate_L = coin_transfers[i];
			coins[i].Draw_rotate(shaderProgram_box, camera, thunderTex, translate_L);
			coins[i].box_bounding_box();
			if (sphere.detect_collision_sphere_box(coins[i])) {
				std::cout << "go brrrrrrrrrrrrrrrrrrr" << endl;
				sphere.increase_speed(0.001);
				//Model* s = coins[i];
				//cout << "point to object" << endl;
				//
				//coins.erase(coins.begin() + i);
				//std::cout << "\ndeleted from bones \n";
				////s->delete_object();
				////delete s;
				//coin_transfers.erase(coin_transfers.begin() + i);

				//i--;
			}

		}
		for (int i = 0; i < low_trees.size(); i++) {
			glm::vec3 translate_L = tree_transfers[i];
			if (maze.isItFarDistance(camera.Position, translate_L)) {
				low_trees[i].Draw_rotate(shaderProgram_box, camera, thunderTex, translate_L);
				low_trees[i].box_bounding_box();
			}
			else {
				middle_trees[i].Draw_rotate(shaderProgram_box, camera, thunderTex, translate_L);
				middle_trees[i].box_bounding_box();
			}
			
			
		}
		//playerObject.drawObject(window, shaderProgram_kup, camera, brickTex);
		//playerObject.model->sphere_bounding_box();

		AI.drawObject(shaderProgram_obj, camera, redTex);

		for (int e = 0; e < bone_of_my_sword.size(); e++) {
			bone_of_my_sword[e]->
				fire_arrow_draw(shaderProgram_kup, camera, brickTex,
					bone_of_my_sword_position[e], bone_of_my_sword_translation[e]);

			bone_of_my_sword[e]->sphere_bounding_box();
			//first = false;

		}
		/*	if(arrows)
			{
				stall.fire_arrow_draw(shaderProgram_kup, camera, brickTex, position2, sphere.bounding_sphere_center);
				if(first)
				{
					stall.sphere_bounding_box();
					first = false;
				}

			}*/
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			Model* arrows = new Model(path___2);
			bone_of_my_sword.push_back(arrows);
			bone_of_my_sword_translation.push_back(sphere.bounding_sphere_center);
			bone_of_my_sword_position.push_back(glm::vec3(0.f));
			std::cout << "Added new arrow, new size: " << bone_of_my_sword.size() << "\n";
		}

		tree.Draw(shaderProgram_tree, camera, boxTex, 0.2f, glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.4f, 10.4f, 10.4f));

		for (int i = 0; i < cubes.size(); i++) {
			glm::vec3 translate_L = transfers[i];
			cubes[i]->Draw(shaderProgram_box, camera, brickTex, 0.0f, translate_L);
			cubes[i]->box_bounding_box();
		}

		std::vector<Model*> adjacentWalls = maze.GetNeighboringWalls(sphere.position + sphere.translation);
		//std::cout << adjacentWalls.size() << "\n";
		for (int i = 0; i < adjacentWalls.size(); i++) {
			if (sphere.detect_collision_sphere_box((*adjacentWalls[i]))) {
				std::cout << "boundi " << sphere.bounding_sphere_center.x << " " << sphere.bounding_sphere_center.y << " " << sphere.bounding_sphere_center.z << endl;
				std::cout << "sphere " << sphere.position.x + sphere.translation.x << " " << sphere.position.y + sphere.translation.y << " " << sphere.position.z + sphere.translation.z << endl;

				sphere.collision_result();
			}
		}

		//
		//if (arrows && stall.detect_collision_sphere_box(cubes[i])) {
		//	std::cout << "it happened" << "\n";
		//	stall.delete_object();
		//	arrows = false;

		//
		//	//break;
		//}
		for (int e = 0; e < bone_of_my_sword.size(); e++) {
			std::vector<Model*> adjacentWallsForArrow = maze.GetNeighboringWalls(bone_of_my_sword_translation[e] + bone_of_my_sword[e]->position);

			//std::cout << adjacentWallsForArrow.size() << "\n";
			for (int i = 0; i < adjacentWallsForArrow.size(); i++) {
				//std::cout << "number of the vector is" << e<<endl;
				//bone_of_my_sword[e].fire_arrow_draw(shaderProgram_kup, camera, brickTex, position2, bone_of_my_sword_translation[e]);
				//cubes[i]->bounding_box;
				if (bone_of_my_sword[e]->detect_collision_sphere_box((*adjacentWallsForArrow[i]))) {
					std::cout << "it happened" << "\n";

					Model* s = bone_of_my_sword[e];
					cout << "point to object" << endl;
					//bone_of_my_sword[e]->delete_object();
					bone_of_my_sword.erase(bone_of_my_sword.begin() + e);
					std::cout << "\ndeleted from bones \n";
					s->delete_object();
					delete s;
					std::cout << "\ndeleted fully \n";
					std::cout << "new size after deletion" << bone_of_my_sword.size() << endl;
					bone_of_my_sword_translation.erase(bone_of_my_sword_translation.begin() + e);
					bone_of_my_sword_position.erase(bone_of_my_sword_position.begin() + e);
					cout << "what2" << endl;
					e--;
					break;
					/*std::vector<Model>::iterator start = bone_of_my_sword.begin() + e;
					std::vector<Model>::iterator end = bone_of_my_sword.begin() + e + 1;
					for (auto it = start; it != end; ++it) {
						it->delete_object();
					}
					bone_of_my_sword.erase(start, end);*/
					/*std::swap(bone_of_my_sword[e], bone_of_my_sword.back());
					bone_of_my_sword.back().delete_object();
					bone_of_my_sword.pop_back();*/
					/*bone_of_my_sword_translation.erase(bone_of_my_sword_translation.begin() + e);
					cout << "what" << endl;
					bone_of_my_sword_position.erase(bone_of_my_sword_position.begin() + e);
					cout << "what2" << endl;
					e--;*/
				}
			}
		}

		object.Draw(shaderProgram, camera, boxTex, 0, translate2);

		//stall.Draw(shaderProgram_obj, camera, boxTex, 0, translateToEntrance);


		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0), glm::vec3(0) + glm::vec3(0, 0, -1), glm::vec3(0) + glm::vec3(0, 1, 0));

		camera.updateDirectly(view, projection);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		auto end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - start);
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		{



			while (true)
			{
				TextRenderer Texts(width, height);
				Texts.Load("arial.ttf", 50);
				ifstream MyReadFile("leaders.txt");
				string myText;
				string name;
				string time, score, sira;


				glClearColor(0.2f, 0.2f, 0.9f, 0.08f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				Model scaledSquare_2 = square.ScaleModel(0.5f, 0.5f, 0.5f);
				glm::vec3 centerOfTable = glm::vec3(-0.0f, -0.3f, 0.0f);
				square.Draw(shaderProgram_obj, camera, redTex, 0, centerOfTable);
				// Clean the back buffer and depth buffer
				Texts.RenderText("LeaderBoard", 440.0f, 680.0f, 1.0f);
				//Text.RenderText("Name       Time       SCORE", 480.0f, 740.0f, 1.0f);
				float yInc = 60.0f;
				float xInc = 250.0f;
				Texts.RenderText("Name", 450.0f, 740.0f, 1.0f);
				Texts.RenderText("Time", 450.0f + xInc, 740.0f, 1.0f);
				Texts.RenderText("Score", 450.0f + xInc + xInc, 740.0f, 1.0f);

				while (std::getline(MyReadFile, myText)) {
					// Output the text from the file

					stringstream ss(myText);

					ss >> name >> time >> score >> sira;
					Texts.RenderText(sira, 410.0f, 740.0f + yInc, 1.0f);
					Texts.RenderText(name, 450.0f, 740.0f + yInc, 1.0f);
					Texts.RenderText(time, 450.0f + xInc, 740.0f + yInc, 1.0f);
					Texts.RenderText(score, 450.0f + xInc + xInc, 740.0f + yInc, 1.0f);
					yInc += 60;
					//Text.RenderText(name, centerOfTable.x +50.0f, centerOfTable.y+960.0f, 1.0f);
				}

				glfwSwapBuffers(window);
				// Take care of all GLFW events
				glfwPollEvents();
				if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
					break;
				}
			}



		}
		if (int(time_span.count()) == 120) {
			while (true)
			{
				glClearColor(0.2f, 0.2f, 0.9f, 0.08f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				TextRenderer a_text(width, height);
				a_text.Load("arial.ttf", 174);
				a_text.RenderText("GAME OVER", 400.0f, 740.0f, 1.0f, glm::vec3(1.0, 0, 0));

				glfwSwapBuffers(window);

				// Take care of all GLFW events
				glfwPollEvents();
				if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
					break;
				}

			}


		}
		Text.RenderText("Time: " + to_string(int(time_span.count()) / 60) + "." + to_string(int(time_span.count()) % 60), 50.0f, 700.0f, 1.0f);
		Text.RenderText("Speed: " + to_string(int(sphere.speed * 100)), 50.0f, 630.0f, 1.0f, glm::vec3(0.1f, 0.1f, 0.9f));
		Text.RenderText("Points: 100", 450.0f, 630.0f, 1.0f, glm::vec3(0.5f, 0.5f, 0.0f));
		glDisable(GL_BLEND);
		float scale = (frameCount % 50) * 0.003 + 1;
		Model scaledHeart = heart.ScaleModel(0.1f * scale, 0.1f * scale, 0.1f * scale);
		Model scaledSquare = square.ScaleModel(0.5f, 0.5f, 0.5f);

		scaledHeart.Draw(shaderProgram_kup, camera, boxTex, 0, glm::vec3(0.4f, 0.12f, 0.0f));
		scaledHeart.Draw(shaderProgram_kup, camera, redTex, 0, glm::vec3(0.62f, 0.12f, 0.0f));
		scaledHeart.Draw(shaderProgram_kup, camera, boxTex, 0, glm::vec3(0.84f, 0.12f, 0.0f));

		if (frameCount == 49)
			incrmnt = -1;
		else if (frameCount == 0)
			incrmnt = 1;
		frameCount += incrmnt;

		float widthOfSquare = 0.2f / mWidth;
		float heightOfSquare = 0.2f / mHeight;
		glm::vec3 centerOfMapLeft = glm::vec3(-0.8f + (widthOfSquare / 2), -0.8f + (heightOfSquare / 2), 0.0f);
		glm::vec3 centerOfMapRight = glm::vec3(0.8f - (widthOfSquare / 2), -0.8f + (heightOfSquare / 2), 0.0f);
		Model littleSquare = scaledSquare.ScaleModel(1.0f / (2 * mWidth + 1), 1.0f / (2 * mHeight + 1), 1.0f);
		glm::vec2 coords = maze.GetMyCoordinate(sphere.position + sphere.translation);
		glm::vec2 AIcoords = maze.GetMyCoordinate(AI.position);

		int xCoord = coords.x, yCoord = coords.y;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {

				int x = xCoord + i;
				int y = yCoord + j;

				if (x >= 0 && x < mWidth * 2 + 1 && y >= 0 && y < mHeight * 2 + 1) {
					if (visitedCoords[x][y] == 'Y' || visitedCoords[x][y] == 'Z')
						visitedCoords[x][y] = 'Z';
					else
						visitedCoords[x][y] = 'X';
				}
			}
		}

		for (glm::vec2 point : AI.path) {
			if (visitedCoords[point.x][point.y] == 'X' || visitedCoords[point.x][point.y] == 'Z')
				visitedCoords[point.x][point.y] = 'Z';
			else
				visitedCoords[point.x][point.y] = 'Y';
		}

		for (int i = 0; i < maze.maze.size(); i++) {
			std::string line = maze.maze[i];
			for (int j = 0; j < line.length(); j++) {
				glm::vec3 transSquare = glm::vec3(1.0f * (i - mHeight) * heightOfSquare, 1.0f * (j - mWidth) * widthOfSquare, 0.0f);
				if (i == yCoord && j == xCoord) {
					littleSquare.Draw(shaderProgram_obj, camera, redTex, 0, centerOfMapRight + transSquare);
					littleSquare.Draw(shaderProgram_obj, camera, redTex, 0, centerOfMapLeft + transSquare);
				}
				else {
					if (visitedCoords[j][i] == 'X' || visitedCoords[j][i] == 'Z') {
						if (line[j] == '#') {
							littleSquare.Draw(shaderProgram_obj, camera, blueTex, 0, centerOfMapLeft + transSquare);
						}
						else {
							littleSquare.Draw(shaderProgram_obj, camera, whiteTex, 0, centerOfMapLeft + transSquare);
						}
					}
					else {
						littleSquare.Draw(shaderProgram_obj, camera, grayTex, 0, centerOfMapLeft + transSquare);
					}

					if (i == AIcoords.y && j == AIcoords.x) {
						littleSquare.Draw(shaderProgram_obj, camera, redTex, 0, centerOfMapRight + transSquare);
					}
					else if (visitedCoords[j][i] == 'Y' || visitedCoords[j][i] == 'Z') {
						littleSquare.Draw(shaderProgram_obj, camera, greenTex, 0, centerOfMapRight + transSquare, glm::vec3(1.0f, 1.0f, 1.0f));
					}
					else {
						if (line[j] == '#') {
							littleSquare.Draw(shaderProgram_obj, camera, blueTex, 0, centerOfMapRight + transSquare);
						}
						else {
							littleSquare.Draw(shaderProgram_obj, camera, whiteTex, 0, centerOfMapRight + transSquare);
						}
					}
				}
			}
		}


		glEnable(GL_DEPTH_TEST);

		//camera.updateDirectly(
		// w, projection);
		//camera.updateMatrix(45.0f, 0.1f, 
		// 
		// .0f);
		//Model* hud = Hud();
		//hud->Draw(shaderProgram_obj, camera, boxTex, 0, translateToEntrance);
		//sphere.moving_obj_draw(shaderProgram_obj, camera, brickTex, window, position, 0, translate2);
		//mylight.Draw(lightShader, camera);
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	//VAO1.Delete();
	//VBO1.Delete();
	//EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}