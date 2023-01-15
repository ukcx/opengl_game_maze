#include "AIObject.h"

Object::Object(Model* _model, glm::vec3 _pos/*, glm::vec3 _orientation*/, glm::vec3 _scale, float _rot, bool _isMovable) {
	movable = _isMovable;
	translation = _pos;
	position = _pos;
	//orientation = _orientation;
	scale = _scale;
	rotation = _rot;
	model = _model;
}


void Object::drawObject(GLFWwindow* window, Shader shader, Camera camera, Texture& texture) {
	//if (movable)
		//Inputs_movement(window, camera);

	model->Draw(shader, camera, texture, rotation, position, scale);
}

AIObject::AIObject(Model* _model, glm::vec3 _pos, glm::vec3 _scale, float _rot, bool _isMovable, MazeGenerator* _maze, Model* _player)
	: Object(_model, _pos, _scale, _rot, _isMovable)
{
	maze = _maze;
	player = _player;
	AStarFindPath();
	start = sc.now();
	//std::cout << "x: " <<  position.x << "y: " << position.y << "z: " << position.z;
}

struct StarSearch {
	int gCost = 0;
	int hCost = 0;
	glm::vec2 previous = glm::vec2(-1.0f);

	StarSearch();
	StarSearch(int _gCost, int _hCost, glm::vec2 _prevPos = glm::vec2(-1.0f))
	{
		gCost = _gCost;
		hCost = _hCost;
		previous = _prevPos;
	}

	int getFCost() {
		return gCost + hCost;
	}
};

void AIObject::AStarFindPath() {
	//std::cout << "here\n";
	//std::vector<glm::vec2> pathNew;
	//path = pathNew;

	glm::vec2 startPos = maze->GetMyCoordinate(position);
	glm::vec2 targetPos = maze->GetMyCoordinate(player->position + player->translation);
	//std::cout << "start pos, x: " << startPos.x << ", y: " << startPos.y << "\n";
	//std::cout << "target pos, x: " << targetPos.x << ", y: " << targetPos.y << "\n";

	std::vector<glm::vec2> openSet;
	std::map<std::string, StarSearch*> allHashMap;
	std::set<std::string> openHashSet;
	std::set<std::string> closedHashSet;

	openSet.push_back(startPos);
	openHashSet.insert(Stringify(startPos));
	allHashMap[Stringify(startPos)] = new StarSearch(0, GetDistance(startPos, targetPos));

	while (openSet.size() > 0) {
		//std::cout << "openset size: " << openSet.size() << "\n";
		//std::make_heap(openSet.begin(), openSet.end());
		glm::vec2 currentPos = openSet[0];
		int removeIndex = 0;
		for (int i = 0; i < openSet.size(); i++) {
			if (allHashMap[Stringify(openSet[i])]->getFCost() < allHashMap[Stringify(currentPos)]->getFCost()
				|| (allHashMap[Stringify(openSet[i])]->getFCost() == allHashMap[Stringify(currentPos)]->getFCost() &&
					allHashMap[Stringify(openSet[i])]->hCost < allHashMap[Stringify(currentPos)]->hCost)) {
				currentPos = openSet[i];
				removeIndex = i;
			}
		}

		openSet.erase(openSet.begin() + removeIndex);
		openHashSet.erase(Stringify(currentPos));
		closedHashSet.insert(Stringify(currentPos));

		if (currentPos == targetPos) {
			//Retrace Path
			//std::cout << "path found\n";
			while (currentPos != startPos) {
				path.push_back(currentPos);
				currentPos = allHashMap[Stringify(currentPos)]->previous;
			}
			std::reverse(path.begin(), path.end());
			//std::cout << "path size: " << path.size() << "\n";
			//Delete dynamically created memory
			for (std::map<std::string, StarSearch*>::iterator it = allHashMap.begin(); it != allHashMap.end(); ++it) {
				if (it->second != NULL)
					delete it->second;
			}
			return;
		}

		std::vector<glm::vec2> neighbours = maze->GetNeighbors(currentPos);
		for (glm::vec2 neighbour : neighbours) {
			//std::cout << "neighbour x: " << neighbour.x << ", y: " << neighbour.y << "\n";
			if (closedHashSet.find(Stringify(neighbour)) != closedHashSet.end())
				continue;

			int movementCostToNeighbour = allHashMap[Stringify(currentPos)]->gCost + GetDistance(currentPos, neighbour);
			if (openHashSet.find(Stringify(neighbour)) == openHashSet.end() || allHashMap[Stringify(neighbour)]->gCost > movementCostToNeighbour) {

				if (openHashSet.find(Stringify(neighbour)) == openHashSet.end()) {
					openSet.push_back(neighbour);
					//std::cout << "pushed new point\n";
					openHashSet.insert(Stringify(neighbour));
				}

				StarSearch* neighbourAStar = new StarSearch(movementCostToNeighbour, GetDistance(neighbour, targetPos), currentPos);
				allHashMap[Stringify(neighbour)] = neighbourAStar;
			}

		}
	}
}

