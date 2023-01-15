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
void Model::Inputs_movement(GLFWwindow* window, glm::vec3& pos, Camera camera)
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

	//if (!camera.godmode) {
	//	float posy = position.y;
	//	// handles key inputs
	//	position = camera.position + camera.orientation * glm::vec3(4.0f, 4.0f, 4.0f);
	//	position.y = posy;
	//	glm::vec3 objectcenter = position + camera.orientation * glm::vec3(0.5f, 0.5f, 0.0f);

	//	// update the center of the bounding sphere
	//	bounding_sphere_center = objectcenter;
	//}
	if (!camera.godMode) {
		float posY = position.y;
		old_pos = position;
		float bounding_y = bounding_sphere_center.y;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position += speed * camera.Orientation ;
			position.y = posY;
			
			bounding_sphere_center += speed * camera.Orientation;
			
			bounding_sphere_center.y = bounding_y;
			std::cout << "sphere moovemet" << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " <<"\n";

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position += speed * -glm::normalize(glm::cross(camera.Orientation, camera.Up));
			position.y = posY;
			bounding_sphere_center += speed * -glm::normalize(glm::cross(camera.Orientation, camera.Up));
			bounding_sphere_center.y = bounding_y;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position += speed * -camera.Orientation ;
			position.y = posY;
			bounding_sphere_center += speed * -camera.Orientation;
			bounding_sphere_center.y = bounding_y;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position += speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));
			position.y = posY;
			bounding_sphere_center += speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));
			bounding_sphere_center.y = bounding_y;
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
	model = glm::scale(view, scale);
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
	Inputs_movement(window, position, camera);
	view = glm::translate(view, position);
	view = glm::translate(view, trans);
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
		first = false;

	}
	

	// Calculate the radius of the bounding sphere
	bounding_sphere_radius = (glm::length(max - min) / 2.0f);//-0.002
}

bool Model::detect_collision_sphere(Model model) {
	model.sphere_bounding_box();
	float distance = glm::length(bounding_sphere_center - model.bounding_sphere_center);
	std::cout << "moving center: " << bounding_sphere_center.x << " "<< bounding_sphere_center.y << " " << bounding_sphere_center.z<< " moving radius " << bounding_sphere_radius << std::endl;
	std::cout << "other object center " << model.bounding_sphere_center.x << " " << model.bounding_sphere_center.y << " " << model.bounding_sphere_center.z << " " << " moving radius " << model.bounding_sphere_radius << std::endl;
	// If the distance between the centers is less than the sum of the radii, then the spheres are colliding
	return distance < bounding_sphere_radius + model.bounding_sphere_radius;
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
	model.box_bounding_box();
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

void Model::fire_arrow_draw(Shader shader, Camera camera, Texture& Texture, glm::vec3& position, glm::vec3 trans) {

	translation = trans;
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Simple timer

	// Initializes matrices so they are not the null matrix

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	float pos = position.y;
	// Assigns different transformations to each matrix
	float speed = 2.05f;
	position += speed* camera.Orientation * 0.5f;
	glm::vec3 bounding_pos = bounding_sphere_center;
	if (first) {
		trajectory = camera.Orientation;
		first = false;
	}
	bounding_sphere_center+= (speed * trajectory* 0.5f);
	bounding_sphere_center.y = bounding_pos.y;
	std::cout << "sphere moovemet for arrows " << bounding_sphere_center.x << "   " << bounding_sphere_center.y << "   " << bounding_sphere_center.z << "   " << "\n";
	
	//std::cout << "bounding sphere for arrow " << bounding_sphere_center.x << " " 
		//<< bounding_sphere_center.y << " " << bounding_sphere_center.z << "\n";
		//camera.speed * camera.Orientation * 0.005f;
	position.y = pos;
	view = glm::translate(view, position);
	view = glm::translate(view, trans);
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
	rotation += 15.05f;
	std::cout << "rotation is" << " " << rotation << " \n";
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
	speed += increament;
}