#ifndef MATERIAL_H
#define MATERIAL_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"shaderClass.h"
class Material
{
private:
	float ambient;
	float diffuse;
	float specular;


public:
	Material(
		float ambient,
		float diffuse,
		float specular

	)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;

	}

	~Material() {}

	//Function
	void sendToShader(Shader& program)
	{
		program.Activate();
	    
		glUniform1f(glGetUniformLocation(program.ID, "material.ambient"),  this->ambient);
		glUniform1f(glGetUniformLocation(program.ID, "material.diffuse"), (this->diffuse));
		glUniform1f(glGetUniformLocation(program.ID, "material.specular"),(this->specular));
		
	}
};
#endif

