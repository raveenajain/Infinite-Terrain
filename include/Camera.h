#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Camera {
public:
	// instance of a camera
	static Camera& instance(float xP, float zP);
	// constructor
  Camera(float x, float z);
	// view matrix
  glm::mat4 getViewMatrix();
	// return the position of the camera
  glm::vec3 getPosition();
  // use the mouse to move the camera
  void mouseMove(int x, int y);

private:
	// origin position
  glm::vec3 cameraPosition;
	// refernce point
  glm::vec3 centerRef;
	// up vector
  glm::vec3 upVector;
	// initial mouse positions
	float lastX;
	float lastY;
	// mouse yaw / pitch
	float yaw;
	float pitch;
	// true if first mouse position
	bool firstMouse;
	// for camera position
	float xPos;
	float zPos;
};

#endif
