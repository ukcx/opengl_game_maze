#include "Mesh.h"
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices,   unsigned int width, unsigned int height)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	//Mesh::textures = textures;
	Mesh::width = width;
	Mesh::height = height;

	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	
	

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

void Mesh::Inputs_movement(GLFWwindow* window, glm::vec3& position)
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

}
void Mesh::moving_obj_draw(Shader shader, Camera camera, Texture& brickTex, GLuint size_indices, GLFWwindow* window, glm::vec3& position, float rotation) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
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
	//std::cout << "with" <<"\n";
	


}
void Mesh::Draw(Shader shader, Camera camera, Texture& brickTex, GLuint size_indices) {
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
	proj = glm::perspective(glm::radians(45.0f), (float)width /height, 0.1f, 100.0f);
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