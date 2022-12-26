
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <string>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
	void SetMatrix4(const char *name, glm::mat4 sended_thing);
	void SetFloat(const char* name, float value);
	void SetInteger(const char* name, int value);
	void SetVector2f(const char* name, float x, float y);
	void SetVector2f(const char* name, const glm::vec2& value);
	void SetVector3f(const char* name, float x, float y, float z);
	void SetVector3f(const char* name, const glm::vec3& value);
	void SetVector4f(const char* name, float x, float y, float z, float w);
	void SetVector4f(const char* name, const glm::vec4& value);

private:
	void compileErrors(unsigned int shader, const char* type);

};
#endif