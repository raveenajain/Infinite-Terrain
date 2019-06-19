// Sources: notes, https://learnopengl.com/Getting-started/Shaders,
// 					https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glUniform.xml
#include "Shader.h"

// constructor
Shader::Shader() {
}

// destructor
Shader::~Shader() {
	glDeleteProgram(program);
}

// use program
void Shader::use() {
	glUseProgram(program);
}

// returns a shader as a string
std::string Shader::toString(std::string fileName) {
	std::string output = "";
	std::ifstream inFile(fileName);
	if(!inFile) {
    throw std::exception();
  }
  std::string line;
  while (std::getline(inFile, line)) {
		output = output + line + "\n";
	}
		inFile.close();
		return output;
}

// create vertex and fragment shaders
void Shader::createShaders(std::string vertexString, std::string fragmentString){
	// create vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexChar = vertexString.c_str();
	glShaderSource(vertex, 1, &vertexChar, NULL);
	glCompileShader(vertex);
	// create fragment shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentChar = fragmentString.c_str();
	// The source of our shader
	glShaderSource(fragment, 1, &fragmentChar, NULL);
	// Now compile our shader
	glCompileShader(fragment);
	// program
	program = glCreateProgram();
	// attatch
	glAttachShader(program, vertex);
  glAttachShader(program, fragment);
	// link
	glLinkProgram(program);
	// delete
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

// set uniforms
void Shader::setUniforms(std::string type, const GLchar* name, const GLfloat* value, glm::vec3 v3) {
	GLint location = glGetUniformLocation(program, name);
	if (type == "4fv") {
		glUniformMatrix4fv(location, 1, GL_FALSE, value);
	} else if (type == "3f") {
		glUniform3f(location, v3.x, v3.y, v3.z);
	} 
}
