#ifndef MAZE_GENERATOR_CLASS_H
#define MAZE_GENERATOR_CLASS_H
#include <vector>
#include <fstream>
#include <string>
#include<glm/glm.hpp>
#include "model.h"

class MazeGenerator {
public:
	MazeGenerator(int h, int w, int seed, int _scale_xz, int _scale_y);
	void CreateModels(const char* objPath);
	std::vector<Model> getModels();
	std::vector<glm::vec3> getTranslates();
	std::vector<std::string> maze;
private:
	int mWidth;
	int mHeight;
	const char* path;
	int scale_xz;
	int scale_y;
	std::vector<Model> models;
	std::vector<glm::vec3> translates;
};
#endif