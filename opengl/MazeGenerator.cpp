#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int h, int w, int seed, int _scale, int _scale_y) {
	mWidth = w, mHeight = h, scale_xz = _scale, scale_y = _scale_y;
	
	std::ostringstream oss;
	oss << "mazeGenerate/maze_" << mHeight << "_" << mWidth << "_" << seed << ".txt";
	std::string path_ = oss.str();
	path = path_.c_str();

	std::fstream newfile;
	std::vector<std::string> lines;

	for (int i = 0; i < mHeight * 2 + 1; i++) {
		std::vector<Model*> modelLine;
		for (int j = 0; j < mWidth * 2 + 1; j++) {
			modelLine.push_back(nullptr);
		}
		maze_models.push_back(modelLine);
	}
	//std::cout << maze_models.size();
	
	newfile.open(path, std::ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()) {   //checking whether the file is open
		std::string tp;
		while (getline(newfile, tp)) { //read data from file object and put it into string.
			lines.push_back(tp);
		}
		newfile.close(); //close the file object.
		lines[1] = " " + lines[1].substr(1, lines[1].length());
		lines[lines[1].length() - 2] = lines[lines[1].length() - 2].substr(0, lines[lines[1].length() - 2].length() - 1) + " ";

		maze = lines;
		std::cout << "Maze created successfully\n";
	}
	else {
		std::cout << "Could not open file! Check file path!\n";
	}	
}
MazeGenerator::~MazeGenerator() {
	for (int i = 0; i < mHeight * 2 + 1; i++) {
		for (int j = 0; j < mWidth * 2 + 1; j++) {
			if (maze_models[i][j] != nullptr)
				delete maze_models[i][j];
		}
	}
}
glm::vec2 MazeGenerator::GetMyCoordinate(glm::vec3 pos) {

	//std::cout << pos.x << "\n";
	//float x_lower = (pos.x - (0.2f * scale_xz)) / (0.4 * scale_xz);
	//float x_upper = (pos.x + (0.2f * scale_xz)) / (0.4 * scale_xz);
	//int x = (x_lower + x_upper) / 2;
	float x_raw = (pos.x) / (0.4 * scale_xz);
	int incrementX = (x_raw < 0.0f) ? -1 : 1;
	int x = abs(x_raw - (int)x_raw) < 0.5 ? (int)x_raw : (int)x_raw + incrementX;

	float z_raw = (pos.z) / (0.4 * scale_xz);
	int incrementZ = (z_raw < 0.0f) ? -1 : 1;
	int z = abs(z_raw - (int)z_raw) < 0.5 ? (int)z_raw : (int)z_raw + incrementZ;
	//float z_lower = (pos.z - (0.2f * scale_xz)) / (0.4 * scale_xz);
	//float z_upper = (pos.z + (0.2f * scale_xz)) / (0.4 * scale_xz);
	//int z = (z_lower + z_upper) / 2;
	return glm::vec2(mWidth + x, mHeight + z);
}
void MazeGenerator::CreateModels(const char* objPath) {
	Model model(objPath);
	Model coin("coin_low.obj");
	Model tree("low_tree.obj",true);
	Model tree_high("middle_tree.obj", true);
	//Model tree("low_tree.obj", true);
	for (int i = 0; i < maze.size(); i++) {

		for (int j = 0; j < maze[i].size(); j++) {
			if (maze[i][j] == '#') {
				glm::vec3 translate_loop = glm::vec3(0.4f * scale_xz * (j - mWidth), (0.4f / 2) * scale_y, 0.4f * scale_xz * (i - mHeight));
				Model* scaledCube = new Model(model.ScaleModel(scale_xz, scale_y, scale_xz));
				translates.push_back(translate_loop);
				models.push_back(scaledCube);
				glm::vec2 maze_coords = GetMyCoordinate(translate_loop);
				//count++;
				//std::cout << "here " << count << "th time\n";
				maze_models[maze_coords.x][maze_coords.y] = scaledCube;
			}
			else {
				int irand = rand() % 10 + 1;
				if (irand == 6) {
					//glm::vec3 translate_loop = glm::vec3( (j - mWidth), (0.4f / 2) * scale_y,  (i - mHeight));
					glm::vec3 translate_loop = glm::vec3(0.4f * scale_xz * (j - mWidth), 0.5, 0.4f * scale_xz * (i - mHeight));
					coins.push_back(coin);
					coins_translates.push_back(translate_loop);

				}
				if (irand == 1) {
					//glm::vec3 translate_loop = glm::vec3( (j - mWidth), (0.4f / 2) * scale_y,  (i - mHeight));
					glm::vec3 translate_loop_tree = glm::vec3(0.4f * scale_xz * (j - mWidth)-0.15f*scale_xz, 2.1, 0.4f * scale_xz * (i - mHeight)+ 0.15f * scale_xz);
					low_trees.push_back(tree);
					middle_trees.push_back(tree_high);
					tree_translates.push_back(translate_loop_tree);

				}
			}
		}
	}
}
std::vector<Model*> MazeGenerator::GetNeighboringWalls(glm::vec3 myPos) {
	std::vector<Model*> neighboringModels;
	glm::vec2 mazePos = GetMyCoordinate(myPos);
	//std::cout << "mazePos is " << mazePos.x << ", " << mazePos.y << "\n";
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0)
				continue;
			int checkX = mazePos.x + x;
			int checkY = mazePos.y + y;
			if (checkX >= 0 && checkX < mWidth * 2 + 1 && checkY >= 0 && checkY < mHeight * 2 + 1) {
				//std::cout << "here\n";
				if (maze_models[checkX][checkY] == nullptr) {
					//std::cout << "here3\n";
					continue;
				}
				else {
					//std::cout << (*maze_models[checkX][checkY]).rotation << "\n";
					neighboringModels.push_back(maze_models[checkX][checkY]);
				}
				//std::cout << "here2\n";
			}
		}
	}
	return neighboringModels;
}
glm::vec2 MazeGenerator::GetRandomEmptyCoordinates(glm::vec2 lowerBound, glm::vec2 upperBound) {
	srand(time(0));
	int rangeX = upperBound.x - lowerBound.x;
	int rangeY = upperBound.y - lowerBound.y;
	int xVal, yVal;

	do {
		xVal = lowerBound.x + (rand() % rangeX);
		yVal = lowerBound.y + (rand() % rangeY);
	} while (maze[yVal][xVal] == '#');

	return glm::vec2(xVal, yVal);
}
glm::vec3 MazeGenerator::MazeToWorldCoordinate(glm::vec2 mazeCoordinate) {
	return glm::vec3(0.4f * scale_xz * (mazeCoordinate.x - mWidth), 0.4f, 0.4f * scale_xz * (mazeCoordinate.y - mHeight));
}

