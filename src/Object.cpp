//Source: notes, https://learnopengl.com/Getting-started/Hello-Triangle,
//        http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
#include "Object.h"

// constructor
Object::Object(unsigned int w, unsigned int l): width(w), length(l) {
  // initialize terrain
  ter = new TERRAIN(width, length);
  offsetX = 0;
  offsetZ = 0;
  // buffers
  buffer();
  // shaders
  std::string vertexString = shader.toString("./shaders/vert.glsl");
  std::string fragmentString = shader.toString("./shaders/frag.glsl");
  shader.createShaders(vertexString, fragmentString);
}

// destructor
Object::~Object(){
  delete ter;
}

// "adds" new terrain onto already existing terrain
void Object::addTiles(int oX, int oZ) {
  offsetX = oX;
  offsetZ = oZ;
  ter->createPlane(offsetX, offsetZ);
  buffer();
}

// make the terrain more or less bumpy
void Object::editPeaks(std::string bump) {
  if (bump == "increase") {
    ter->increasePeaks();
  } else if (bump == "decrease") {
    ter->decreasePeaks();
  }
  buffer();
}

void Object::buffer() {
  // initial plane
  ter->createPlane(offsetX, offsetZ);
  // vertex array
  glGenVertexArrays(1, &vertexArrayObject);
  glBindVertexArray(vertexArrayObject);
  glBindVertexArray(vertexArrayObject);
  // vertex buffer object
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, ter->vertices.size() * sizeof(GLfloat),
    ter->vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  // index buffer object
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ter->vertIndices.size() * sizeof(GLuint),
    ter->vertIndices.data(), GL_STATIC_DRAW);
}

// bind buffers
void Object::bind() {
  glBindVertexArray(vertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  shader.use();
}

void Object::setMatrix(int width, int height) {
  bind();
  // matrices
  glm::vec3 temp = glm::vec3(0.0f);
  glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.4f));
  projectionMatrix = glm::perspective(45.0f, ((float)width) / ((float)height), 0.1f, 20.0f);
  shader.setUniforms("4fv", "model", &modelMatrix[0][0], temp);
  shader.setUniforms("4fv", "view",
    &Camera::instance((float)width, (float)height).getViewMatrix()[0][0], temp);
  shader.setUniforms("4fv", "projection", &projectionMatrix[0][0], temp);
  // positions
  glm::vec3 v3 = glm::vec3(0.0f);
  shader.setUniforms("3f", "lightPos", NULL, v3);
  shader.setUniforms("3f", "viewPos", NULL, v3);
}

// draw
void Object::render() {
  bind();
  glDrawElements(GL_TRIANGLES, ter->vertIndices.size(), GL_UNSIGNED_INT, NULL);
}
