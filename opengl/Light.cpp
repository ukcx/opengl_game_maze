#include"Light.h"
Light::Light(glm::vec4 color, glm::vec3 position) {
	lightColor = color;
	lightPos = position;
	lightModel = glm::translate(lightModel, lightPos);
}
void Light::light_conf(Shader shader) {
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}
void Light::light_conf(Shader shader, int delete_this_later_and_find_a_better_way_to_do_this) {
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
}