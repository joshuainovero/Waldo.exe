#include "Engine.hpp"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow){
	// #ifdef DEBUG
	// 	system(std::string("title Waldo Debug " + getDataJson()["app-properties"]["localversion"].asString()).c_str());
    // 	RECT r;
    // 	GetWindowRect(GetConsoleWindow(), &r);
    // 	MoveWindow(GetConsoleWindow(), r.left, r.top, 800, 600, TRUE);
	// #endif // DEBUG
	Engine engine;
	engine.run();
	return EXIT_SUCCESS;
}