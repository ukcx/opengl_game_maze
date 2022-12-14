#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Mesh.h"
#include"Camera.h"
#include"Material.h"
const unsigned int width = 1600;
const unsigned int height = 1600;
/*
void moving_obj_draw(Shader shader, Camera camera, VAO& VAO1, Texture& brickTex, GLuint size_indices,GLFWwindow* window, glm::vec3& position) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	Inputs_movement(window, position);
	view = glm::translate(view, position);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	brickTex.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, size_indices / sizeof(int), GL_UNSIGNED_INT, 0);
	// Swap the back buffer with the front buffer


}*/

void Draw(Shader shader, Camera camera, VAO& VAO1, Texture& brickTex, GLuint size_indices) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Inputs_movement(window, position);
	//view = glm::translate(view, position);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	brickTex.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, size_indices / sizeof(int), GL_UNSIGNED_INT, 0);
	// Swap the back buffer with the front buffer
}
void Draw_array(Shader shader, Camera camera, VAO& VAO1, Texture& brickTex) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Inputs_movement(window, position);
	//view = glm::translate(view, position);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	brickTex.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawArrays(GL_TRIANGLES,0,36);
	// Swap the back buffer with the front buffer
}

/*
void Inputs_movement(GLFWwindow* window, glm::vec3 &position)
{
	glm::mat4 view = glm::mat4(1.0f);
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		position.z += 0.01;
		//view = glm::translate(view, position);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		position.x -= 0.01;
		//view = glm::translate(view, position);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		position.z -= 0.01;
		//view = glm::translate(view, position);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		position.x += 0.01;
		//view = glm::translate(view, position);
	}

}*/
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
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
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
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
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

std::vector<Vertex> parseObject(const char* path, std::vector < glm::vec3 >& out_vertices,
	std::vector < glm::vec2 >& out_uvs,
	std::vector < glm::vec3 >& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	
	FILE* file;
	fopen_s(&file, path, "r");

	if (file == NULL) {
		printf("Impossible to open the file !\n");
		//return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line

		int res = fscanf(file, "%s", lineHeader);
		
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
			// else : parse lineHeader
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				//return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::vector<Vertex> vertices;
	vertices.resize(vertexIndices.size(), Vertex());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = temp_vertices[vertexIndices[i] - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
		vertices[i].normal = temp_normals[normalIndices[i] - 1];
		vertices[i].texUV = temp_uvs[uvIndices[i] - 1];
		
	}

	//DEBUG
	

	//Loaded success

	return vertices;

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


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("model.vert", "model.frag");
	VAO VAO1;
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	
	
	
	Mesh obj(verts, ind,width,height);
	
	


	Shader shaderProgram_obj("model.vert", "model.frag");
	const char* path = "donut_deneme.obj";
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector<Vertex> x = parseObject(path, vertices, uvs, normals);
	
	//GLuint ind_de[35];

	std::vector <GLuint> inds;
	for (int i = 0; i < x.size(); i++) {
		inds.push_back(i);
	}

	
	//std::vector <GLuint> ind_des(ind_de, ind_de + sizeof(ind_de) / sizeof(GLuint));
	
	Mesh object(x, inds, width, height);
	
	Shader shaderProgram_box("model.vert", "model.frag");
	std::vector <Vertex> vert_pry(vertices_x, vertices_x + sizeof(vertices_x) / sizeof(Vertex));
	std::vector <GLuint> ind_pry(indices_2d, indices_2d + sizeof(indices_2d) / sizeof(GLuint));
	Mesh piramid(vert_pry, ind_pry, width, height);
	/*
	// Generates Vertex Array Object and binds it
	VAO VAObox;
	VAObox.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBObox(vertices_2d, sizeof(vertices_2d));

	// Generates Element Buffer Object and links it to indices
	EBO EBObox(indices_2d, sizeof(indices_2d));

	// Links VBO attributes such as coordinates and colors to VAO
	VAObox.LinkAttrib(VBObox, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAObox.LinkAttrib(VBObox, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAObox.LinkAttrib(VBObox, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAObox.LinkAttrib(VBObox, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Unbind all to prevent accidentally modifying them
	VAObox.Unbind();
	VBObox.Unbind();
	EBObox.Unbind();*/
	Material mat_pry(0.0f, 0.2f, 0.1f);
	mat_pry.sendToShader(shaderProgram_box);
	mat_pry.sendToShader(shaderProgram);
	mat_pry.sendToShader(shaderProgram_obj);
	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram_obj.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_obj.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram_obj.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram_obj.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram_box.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_box.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram_box.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram_box.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/


	
	Texture	textures[] = {Texture("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)};
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Texture brickTex("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram_obj, "tex0", 0);
	Texture boxTex("odin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	boxTex.texUnit(shaderProgram_box, "tex0", 0);
	tex[0].texUnit(shaderProgram_box, "tex0", 0);
	tex[0].Bind();


	glEnable(GL_DEPTH_CLAMP);
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	glm::vec3 position(0.f);
	// Main while loop
	
	
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		// Tell OpenGL which Shader Program we want to use
		/*shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			//rotation += 0.05f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		Inputs_movement(window, position);
		view = glm::translate(view, position);*/
		
		rotation += 0.35f;
		/*//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		model =  view * model;
		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	
		camera.Matrix(shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);*/

		//obj.moving_obj_draw(shaderProgram, camera, brickTex, sizeof(indices),window,position, 0);
		piramid.moving_obj_draw(shaderProgram_box, camera, boxTex, sizeof(indices_2d), window, position, rotation);
		//Draw(shaderProgram_box, camera, VAObox, boxTex, sizeof(indices_2d));
		//object.moving_obj_draw(shaderProgram_obj, camera, brickTex, sizeof(inds), window, position,0);
		//Draw_array(shaderProgram_obj, camera, VAOs, boxTex);
		/*
		glm::mat4 modelBOX = glm::mat4(1.0f);
		
		glUniform3f(glGetUniformLocation(shaderProgram_box.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		int modelLO = glGetUniformLocation(shaderProgram_box.ID, "model");
		glUniformMatrix4fv(modelLO, 1, GL_FALSE, glm::value_ptr(modelBOX));
		
		camera.Matrix(shaderProgram_box, "camMatrix");
		boxTex.Bind();
		VAObox.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices_2d) / sizeof(int), GL_UNSIGNED_INT, 0);
		*/
		
		lightShader.Activate();
		
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBufferData(GL_ARRAY_BUFFER, x.size() * sizeof(glm::vec3), &x[0], GL_STATIC_DRAW);
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