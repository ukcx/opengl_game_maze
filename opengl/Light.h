#ifndef LIGHT_H
#define lIGHT_CLASS_H
#include <glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
#include<glm/gtc/matrix_transform.hpp>
class Light {
public:
	glm::vec4 lightColor;
	glm::vec3 lightPos;
	glm::mat4 lightModel = glm::mat4(1.0f);
	Light(glm::vec4 color, glm::vec3 position);
	void light_conf(Shader shader);
	void light_conf(Shader shader ,int delete_this_later_and_find_a_better_way_to_do_this);


};
	
	
#endif
