#include "Model.h"
Model::Model(const char* path) {

	model_load(path);
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO1=VBO(vertices_model);

	// Generates Element Buffer Object and links it to indices
	EBO1=EBO(indices_model);
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
Model::Model(const char* path, glm::vec3 color) {

	model_load2(path, color);

	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO1=VBO(vertices_model);

	// Generates Element Buffer Object and links it to indices
	EBO1=EBO(indices_model);
	
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
	translation = trans;
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
	view = glm::translate(view, translation);
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
void Model::Inputs_movement(GLFWwindow* window, glm::vec3& pos, Camera camera)
{
	glm::mat4 view = glm::mat4(1.0f);

	if (!camera.godMode) {
		glm::vec3 orient = camera.Orientation - glm::vec3(0, camera.Orientation.y, 0);
		new_speed = accel_speed;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			acc = orient * acc_magnitude;
			glm::vec3 speedChange = acc * time_delta;

			new_speed += speedChange;
			float newSpeedSize = glm::length(new_speed);
			new_speed = glm::normalize(new_speed) * glm::min(newSpeedSize, max_speed);
			//std::cout << "accel_speed: " << accel_speed.x << " " << accel_speed.y << " " << accel_speed.z << "\n";
			
			//std::cout << "sphere moovemet" << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " <<"\n";
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			acc = -glm::normalize(glm::cross(orient, camera.Up)) * acc_magnitude;
			glm::vec3 speedChange = time_delta * acc;

			new_speed += speedChange;
			float newSpeedSize = glm::length(new_speed);
			new_speed = glm::normalize(new_speed) * glm::min(newSpeedSize, max_speed);

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			acc = -orient * acc_magnitude;
			glm::vec3 speedChange = acc * time_delta;

			new_speed += speedChange;
			float newSpeedSize = glm::length(new_speed);
			new_speed = glm::normalize(new_speed) * glm::min(newSpeedSize, max_speed);

			//position += speed * -camera.Orientation ;
			//position.y = posY;
			//bounding_sphere_center += speed * -camera.Orientation;
			//bounding_sphere_center.y = bounding_y;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			acc = glm::normalize(glm::cross(orient, camera.Up)) * acc_magnitude;
			glm::vec3 speedChange = acc * time_delta;

			new_speed += speedChange;
			float newSpeedSize = glm::length(new_speed);
			new_speed = glm::normalize(new_speed) * glm::min(newSpeedSize, max_speed);
		}
	}

}
void Model::Draw(Shader shader, Camera camera, Texture& Texture, float rotation, glm::vec3 trans, glm::vec3 scale) {
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
	model *= glm::scale(view, scale);
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
void Model::Draw_rts(Shader shader, Camera camera, Texture& Texture, glm::vec3 trans, glm::vec3 scale) {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	
	//std::cout << "rotation is" << rotation << "\n";
	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation += 1.0;
	//Inputs_movement(window, position);
	model *= glm::scale(view, scale);
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
void Model::moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& pos) {
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
void Model::moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& pos, float rotation, glm::vec3 trans) {
	if (first_move)
	{
		translation = trans;
		first_move = false;

	}
	
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	
	float posY = position.y;
	old_pos = position;
	float bounding_y = bounding_sphere_center.y;
	
	//Friction
	float delta_speed = frict_coefficient * time_delta;
	float speedLen = glm::length(accel_speed);
	if (speedLen > 0) {
		if ((glm::length(accel_speed) - delta_speed) > 0)
			accel_speed = glm::normalize(accel_speed) * (glm::length(accel_speed) - delta_speed);
		else
			accel_speed = glm::normalize(accel_speed) * 0.0f;
	}
	//std::cout << "accel_speed: " << accel_speed.x << " " << accel_speed.y << " " << accel_speed.z << "\n";

	//Acceleration
	Inputs_movement(window, position, camera);
	
	//Position Change in Total
	position += accel_speed * time_delta + (0.5f * acc * time_delta * time_delta);
	position.y = posY;
	bounding_sphere_center += accel_speed * time_delta + (0.5f * acc * time_delta * time_delta);
	bounding_sphere_center.y = bounding_y;

	//Calculate angle change and new angular position
	angular_speed = accel_speed / bounding_sphere_radius;
	glm::vec3 angular_pos_change = angular_speed * time_delta;// + (0.5f * acc * time_delta * time_delta);
	angular_position += angular_pos_change;
	//int ang_x = angular_position.x / (M_PI * 2);
	//angular_position.x = angular_position.x - ang_x * 2 * M_PI;
	//int ang_z = angular_position.z / (M_PI * 2);
	//angular_position.z = angular_position.z - ang_z * 2 * M_PI;

	//Update speed and accleration
	accel_speed = new_speed;
	acc = glm::vec3(0.0f, 0.0f, 0.0f);
	
	//Rotate the object with respect to its current angular position
	model = glm::rotate(model, angular_position.x, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, angular_position.z, glm::vec3(1.0f, 0.0f, 0.0f));

	//model = glm::rotate(model, angular_pos_change.x, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::rotate(model, angular_pos_change.z, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, position);
	view = glm::translate(view, translation);
	//change center
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	model = view * model;
	//bounding_sphere_center += trans;
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
void Model::model_load2(const char* path,glm::vec3 color) {
	std::vector< unsigned int > vertexIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
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
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
			// else : parse lineHeader
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				std::cout << matches<<"\n";
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				//return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	//std::cout << "buraya kadar geldi\n";
	std::vector<Vertex> vertices;
	vertices.resize(vertexIndices.size(), Vertex());

	for (size_t i = 0; i < vertices.size(); ++i)
	{

		vertices[i].position = temp_vertices[vertexIndices[i] - 1];
		vertices[i].color = color;
		vertices[i].normal = temp_normals[normalIndices[i] - 1];
		vertices[i].texUV = glm::vec3(0.0f, 0.0f, 0.0f);
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
void Model::sphere_bounding_box() {
	glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	// Loop through the vertices of the object
	for (int i = 0; i < vertices_model.size(); i++) {
		// Update the minimum and maximum values as necessary
		min.x = fmin(min.x, vertices_model[i].position.x);
		min.y = fmin(min.y, vertices_model[i].position.y);
		min.z = fmin(min.z, vertices_model[i].position.z);
		max.x = fmax(max.x, vertices_model[i].position.x);
		max.y = fmax(max.y, vertices_model[i].position.y);
		max.z = fmax(max.z, vertices_model[i].position.z);
	}

	// Calculate the center of the bounding box
	if (first)
	{
		glm::vec3 center = (min + max) / 2.0f;
		bounding_sphere_center = center;
		bounding_sphere_center += translation;
		bounding_sphere_radius = (glm::length(max - min) / 2.0f);//-0.002
		bounding_sphere_radius = bounding_sphere_radius * 60 / 100;
		first = false;

	}
	

	// Calculate the radius of the bounding sphere
	
}

bool Model::detect_collision_sphere(Model model) {
	//model.sphere_bounding_box();
	float distance = glm::length(bounding_sphere_center - model.bounding_sphere_center);
	//std::cout << "moving center: " << bounding_sphere_center.x << " "<< bounding_sphere_center.y << " " << bounding_sphere_center.z<< " moving radius " << bounding_sphere_radius << std::endl;
	//std::cout << "other object center " << model.bounding_sphere_center.x << " " << model.bounding_sphere_center.y << " " << model.bounding_sphere_center.z << " " << " moving radius " << model.bounding_sphere_radius << std::endl;
	// If the distance between the centers is less than the sum of the radii, then the spheres are colliding
	return distance < bounding_sphere_radius + model.bounding_sphere_radius;
}
bool Model::detect_collision_sphere(glm::vec3 boundingsphere, float rad) {
	float distance = glm::length(bounding_sphere_center - boundingsphere);
	//std::cout << "moving center: " << bounding_sphere_center.x << " " << bounding_sphere_center.y << " " << bounding_sphere_center.z << " moving radius " << bounding_sphere_radius << std::endl;
	//std::cout << "other object center " << boundingsphere.x << " " << model.bounding_sphere_center.y << " " << model.bounding_sphere_center.z << " " << " moving radius " << model.bounding_sphere_radius << std::endl;
	// If the distance between the centers is less than the sum of the radii, then the spheres are colliding
	return distance < bounding_sphere_radius + rad;
}
void Model::box_bounding_box()
{
	bounding_box.minX = bounding_box.maxX = vertices_model[0].position.x;
	bounding_box.minY = bounding_box.maxY = vertices_model[0].position.y;
	bounding_box.minZ = bounding_box.maxZ = vertices_model[0].position.z;

	for (int i = 0; i < vertices_model.size(); i++)
	{
		bounding_box.minX = fmin(bounding_box.minX, vertices_model[i].position.x);
		bounding_box.maxX = fmax(bounding_box.maxX, vertices_model[i].position.x);
		bounding_box.minY = fmin(bounding_box.minY, vertices_model[i].position.y);
		bounding_box.maxY = fmax(bounding_box.maxY, vertices_model[i].position.y);
		bounding_box.minZ = fmin(bounding_box.minZ, vertices_model[i].position.z);
		bounding_box.maxZ = fmax(bounding_box.maxZ, vertices_model[i].position.z);
	}
	bounding_box.minX+=translation.x;
	bounding_box.minY += translation.y;
	bounding_box.minZ += translation.z;
	bounding_box.maxX += translation.x;
	bounding_box.maxY += translation.y;
	bounding_box.maxZ += translation.z;
}
bool Model::detect_collision_sphere_box(Model model) {
	//model.box_bounding_box();
	// Find the closest point on the box to the sphere
	float x = fmax(model.bounding_box.minX, fmin(bounding_sphere_center.x, model.bounding_box.maxX));
	float y = fmax(model.bounding_box.minY, fmin(bounding_sphere_center.y, model.bounding_box.maxY));
	float z = fmax(model.bounding_box.minZ, fmin(bounding_sphere_center.z, model.bounding_box.maxZ));

	// Calculate the distance between the closest point and the sphere
	float distance = std::sqrt((x - bounding_sphere_center.x) * (x - bounding_sphere_center.x) + (y - bounding_sphere_center.y) * (y - bounding_sphere_center.y) + (z - bounding_sphere_center.z) * (z - bounding_sphere_center.z));

	// Check if the distance is less than the radius
	return distance < bounding_sphere_radius;
}   
bool Model::detect_collision_box_box(Model model) {
	if (bounding_box.maxX < model.bounding_box.minX || bounding_box.minX> model.bounding_box.maxX) return false;
	if (bounding_box.maxY < model.bounding_box.minY || bounding_box.minY > model.bounding_box.maxY) return false;
	if (bounding_box.maxZ < model.bounding_box.minZ || bounding_box.minZ > model.bounding_box.maxZ) return false;
	return true;
}

void Model::fire_arrow_draw(Shader shader, Camera camera, Texture& Texture, glm::vec3& posit, glm::vec3 trans, glm::vec3 orientation) {
	if (first_arrow) {
		//std::cout << "arrow pos: " << translation.x + position.x << " " << translation.y + position.y << " " << " " << translation.z + position.z << "\n";
		//std::cout << "sphere moovemet for arrows " << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " << "\n";
		//std::cout << "buraya girdi \n";
		
		first_arrow = false;
	}
	trajectory = orientation;
	trajectory.y = 0;
	//std::cout << "translate before" << trans.x<<" " <<trans.y<<" "<<trans.z<<"\n";
	translation = trans +trajectory*2.5f;
	translation.y = trans.y;
	//std::cout << "translate after" << translation.x << " " << translation.y << " " << translation.z << "\n";
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	float pos =Model::position.y;
	// Assigns different transformations to each matrix
	float speed = 3.5f;
	
	glm::vec3 bounding_pos = bounding_sphere_center;
	
	/*std::cout << "before arrow pos: " << translation.x + position.x << " " << translation.y + position.y << " " << " " << translation.z + position.z << "\n";
	std::cout << "before sphere moovemet for arrows " << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " << "\n";*/	
	Model::position += speed * trajectory * 0.5f;
	bounding_sphere_center+= (speed * trajectory* 0.5f);
	bounding_sphere_center.y = bounding_pos.y;
	Model::position.y = bounding_pos.y;
	//std::cout << "arrow pos: " << translation.x + position.x << " " << translation.y + position.y << " " << " " << translation.z + position.z << "\n";
	//std::cout << "sphere moovemet for arrows " << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " << "\n";
	
	//std::cout << "bounding sphere for arrow " << bounding_sphere_center.x << " " 
		//<< bounding_sphere_center.y << " " << bounding_sphere_center.z << "\n";
		//camera.speed * camera.Orientation * 0.005f;
	
	view = glm::translate(view, position);
	view = glm::translate(view, translation);
	//change center
	//std::cout << position.x<<"     "<<position.y << position.z << std::endl;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	model = view * model;
	//bounding_sphere_center += trans;
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
void Model::delete_object() {
	glBindVertexArray(0);
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	vertices_model.clear();
	indices_model.clear();
} 
void Model::translate(glm::vec3 translation) {
	Model::translation = translation;
}
void Model::transportation(glm::vec3 new_trans) {
	bounding_sphere_center -= position;
	bounding_sphere_center -= translation;
	bounding_sphere_center += new_trans;
	std::cout << "moving center sphere after isinlanma: " << bounding_sphere_center.x << " "<< bounding_sphere_center.y << " " << bounding_sphere_center.z<< std::endl;
	position = glm::vec3(0);

	translation = new_trans;
	std::cout << "moving pos: " << position.x+translation.x << " "<< position.y + translation.y << " " << position.z + translation.z<< std::endl;
}
void Model::Draw_rotate(Shader shader, Camera camera, Texture& Texture, glm::vec3 trans) {
	translation = trans;
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Assigns different transformations to each matrix
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation += 6.05f;
	//std::cout << "rotation is" << " " << rotation << " \n";
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
void Model::increase_speed(float increament) {
	max_speed += increament;
}
void Model::collision_result_wall(glm::vec3 normal_raw) {
	bounding_sphere_center += old_pos - position;
	position = old_pos;
	glm::vec3 normal = glm::normalize(normal_raw);

	glm::vec3 reflected_speed = accel_speed - 2.0f * glm::dot(accel_speed, normal) * normal;
	accel_speed = reflected_speed * elast_coefficient;
	new_speed = accel_speed;
}
void Model::collision_result_tree() {
	bounding_sphere_center += old_pos - position;
	position = old_pos;
	accel_speed = glm::vec3(0.0f);
	new_speed = glm::vec3(0.0f);
}
