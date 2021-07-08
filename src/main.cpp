#include "Core.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	loadingScreen();
	getMainDirectory();
	Engine engine;
	engine.run();
	return EXIT_SUCCESS;
}