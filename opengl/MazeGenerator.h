#ifndef MAZE_GENERATOR_CLASS_H
#define MAZE_GENERATOR_CLASS_H
#include <vector>
#include <fstream>
#include <string>
#include<glm/glm.hpp>
#include "model.h"

struct ModelInfo {
	enum modelType {WALL, COIN, TREE};
	enum modelLoad {LOW, MEDIUM, HIGH};

	modelType type;
	Model* lowModel;
	Model* mediumModel;
	Model* highModel;

	ModelInfo() {
		type = WALL;
		lowModel = nullptr;
		mediumModel = nullptr;
		highModel = nullptr;
	};
	ModelInfo(modelType mt, Model* low, Model* medium = nullptr, Model* high = nullptr) {
		type = mt;
		lowModel = low;
		mediumModel = medium;
		highModel = high;
	}
	Model* getModel(modelLoad ml = LOW) {
		if (ml == LOW)
			return lowModel;
		else if (ml == MEDIUM)
			return mediumModel;
		else
			return highModel;
	}
	modelType getModelType() {
		return type;
	}
};

class MazeGenerator {
public:
	MazeGenerator(int h, int w, int seed, int _scale_xz, int _scale_y);
	void CreateModels(const char* objPath);
	std::vector<glm::vec2> GetNeighbors(glm::vec2 currentPos);
	std::vector<Model*> getModels_low_coins();
	std::vector<Model*> getModels_middle_coins();
	std::vector<Model*> getModels_high_coins();
	std::vector<Model*> getModels_low_tree();
	std::vector<Model*> getModels_middle_tree();
	std::vector<Model*> getModels_high_tree();
	std::vector<glm::vec3> coin_getTranslates();
	std::vector<glm::vec3> tree_getTranslates();
	bool isItFarDistance(glm::vec3 cameraPos, glm::vec3 objectPos);
	bool isMiddleDistance(glm::vec3 cameraPos, glm::vec3 objectPos);
	//std::vector<glm::vec3> midle_tree_getTranslates();
	glm::vec2 GetRandomEmptyCoordinates(glm::vec2 lowerBound, glm::vec2 upperBound);
	glm::vec3 MazeToWorldCoordinate(glm::vec2 mazeCoordinate);
	std::vector<Model*> getModels();
	std::vector<glm::vec3> getTranslates();
	std::vector<std::vector<ModelInfo>> maze_models;
	std::vector<std::string> maze;
	glm::vec2 GetMyCoordinate(glm::vec3 pos);
	std::vector<Model*> GetNeighboringWalls(glm::vec3 myPos);
	std::vector<Model*> GetNeighboringCoins(glm::vec3 myPos, ModelInfo::modelLoad ml = ModelInfo::LOW);
	std::vector<Model*> GetNeighboringTrees(glm::vec3 myPos, ModelInfo::modelLoad ml = ModelInfo::LOW);
	bool isThisWall(glm::vec2 mazeCoord);
	~MazeGenerator();
	int mWidth;
	int mHeight;
	const char* path;
	int scale_xz;
	int scale_y;
	
private:
	std::vector<Model*> low_coins;
	std::vector<Model*> middle_coins;
	std::vector<Model*> high_coins;
	std::vector<Model*> low_trees;
	std::vector<Model*> middle_trees;
	std::vector<Model*> high_trees;
	std::vector<glm::vec3> coins_translates;
	std::vector<glm::vec3> tree_translates;
	std::vector<Model*> models;
	std::vector<glm::vec3> translates;
};
#endif