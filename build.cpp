//VS code extension | Code runner - Exectutor map - settings.json
//File -> Preferences -> Settings -> Search executor -> Executor Map | settings.json
 //"cpp": "g++ build.cpp -o build.exe && start build.exe"

#include <Windows.h>
#include <iostream>

int main(){
    system("mingw32-make");
    system("start main.exe");
    std::cin.get();
    return 0;
}