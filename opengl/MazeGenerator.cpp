#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int h, int w, int seed, int _scale, int _scale_y) {
	mWidth = w, mHeight = h, scale_xz = _scale, scale_y = _scale_y;
	
	std::ostringstream oss;
	oss << "mazeGenerate/maze_" << mHeight << "_" << mWidth << "_" << seed << ".txt";
	std::string path_ = oss.str();
	path = path_.c_str();

	std::fstream newfile;
	std::vector<std::string> lines;
	
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

	for (int i = 0; i < maze.size(); i++) {

		for (int j = 0; j < maze[i].size(); j++) {
			if (maze[i][j] == '#') {
				glm::vec3 translate_loop = glm::vec3(0.4f * scale_xz * (j - mWidth), (0.4f / 2) * scale_y, 0.4f * scale_xz * (i - mHeight));
				Model scaledCube = model.ScaleModel(scale_xz, scale_y, scale_xz);
				translates.push_back(translate_loop);
				models.push_back(scaledCube);
			}
		}
	}
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
std::vector<Model> MazeGenerator::getModels() {
	return models;
}
std::vector<glm::vec3> MazeGenerator::getTranslates() {
	return translates;
}