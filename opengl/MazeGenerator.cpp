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