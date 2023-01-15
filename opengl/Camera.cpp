#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	old_pos = position;
	position_if_collision = position;
}
void Camera::updateDirectly(glm::mat4 view, glm::mat4 perspective) {
	cameraMatrix = perspective * view;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	// Sets new camera matrix
	cameraMatrix = projection * view;
	// Exports the camera matrix to the Vertex Shader
	//glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}
void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

float slow = 0.01;
void Camera::Inputs(GLFWwindow* window, glm::vec3 playerPos)
{
	// Handles key inputs
	float posY = Position.y;
	position_if_collision = Position;

	if (godMode) {

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//position_if_collision = Position;
			std::cout << "positio of olds is " << position_if_collision.x << " " << position_if_collision.z << " " << "\n";
			Position += speed * Orientation * slow;
			Position.y = posY;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//position_if_collision = Position;
			Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * slow;
			Position.y = posY;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//position_if_collision = Position;
			Position += speed * -Orientation * slow;
			Position.y = posY;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//position_if_collision = Position;
			Position += speed * glm::normalize(glm::cross(Orientation, Up)) * slow;
			Position.y = posY;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && godMode)
		{
			Position += speed * Up * slow;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && godMode)
		{
			Position += speed * -Up * slow;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			Up = -Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 30.0f;//4.4f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = 10.0f;
		}
	}
	else {
		Position = playerPos + glm::vec3(0.0f, 2.0f, 0.0f) + Orientation * glm::vec3(-4.0f, 0.0f, -4.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		godMode = !godMode;
		//if (!godMode)
		//{
		//	Position = old_pos;
		//	//position_if_collision = old_pos;
		//}
		//	

		//else {
		//	old_pos = Position;
		//}
	}
	

	

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			/*
			double mouseX_1;
			double mouseY_1;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX_1, &mouseY_1);

			std::cout << "before press: " << Position.x << " " << Position.y << " " << Position.z << "\n";
			Position += glm::normalize( glm::vec3(mouseX_1, mouseY_1, 0)) * 2.0f;
			Position += Orientation * 2.f;
			std::cout << "after press: " << Position.x << " " << Position.y << " " << Position.z << "\n";
			*/

			// Fetches the coordinates of the cursor
			/*

			glfwGetCursorPos(window, &mouseX_1, &mouseY_1);
			std::cout << "before press: " << Position.x << " " << Position.y << " " << Position.z << "\n";
			std::cout << "x is: "<<mouseX_1<< " y is"<<mouseY_1<<" normalize x is " << glm::normalize(glm::vec3(mouseX_1, mouseY_1, 0)).x << "\n";
			Position +=glm::normalize(glm::vec3(mouseX_1,mouseY_1,0));
			std::cout << "after press: " << Position.x << " " << Position.y << " " << Position.z << "\n";
			*/
				
			if (godMode) {
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					Position += Orientation * 3.f;
				}
				else {
					Position -= Orientation * 3.f;
				}
			}
			glfwSetCursorPos(window, (width / 2), (height / 2));
			// += Orientation * 5.f;
			firstClick = false;
			std::cout << "camera after click: " << Position.x << " " << Position.y << " " << Position.z << "\n";
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);


		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{

			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE|| glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
	

}
void Camera::changepos(float increament) {
	Position +=increament *Orientation;
}
void Camera::collision_pos() {
	Position = position_if_collision;
}