std::string AIObject::Stringify(glm::vec2 point) {
	return std::to_string(point.x) + "-/-" + std::to_string(point.y);
}

int AIObject::GetDistance(glm::vec2 point1, glm::vec2 point2) {
	int distX = abs(point1.x - point2.x);
	int distY = abs(point1.y - point2.y);

	if (distX > distY)
		return 10 * (distX + distY);//14 * distY + 10 * (distX - distY);
	else
		return 10 * (distX + distY);//14 * distX + 10 * (distY - distX);
}

AIObject::MOVE AIObject::MonsterGetMove() {
	glm::vec2 playerPos = maze->GetMyCoordinate(player->position);
	glm::vec2 monsterPos = maze->GetMyCoordinate(position);
	glm::vec2 distanceVec = playerPos - monsterPos;
	float distance = sqrt(glm::dot(distanceVec, distanceVec));
	//std::cout << "distance: " << distance << "\n";

	if (distance > 4.0f * maze->mHeight) {
		return RANDOM;
	}
	else {
		auto end = sc.now();
		auto time_span = static_cast<std::chrono::duration<double>>(end - start);
		if (time_span.count() > allowedTimeSpan) {
			AStarFindPath();
			/*for (int i = 0; i < path.size(); i++) {
				std::cout << "pathway (" << path[i].x << ", " << path[i].y << ")\n";
			}*/
			start = sc.now();
		}

		if (isPathStraightLine()) {
			return STRAIGHTLINE;
		}
		else {
			return ASTARMOVE;
		}
	}
}

void AIObject::RandomMove()
{
	float speed = 0.2f;
	//create a random number between 0.0f and 1.0f
	float randXMove = 0.0f + static_cast <float>  (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.0f)));
	float randZMove = 1 - randXMove;
	srand((unsigned)time(NULL));
	float signX = 1 + (rand() % 2) == 1 ? -1.0f : 1.0f;
	float signZ = 1 + (rand() % 2) == 1 ? -1.0f : 1.0f;

	position.x += randXMove * signX * speed;
	position.z += randZMove * signZ * speed;
}

void AIObject::AStarMove()
{
	float speed = 0.2f;

	if (path.size() <= 1)
		return;

	if (maze->GetMyCoordinate(position) == path[0])
		path.erase(path.begin() + 0);

	if (path.size() <= 1)
		return;

	glm::vec3 direction = maze->MazeToWorldCoordinate(path[0]) - position;
	position.x += direction.x * speed * 0.1;
	position.z += direction.z * speed * 0.1;
}

bool AIObject::isPathStraightLine() {
	//std::cout << "isStraight?\n";
	//std::cout << "size: " << path.size() << "\n";
	if (path.size() <= 2)
		return true;
	//std::cout << "is really Straight?\n";
	bool straightLine = true;
	glm::vec2 direction = path[1] - path[0];
	for (int i = 2; i < path.size(); i++) {
		if (path[i] - path[i - 1] != direction)
			return false;
	}
	return true;
}

void AIObject::drawObject(Shader shader, Camera camera, Texture& texture) {
	if (movable)
	{
		MOVE nextMove = MonsterGetMove();
		//std::cout << "nextMove: " << nextMove << "\n";

		if (nextMove == RANDOM) {
			//RandomMove();
		}
		else if (nextMove == ASTARMOVE) {
			AStarMove();
		}
		else if (nextMove == STRAIGHTLINE) {
			AStarMove();
			//extra functions
		}

	}

	model->Draw(shader, camera, texture, rotation, position, scale);
}