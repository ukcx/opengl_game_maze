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
	std::vector<glm::vec2> GetNeighbors(glm::vec2 currentPos);
	std::vector<Model> getModels_coins();
	std::vector<glm::vec3> coin_getTranslates();
	glm::vec2 GetRandomEmptyCoordinates(glm::vec2 lowerBound, glm::vec2 upperBound);
	glm::vec3 MazeToWorldCoordinate(glm::vec2 mazeCoordinate);
	std::vector<Model*> getModels();
	std::vector<glm::vec3> getTranslates();
	std::vector<std::vector<Model*>> maze_models;
	std::vector<std::string> maze;
	glm::vec2 GetMyCoordinate(glm::vec3 pos);
	std::vector<Model*> GetNeighboringWalls(glm::vec3 myPos);
	~MazeGenerator();
	int mWidth;
	int mHeight;
	const char* path;
	int scale_xz;
	int scale_y;
private:
	std::vector<Model> coins;
	std::vector<glm::vec3> coins_translates;
	std::vector<Model*> models;
	std::vector<glm::vec3> translates;
};
#endif