#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
private:
	void Inputs_movement(GLFWwindow* window, glm::vec3& position);
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	//std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO1;
	unsigned int width=1600;
	unsigned int height=1600;
	
	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, unsigned int width,unsigned int height);
	void Draw(Shader shader, Camera camera,Texture& Texture,float rotation, glm::vec3 trans);
	// Draws the mesh
	void moving_obj_draw(Shader shader, Camera camera, Texture& brickTex,GLFWwindow* window, glm::vec3& position, float rotation,glm::vec3 trans);
};
#endif