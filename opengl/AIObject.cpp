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
	start_astar = sc.now();
	start_arrows = sc.now();

	glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	// Loop through the vertices of the object
	for (int i = 0; i < model->vertices_model.size(); i++) {
		// Update the minimum and maximum values as necessary
		min.x = fmin(min.x, model->vertices_model[i].position.x);
		min.y = fmin(min.y, model->vertices_model[i].position.y);
		min.z = fmin(min.z, model->vertices_model[i].position.z);
	}
	position += -min.y;
	translation = position;
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

	glm::vec2 startPos = maze->GetMyCoordinate(position);
	glm::vec2 targetPos = maze->GetMyCoordinate(player->position + player->translation);

	if (maze->isThisWall(targetPos) || targetPos.x < 0 || targetPos.y < 0) {
		path_findable = false;
		return;
	}
	
	std::vector<glm::vec2> pathNew;
	path = pathNew;

	if (startPos == targetPos)
		return;
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
				//std::cout << "position x: " << currentPos.x << ", y: " << currentPos.y << "\n";
				currentPos = allHashMap[Stringify(currentPos)]->previous;
			}
			std::reverse(path.begin(), path.end());
			//std::cout << "path size: " << path.size() << "\n";
			//Delete dynamically created memory
			for (std::map<std::string, StarSearch*>::iterator it = allHashMap.begin(); it != allHashMap.end(); ++it) {
				if (it->second != NULL)
					delete it->second;
			}
			path_findable = true;
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
	glm::vec3 playerPos = player->position + player->translation;
	glm::vec3 monsterPos = position;
	glm::vec3 distanceVec = playerPos - monsterPos;
	float distance = sqrt(glm::dot(distanceVec, distanceVec));
	//std::cout << "distance: " << distance << "\n";

	if (distance > 1.0f * maze->mHeight * maze->scale_xz) {
		return STOP;
	}
	else {
		auto end = sc.now();
		auto time_span = static_cast<std::chrono::duration<double>>(end - start_astar);
		if (time_span.count() > allowedTimeSpanAStar) {
			AStarFindPath();
			/*for (int i = 0; i < path.size(); i++) {
				std::cout << "pathway (" << path[i].x << ", " << path[i].y << ")\n";
			}*/
			start_astar = sc.now();
		}
		if (path_findable) {
			if (areWeAdjacent()) {
				return CLOSEBY;
			}
			else if (isPathStraightLine()) {
				return STRAIGHTLINE;
			}
			else {
				return ASTARMOVE;
			}
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
	bounding_sphere_center.x += randXMove * signX * speed;
	bounding_sphere_center.z += randXMove * signZ * speed;
}

void AIObject::AStarMove()
{
	float speed = 0.2f;

	if (path.size() < 1) {
		//glm::vec3 direction = player->position + player->translation - position;
		//position.x += direction.x * speed * 0.05;
		//position.z += direction.z * speed * 0.05;
		//bounding_sphere_center.x += direction.x * speed * 0.05;
		//bounding_sphere_center.z += direction.z * speed * 0.05;
		return;
	}

	if (maze->GetMyCoordinate(position) == path[0])
		path.erase(path.begin() + 0);

	if (path.size() < 1)
		return;

	glm::vec3 direction = maze->MazeToWorldCoordinate(path[0]) - position;
	position.x += direction.x * speed * 0.1;
	position.z += direction.z * speed * 0.1;
	bounding_sphere_center.x += direction.x * speed * 0.1;
	bounding_sphere_center.z += direction.z * speed * 0.1;

}

bool AIObject::isPathStraightLine() {
	//std::cout << "isStraight?\n";
	//std::cout << "size: " << path.size() << "\n";
	if (path.size() <= 1)
		return true;
	//std::cout << "is really Straight?\n";

	glm::vec2 direction = path[0] - maze->GetMyCoordinate(position);
	for (int i = 1; i < path.size(); i++) {
		if (path[i] - path[i - 1] != direction)
			return false;
	}
	return true;
}

void AIObject::FireArrows() {
	auto end = sc.now();
	auto time_span = static_cast<std::chrono::duration<double>>(end - start_arrows);
	//std::cout << "arrow fired\n";
	
	if (time_span.count() > allowedTimeSpanArrows) {
		
		Model* arrow = new Model("s.obj");
		arrows.push_back(arrow);
		arrows_translation.push_back(bounding_sphere_center - glm::vec3(0.0f, 1.1f, 0.0f));
		arrows_orientation.push_back(glm::normalize(player->position + player->translation - position));
		start_arrows = sc.now();
	}
}

void AIObject::drawObject(Shader shader, Camera camera, Texture& texture) {
	if (movable)
	{
		MOVE nextMove = MonsterGetMove();
		////std::cout << "nextMove: " << nextMove << "\n";

		if (nextMove == RANDOM) {
			RandomMove();
		}
		else if(nextMove == STOP){}
		else if (nextMove == ASTARMOVE) {
			AStarMove();
		}
		else if (nextMove == STRAIGHTLINE) {
			//AStarMove();
			FireArrows();
		}
		else if (nextMove == CLOSEBY) {
			CloseByMove();
		}
	}

	model->Draw(shader, camera, texture, rotation, position, scale);
}
void AIObject::sphere_bounding_box() {
	glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	// Loop through the vertices of the object
	for (int i = 0; i < model->vertices_model.size(); i++) {
		// Update the minimum and maximum values as necessary
		min.x = fmin(min.x, model->vertices_model[i].position.x);
		min.y = fmin(min.y, model->vertices_model[i].position.y);
		min.z = fmin(min.z, model->vertices_model[i].position.z);
		max.x = fmax(max.x, model->vertices_model[i].position.x);
		max.y = fmax(max.y, model->vertices_model[i].position.y);
		max.z = fmax(max.z, model->vertices_model[i].position.z);
	}

	// Calculate the center of the bounding box
	if (first)
	{
		glm::vec3 center = (min + max) / 2.0f;
		bounding_sphere_center = center;
		bounding_sphere_center += position;
		bounding_sphere_radius = (glm::length(max - min) / 2.0f);//-0.002
		bounding_sphere_radius = bounding_sphere_radius * 60 / 100;
		first = false;

	}


	// Calculate the radius of the bounding sphere

}
void AIObject::transportation(glm::vec3 new_pos) {
	float old_y = position.y;
	bounding_sphere_center -= position;
	position = new_pos;
	
	bounding_sphere_center += position;
	bounding_sphere_center.y = old_y;
	position.y = old_y;
	
}
void AIObject::arrow_hit() {
	lives -= 1;
	if (lives <= 0) {
		glm::vec2 new_2d=maze->GetRandomEmptyCoordinates(glm::vec2(0), glm::vec2(2 * maze->mWidth + 1, 2 * maze->mHeight + 1));
		while (new_2d == maze->GetMyCoordinate(player->position + player->translation)) {
			new_2d = maze->GetRandomEmptyCoordinates(glm::vec2(0), glm::vec2(2 * maze->mWidth + 1, 2 * maze->mHeight + 1));

		}
		glm::vec3 new_3d = maze->MazeToWorldCoordinate(new_2d);
		lives = 5;
		std::vector<glm::vec2> pathNew;
		path = pathNew;
		transportation(new_3d);
		
	}
}

bool AIObject::areWeAdjacent() {
	if (path.size() <= 1)
		return true;
	return false;
}

void AIObject::CloseByMove()
{
	float speed = 0.2f;

	if (path.size() > 1) {
		return;
	}

	if (path.size() == 0) {
		glm::vec3 direction = player->position + player->translation - position;
		glm::vec3 oldPos = position;
		glm::vec3 oldCenter = bounding_sphere_center;
		model->bounding_sphere_center = bounding_sphere_center;
		model->bounding_sphere_radius = bounding_sphere_radius;
		
		position.x += direction.x * speed * 0.1;
		position.z += direction.z * speed * 0.1;
		bounding_sphere_center.x += direction.x * speed * 0.1;
		bounding_sphere_center.z += direction.z * speed * 0.1;

		std::vector<Model*> walls = maze->GetNeighboringWalls(position);
		for (Model* wall : walls) {
			if((*this).model->detect_collision_sphere_box((*wall))) {
				std::cout << "collision with wall somehow\n";
				position = oldPos;
				bounding_sphere_center = oldCenter;
			}
		}

		//std::vector<Model*> highTrees = maze->GetNeighboringTrees(position, ModelInfo::HIGH);
		//std::vector<Model*> middleTrees = maze->GetNeighboringTrees(position, ModelInfo::MEDIUM);
		//std::vector<Model*> lowTrees = maze->GetNeighboringTrees(position, ModelInfo::LOW);
		//for (int i = 0; i < highTrees.size(); i++) {
		//	if ((*this).model->detect_collision_sphere_box((*highTrees[i])) || (*this).model->detect_collision_sphere_box((*middleTrees[i])) || (*this).model->detect_collision_sphere_box((*lowTrees[i]))) {
		//		std::cout << "collision with tree somehow\n";
		//		position = oldPos;
		//		bounding_sphere_center = oldCenter;
		//	}
		//}

	}
	else {
		if (maze->GetMyCoordinate(position) == path[0])
			path.erase(path.begin() + 0);	

		if (path.size() == 1) {
			glm::vec3 direction = maze->MazeToWorldCoordinate(path[0]) - position;
			position.x += direction.x * speed * 0.1;
			position.z += direction.z * speed * 0.1;
			bounding_sphere_center.x += direction.x * speed * 0.1;
			bounding_sphere_center.z += direction.z * speed * 0.1;
		}
	}
}