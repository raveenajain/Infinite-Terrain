#include "SDLGraphicsProgram.h"

int main(int argc, char** argv){
	// initialize
	SDLGraphicsProgram mySDLGraphicsProgram(800, 720, 100, 100);
	// run program until quit
	mySDLGraphicsProgram.loop();
	return 0;
}
