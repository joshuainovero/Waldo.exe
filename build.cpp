//VS code extension | Code runner - Exectutor map - settings.json
//File -> Preferences -> Settings -> Search executor -> Executor Map | settings.json
//"cpp": "g++ build.cpp -o build.exe && start build.exe"

#include <Windows.h>

int main(){
    system("title Build && mingw32-make");
    system("start Build/release/Waldo.exe && pause");
    return 0;
}