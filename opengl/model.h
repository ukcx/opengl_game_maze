#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include"Mesh.h"
#include "shaderClass.h"
#include "Camera.h"
#include <vector>
#include "texture.h"
#include "common.h"

class Model
{
private:
	void Inputs_movement(GLFWwindow* window, glm::vec3& position, Camera camera);
	
public:
	std::vector <Vertex> vertices_model;
	std::vector <GLuint> indices_model;
	const unsigned int width = 1600;
	const unsigned int height = 1600;
	enum type { normal, lit };
	//std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO1;
	// Initializes the mesh
	Model(const char* path);
	Model(std::vector<Vertex> model_vertices, std::vector<GLuint> model_indices);
	Model(const char* path, int this_is_dumm_you_should_find_a_better_way_to_do_this);
	Model ScaleModel(float x_scale, float y_scale, float z_scale);
	void model_load(const char* path);
	void Draw(Shader shader, Camera camera, Texture& Texture, float rotation, glm::vec3 trans);
	void Draw(Shader shader, Camera camera, Texture& Texture);
	// Draws the mesh
	void Draw(Shader shader, Camera camera);
	void moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position, float rotation, glm::vec3 trans);
	void moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position);
	void Draw(Shader shader, Camera camera, float rotation, glm::vec3 trans);

};
#endif


