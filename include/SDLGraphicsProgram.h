#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include <math.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class SDLGraphicsProgram {
public:
  // constructor
  SDLGraphicsProgram(int w, int h, unsigned int terW, unsigned int terL);
  // desctructor
  ~SDLGraphicsProgram();
  // pointer to window
  SDL_Window* getWindow();
  // draw object
  void render();
  void loop();

private:
  // window data
  SDL_Window* window;
  int width;
  int height;
  SDL_GLContext context;
  // object data
  Object* object;
  unsigned int terWidth;
  unsigned int terLength;
  // stores initial values
  glm::vec3 originalPos;
};

#endif
