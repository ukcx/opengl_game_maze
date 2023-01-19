#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include"Mesh.h"
#include "shaderClass.h"
#include "Camera.h"
#include <vector>
#include "texture.h"
#include "common.h"
#include <string> 
struct box {
	float minX = 0;
	float minY = 0;
	float minZ = 0;
	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;
};
class Model
{
private:
	void Inputs_movement(GLFWwindow* window, glm::vec3& position, Camera camera);
	
public:
	std::vector <Vertex> vertices_model;
	std::vector <GLuint> indices_model;
	const unsigned int width = 1600;
	const unsigned int height = 1600;
	glm::vec3 bounding_sphere_center;
	float bounding_sphere_radius;
	glm::vec3 translation=glm::vec3(0);
	box bounding_box;
	float rotation=0;
	bool first_arrow = true;
	enum type { normal, lit };
	
	//std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO1;
	VBO VBO1;
	// Generates Element Buffer Object and links it to indices
	EBO EBO1;
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
	glm::vec3 position;
	float speed= 0.2f;
	void increase_speed(float increament);
	glm::vec3 old_pos = glm::vec3(0);
	void moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position, float rotation, glm::vec3 trans);
	void moving_obj_draw(Shader shader, Camera camera, Texture& Texture, GLFWwindow* window, glm::vec3& position);
	void Draw(Shader shader, Camera camera, float rotation, glm::vec3 trans);
	void Draw(Shader shader, Camera camera, Texture& Texture, float rotation, glm::vec3 trans, glm::vec3 scale);
	void sphere_bounding_box();
	void sphere_bounding_box(glm::vec3 trans);
	void box_bounding_box();
	bool detect_collision_sphere(Model model);
	bool detect_collision_sphere_box(Model model);
	void Draw_rotate(Shader shader, Camera camera, Texture& Texture, glm::vec3 trans);
	bool detect_collision_box_box(Model model);
	void fire_arrow_draw(Shader shader, Camera camera, Texture& Texture, glm::vec3& position,glm::vec3 trasns);
	void translate(glm::vec3 translati);
	void delete_object();
	bool first = true;
	void collision_result();
	glm::vec3 trajectory;

	enum objects { wall, arrow, player, ai };
};
#endif


