#pragma once
#ifndef OBJECTCLASSH
#define OBJECTCLASSH

#include"model.h"
#include"MazeGenerator.h"
#include<iostream>
#include<chrono>
#include<map>
#include<set>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Object {
	//enum type { Light, AI, Arrow, Player, Other };
public:
	Object(Model* _model, glm::vec3 _pos/*, glm::vec3 _orientation*/, glm::vec3 _scale, float _rot, bool _isMovable);
	void drawObject(GLFWwindow* window, Shader shader, Camera camera, Texture& Texture);
	//type typeOfObject;
	bool movable = false;
	glm::vec3 translation;
	glm::vec3 scale;
	float rotation;
	glm::vec3 position;
	Model* model;
	glm::vec3 bounding_sphere_center;
	float bounding_sphere_radius;
	//glm::vec3 orientation;

protected:
	//void Inputs_movement(GLFWwindow* window, Camera camera);

	
};

class AIObject : public Object {

private:
	MazeGenerator* maze;
	Model* player;
	std::string Stringify(glm::vec2 point);
	std::chrono::steady_clock sc;
	std::chrono::steady_clock::time_point start_astar;
	double allowedTimeSpanAStar = 3.0f;
	double allowedTimeSpanArrows = 7.0f;
	bool first=true;
	std::chrono::steady_clock::time_point start_arrows;

public:
	enum MOVE { RANDOM, ASTARMOVE, STRAIGHTLINE };
	AIObject(Model* _model, glm::vec3 _pos, glm::vec3 _scale, float _rot, bool _isMovable, MazeGenerator* _maze, Model* _player);
	void RandomMove();
	void AStarMove();
	int GetDistance(glm::vec2 point1, glm::vec2 point2);
	void AStarFindPath();
	void FireArrows();
	MOVE MonsterGetMove();
	std::vector<glm::vec2> path;
	void drawObject(Shader shader, Camera camera, Texture& Texture);
	bool isPathStraightLine();
	void sphere_bounding_box();
	std::vector<Model*> arrows;
	std::vector<glm::vec3> arrows_translation;
	std::vector<glm::vec3> arrows_orientation;
	void arrow_hit();
	void transportation(glm::vec3 new_trans);
	int lives = 5;
};

#endif