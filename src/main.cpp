#include "Core.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	State::states.push_back(new GAMEMENU);
	State::states.push_back(new MAPSELECT);
	State::states.push_back(new INGAME);
	windowLoad();
	getMainDirectory();
	Engine engine;
	engine.run();
	return EXIT_SUCCESS;
}