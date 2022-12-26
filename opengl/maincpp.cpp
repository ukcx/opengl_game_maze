#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string> 
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
void obj_creation(GLfloat *vertices,GLuint *indices,VAO &VAO1) {
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


	//maze parameters
	int seeds[8] = { 42, 24, 68, 11, 52, 35, 76, 18 };
	int mWidth = 20, mHeight = 20, scaleXZ = 10, scaleY = 16;
	const char* path_2_ = "s.obj";

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("model.vert", "model.frag");
	VAO VAO1;
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	
	for (int i = 0; i < verts.size(); i++) {
		verts[i].position.x *= scaleXZ*10;
		verts[i].position.z *= scaleXZ*10;
	}
	
	Mesh object(verts, ind,width,height);
	


	Shader shaderProgram_obj("model.vert", "model.frag");
	const char* path = "stall.obj";
	Model stall(path);


	Shader shaderProgram_kup("model.vert", "model.frag");
	const char* path___2 = "s.obj";
	Model kup(path___2);

	const char* path2 = "Sphere_mit.obj";
	Model sphere(path2);
	
	Shader shaderProgram_box("model.vert", "model.frag");
	std::vector <Vertex> vert_pry(vertices_x, vertices_x + sizeof(vertices_x) / sizeof(Vertex));
	std::vector <GLuint> ind_pry(indices_2d, indices_2d + sizeof(indices_2d) / sizeof(GLuint));
	Mesh piramid(vert_pry, ind_pry, width, height);
	Material mat_pry(0.9f, 0.8f, 0.8f);
	Material mat_maze(0.5f, 0.5f, 0.5f);
	Material mat_2(0.1f, 0.1f, 0.1f);
	Material mat_3(0.9f, 0.9f, 0.9f);
	mat_maze.sendToShader(shaderProgram_box);
	mat_2.sendToShader(shaderProgram);
	mat_pry.sendToShader(shaderProgram_obj);
	mat_3.sendToShader(shaderProgram_kup);
	Shader lightShader("light.vert", "light.frag");
	Model mylight(path___2, 1);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	Light only_light(lightColor, lightPos);
	
	only_light.light_conf(lightShader);
	only_light.light_conf(shaderProgram,1);
	only_light.light_conf(shaderProgram_box, 1);
	only_light.light_conf(shaderProgram_kup,1);
	only_light.light_conf(shaderProgram_obj, 1);
	shaderProgram.Activate();

	
	Texture	textures[] = {Texture("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)};
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Texture brickTex("newBrick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram_obj, "tex0", 0);
	brickTex.texUnit(shaderProgram_kup, "tex0", 0);
	Texture boxTex("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	boxTex.texUnit(shaderProgram_box, "tex0", 0);
	tex[0].texUnit(shaderProgram_box, "tex0", 0);
	tex[0].Bind();


	//glEnable(GL_DEPTH_CLAMP);
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);


	
	// Maze Generation
	MazeGenerator maze(mHeight, mWidth, seeds[1], scaleXZ, scaleY);
	maze.CreateModels(path_2_);
	std::vector<Model> cubes = maze.getModels();
	std::vector<glm::vec3> transfers = maze.getTranslates();
	
	// Creates camera object
	glm::vec3 translateCameraToEntrance = glm::vec3(-0.4f * scaleXZ * mWidth, 0.5f, -0.4f * scaleXZ * (mHeight - 1));
	Camera camera(width, height, translateCameraToEntrance);
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	glm::vec3 position(0.f);

	Texture hudTex("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Model hud2("heart.obj");

	Shader shaderNew("model.vert", "model.frag");
	only_light.light_conf(shaderNew, 1);
	TextRenderer Text(width, height);
	Text.Load("arial.ttf", 80);

	Model square(vertices_square, indicesSquare);
	Texture whiteTex("white.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture blackTex("black.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture redTex("red.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture blueTex("blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blueTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture grayTex("darkgray.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grayTex.texUnit(shaderProgram_obj, "tex0", 0);

	Model sphere2 = sphere.ScaleModel(1.0f, 1.0f, 1.0f);

	std::vector<std::string> visitedCoords;
	for (int i = 0; i < (2 * mHeight + 1); i++) {
		std::string line((mWidth * 2 + 1), 'O');
		visitedCoords.push_back(line);
	}
	
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.529f, 0.808f, 0.922f, 0.08f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 5000.0f);
		//Text.RenderText("Remaing time \n 4:36", 50.0f, 600.0f, 1.0f);

		rotation += 0.35f;
		//obj.moving_obj_draw(shaderProgram, camera, brickTex, sizeof(indices),window,position, 0);
		piramid.Draw(shaderProgram_obj, camera, boxTex, 0.0f, glm::vec3(3.0f));
		hud2.Draw(shaderProgram_obj, camera, boxTex, 0.0f, glm::vec3(-3.0f));
		//Draw(shaderProgram_box, camera, VAObox, boxTex, sizeof(indices_2d));
		glm::vec3 translate = glm::vec3(0.5f, 0.0f, 0.0f);
		glm::vec3 translate2 = glm::vec3(0.0f, -0.001f, 0.0f);
		glm::vec3 translate3 = glm::vec3(1.5f, 0.3f, 0.0f);
		
		
		for (int i = 0; i < cubes.size(); i++) {
			glm::vec3 translate_L = transfers[i];
			cubes[i].Draw(shaderProgram_box, camera, brickTex, 0.0f, translate_L);
		}

		kup.moving_obj_draw(shaderProgram_kup, camera, brickTex , window, position, 0, translate3);
		object.Draw(shaderProgram, camera, boxTex , 0, translate2);
		glm::vec3 translateToEntrance = glm::vec3(-0.4f * scaleXZ * mWidth, 0.01f, -0.4f * scaleXZ * (mHeight - 1));
		stall.Draw(shaderProgram_obj, camera, boxTex, 0, translateToEntrance);
		

		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0), glm::vec3(0) + glm::vec3(0, 0, -1), glm::vec3(0) + glm::vec3(0, 1, 0));

		camera.updateDirectly(view, projection);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Text.RenderText("Remaining time: 4:36", 50.0f, 650.0f, 1.0f);
		glDisable(GL_BLEND);
		Model scaledHeart = hud2.ScaleModel(0.1f, 0.1f, 0.1f);
		Model scaledSquare = square.ScaleModel(0.5f, 0.5f, 0.5f);

		scaledHeart.Draw(shaderProgram_kup, camera, redTex, 0, glm::vec3(0.4f, 0.12f, 0.0f));
		scaledHeart.Draw(shaderProgram_kup, camera, redTex, 0, glm::vec3(0.62f, 0.12f, 0.0f));
		scaledHeart.Draw(shaderProgram_kup, camera, redTex, 0, glm::vec3(0.84f, 0.12f, 0.0f));

		float widthOfSquare = 0.2f / mWidth;
		float heightOfSquare = 0.2f / mHeight;
		glm::vec3 centerOfMap = glm::vec3(-0.8f + (widthOfSquare / 2), -0.8f + (heightOfSquare / 2), 0.0f);
		Model littleSquare = scaledSquare.ScaleModel(1.0f / (2 * mWidth + 1), 1.0f / (2 * mHeight + 1), 1.0f);
		glm::vec2 coords = maze.GetMyCoordinate(camera.Position);
		int xCoord = coords.x, yCoord = coords.y;
		if (xCoord >= 0 && yCoord >= 0)
			visitedCoords[xCoord][yCoord] = 'X';
		if (xCoord >= 1 && yCoord >= 0)
			visitedCoords[xCoord - 1][yCoord] = 'X';
		if (xCoord >= -1 && yCoord >= 0)
			visitedCoords[xCoord + 1][yCoord] = 'X';
		if (xCoord >= 0 && yCoord >= 1)
			visitedCoords[xCoord][yCoord - 1] = 'X';
		if (xCoord >= 0 && yCoord >= -1)
			visitedCoords[xCoord][yCoord + 1] = 'X';

		for (int i = 0; i < maze.maze.size(); i++) {
			std::string line = maze.maze[i];
			for (int j = 0; j < line.length(); j++) {
				glm::vec3 transSquare = glm::vec3(1.0f * (i - mHeight) * heightOfSquare, 1.0f * (j - mWidth) * widthOfSquare, 0.0f);
				if (i == yCoord && j == xCoord) {
					littleSquare.Draw(shaderProgram_obj, camera, redTex, 0, centerOfMap + transSquare);
				}
				else {
					if (visitedCoords[j][i] == 'X') {
						if (line[j] == '#') {
							littleSquare.Draw(shaderProgram_obj, camera, blueTex, 0, centerOfMap + transSquare);
						}
						else {
							littleSquare.Draw(shaderProgram_obj, camera, whiteTex, 0, centerOfMap + transSquare);
						}
					}
					else {
						littleSquare.Draw(shaderProgram_obj, camera, grayTex, 0, centerOfMap + transSquare);
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