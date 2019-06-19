#ifndef OBJECT_H
#define OBJECT_H

#include "Shader.h"
#include "Camera.h"
#include "TERRAIN.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>
#include <vector>

class Object {
public:
  // constructor
  Object(unsigned int w, unsigned int l);
  // destructor
  ~Object();
  // create vertex and index buffers
  void buffer();
  // bind buffers
  void bind();
  // set MVP matrix and uniforms
  void setMatrix(int width, int height);
  // draw
  void render();
  // adds new terrain onto already existing terrain
  void addTiles(int offsetX, int offsetY);
  // make the terrain more or less bumpy
  void editPeaks(std::string bump);  
private:
  Shader shader;
  glm::mat4 projectionMatrix;
  // vertex buffer object
  GLuint vertexBuffer;
  // index buffer object
  GLuint indexBuffer;
  // vertex array object
  GLuint vertexArrayObject;
  // terrain dimensions
  unsigned int width;
  unsigned int length;
  // terrain
  TERRAIN* ter;
  // offset for terrain movement
  int offsetX;
  int offsetZ;
};

#endif
