#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include "glm/vec3.hpp"

class Shader {
public:
  // constructor
  Shader();
  // destructor
  ~Shader();
  // use program
  void use();
  // returns a shader as a string
  std::string toString(std::string fileName);
  // create vertex and fragment shaders
  void createShaders(std::string vertexString, std::string fragmentString);
  // set matrix uniforms
  void setUniforms(std::string type, const GLchar* name, const GLfloat* value, glm::vec3 v3);

private:
  // shader id
  GLuint program;
};

#endif
