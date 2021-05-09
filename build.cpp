#include <Windows.h>
#include <iostream>

int main(){
    //VS code extension | Code runner - Executor map -> settings.json:
    //"cpp": "g++ build.cpp -o build.exe && start build.exe"
    system("mingw32-make");
    system("start main.exe");
    
    std::cin.get();
    return 0;
}