std::vector<glm::vec2> MazeGenerator::GetNeighbors(glm::vec2 currentPos) {
	std::vector<glm::vec2> neighbours;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == -1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == -1))
				continue;

			int checkX = currentPos.x + x;
			int checkY = currentPos.y + y;

			if (checkX >= 0 && checkX < mWidth * 2 + 1 && checkY >= 0 && checkY < mHeight * 2 + 1) {
				if (maze[checkY][checkX] == '#')
					continue;
				else
					neighbours.push_back(glm::vec2(checkX, checkY));
			}

		}
	}

	return neighbours;
}
//void MazeGenerator::CreateModels(const char* objPath) {
//	Model model(objPath);
//
//	for (int i = 0; i < maze.size(); i++) {
//		int wall_start = 0;
//		bool wallStarted = false;
//
//		for (int j = 0; j <= maze[i].size(); j++) {
//			if (maze[i][j] == '#' && !wallStarted) {
//				wallStarted = true;
//				wall_start = j;
//			}
//			else if ((j == maze[i].size() || maze[i][j] != '#') && wallStarted) {
//				float x_scale = (j - wall_start) * scale_xz;
//				glm::vec3 translate_loop = glm::vec3(0.4f * scale_xz * (((j + wall_start) / 2) - mWidth), 0.2f * scale_y, 0.4f * scale_xz * (i - mHeight));
//				translates.push_back(translate_loop);
//				Model scaledCube = model.ScaleModel(x_scale, scale_y, scale_xz);
//				models.push_back(scaledCube);
//				wallStarted = false;
//			}
//		}
//	}
//}
bool MazeGenerator::isMiddleDistance(glm::vec3 cameraPos, glm::vec3 objectPos) {
	glm::vec3 distance = cameraPos - objectPos;
	float dist = sqrt(glm::dot(distance, distance));

	if(dist < 3 * 0.4f * scale_xz){
		return true;
	}
	return false;
}
bool MazeGenerator::isItFarDistance(glm::vec3 cameraPos, glm::vec3 objectPos) {
	glm::vec3 distance = cameraPos - objectPos;
	float dist = sqrt(glm::dot(distance, distance));

	if (dist >= 3 * 0.4f * scale_xz) {
		return true;
	}
	return false;
}
std::vector<Model*> MazeGenerator::getModels() {
	return models;
}
std::vector<Model> MazeGenerator::getModels_coins() {
	return coins;
}
std::vector<Model> MazeGenerator::getModels_low_tree() {
	return low_trees;
}
std::vector<Model> MazeGenerator::getModels_middle_tree() {
	return middle_trees;
}
std::vector<glm::vec3> MazeGenerator::getTranslates() {
	return translates;
}
std::vector<glm::vec3> MazeGenerator::tree_getTranslates() {
	return tree_translates;
}
std::vector<glm::vec3> MazeGenerator::coin_getTranslates() {
	return coins_translates;
}