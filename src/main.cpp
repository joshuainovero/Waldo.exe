#include "Engine.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	Engine engine;
	engine.run();
	return EXIT_SUCCESS;
}