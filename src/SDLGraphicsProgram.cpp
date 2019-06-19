// Sources: notes, https://wiki.libsdl.org/SDL_Init, https://wiki.libsdl.org/SDL_CreateWindow,
// 					https://learnopengl.com/Getting-started/Hello-Window,
// 					https://learnopengl.com/Advanced-OpenGL/Depth-testing
#include "SDLGraphicsProgram.h"

// constructor
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h, unsigned int terW, unsigned int terL):
width(w), height(h), terWidth(terW), terLength(terL) {
	window = NULL;
	bool success = true;

	// iniitalize
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		success = false;
	} else {
		//OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// initialize window
		window = SDL_CreateWindow("final", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		context = SDL_GL_CreateContext(window);

		// initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
			success = false;
		}
  }

	// initial data
	originalPos = Camera::instance(terWidth, terLength).getPosition();
	// initialize object with specified tile size
	object = new Object(terWidth, terLength);
}

// destructor
SDLGraphicsProgram::~SDLGraphicsProgram() {
	delete object;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// pointer to window
SDL_Window* SDLGraphicsProgram::getWindow(){
  	return window;
}

void SDLGraphicsProgram::render() {
	// depth
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
	//  background
  glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object->setMatrix(width * 3, height * 3);
	object->render();
}

void SDLGraphicsProgram::loop() {
	// if true program quits
	bool quit = false;
	// switches wireframe
	bool fill = true;
	// to track offset
	int distanceX = 0;
	int distanceZ = 0;
	// event handler
  SDL_Event e;

	bool cameraEnabled = false;
	// run program
	while(!quit) {
		while(SDL_PollEvent(&e) != 0) {
			// quit
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
				quit = true;
	    	}

			// mouse movement
			if(e.type==SDL_MOUSEMOTION && cameraEnabled) {
				int x = e.motion.x;
				int y = e.motion.y;
				Camera::instance(terWidth,terLength).mouseMove(x, y);
			}
			// key press
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP) {
					distanceZ = distanceZ + 1;
					object->addTiles(distanceX, distanceZ);
				} if (e.key.keysym.sym == SDLK_DOWN) {
					distanceZ = distanceZ - 1;
					object->addTiles(distanceX, distanceZ);
				} if (e.key.keysym.sym == SDLK_LEFT) {
					distanceX = distanceX - 1;
					object->addTiles(distanceX, distanceZ);
				} if (e.key.keysym.sym == SDLK_RIGHT) {
					distanceX = distanceX + 1;
					object->addTiles(distanceX, distanceZ);
				} if (e.key.keysym.sym == SDLK_a) {
					object->editPeaks("increase");
				} if (e.key.keysym.sym == SDLK_d) {
					object->editPeaks("decrease");
				} if (e.key.keysym.sym == SDLK_w) {
					if (fill) {
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					} else {
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					}
					fill = !fill;
				} if (e.key.keysym.sym == SDLK_r) {
					delete object;
					distanceX = 0;
					distanceZ = 0;
					object = new Object(terWidth, terLength);
				} if (e.key.keysym.sym == SDLK_c) {
				    cameraEnabled = !cameraEnabled;
			   	}
			}



		}
		// draw
	  render();
		SDL_GL_SwapWindow(getWindow());
  }
}
