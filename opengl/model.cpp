#include "Model.h"
Model::Model(const char* path) {
	model_load(path);
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices_model);
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices_model);
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
Model::Model(std::vector<Vertex> model_vertices, std::vector<GLuint> model_indices) {
	VAO1.Bind();
	vertices_model = model_vertices;
	indices_model = model_indices;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices_model);
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices_model);
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
Model::Model(const char* path, int ligth) {
	model_load(path);
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices_model);
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices_model);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}
void Model::Draw(Shader shader, Camera camera, Texture& Texture) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	Texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
}
void Model::Draw(Shader shader, Camera camera) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
}
void Model::Draw(Shader shader, Camera camera, Texture& Texture, float rotation, glm::vec3 trans){
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	//Inputs_movement(window, position);
	view = glm::translate(view, trans);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	Texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
}
void Model::Draw(Shader shader, Camera camera, float rotation, glm::vec3 trans) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	//Inputs_movement(window, position);
	view = glm::translate(view, trans);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	//Texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
}
void Model::Inputs_movement(GLFWwindow* window, glm::vec3& position, Camera camera)
{
	glm::mat4 view = glm::mat4(1.0f);
	//// Handles key inputs
	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	position.z -= 0.01;
	//	//view = glm::translate(view, position);
	//}
	//if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	position.x -= 0.01;
	//	//view = glm::translate(view, position);
	//}
	//if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	position.z += 0.01;
	//	//view = glm::translate(view, position);
	//}
	//if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	position.x += 0.01;
	//	//view = glm::translate(view, position);
	//}

	if (!camera.godMode) {
		float posY = position.y;
		// Handles key inputs
		position = camera.Position + camera.Orientation * glm::vec3(4.0f, 4.0f, 4.0f);
		position.y = posY;
	}

}
void Model::moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	Texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();

	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
	//std::cout << "with" <<"\n";
}
void Model::moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position, float rotation, glm::vec3 trans) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	Inputs_movement(window, position, camera);
	view = glm::translate(view, position);
	view = glm::translate(view, trans);
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	// Outputs the matrices into the Vertex Shader
	int modelLoc = glGetUniformLocation(shader.ID, "model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	camera.Matrix(shader, "camMatrix");

	// Binds texture so that is appears in rendering
	Texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();

	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, indices_model.size(), GL_UNSIGNED_INT, 0);
	//std::cout << "with" <<"\n";
}
Model Model::ScaleModel(float x_scale, float y_scale, float z_scale) {
	std::vector<Vertex> vertices = (*this).vertices_model;
	std::vector<GLuint> indices = (*this).indices_model;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position.x *= x_scale;
		vertices[i].position.y *= y_scale;
		vertices[i].position.z *= z_scale;
	}
	return Model(vertices, indices);
}
void Model::model_load(const char* path) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;


	FILE* file;
	fopen_s(&file, path, "r");

	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
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

	vertices_model = vertices;
	std::vector <GLuint> inds;
	for (unsigned int i = 0; i < vertices_model.size(); i++) {
		inds.push_back(i);
	}
	indices_model = inds;

}
