#include "EDassets.hpp"
#include <fstream>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

void EDassets::encryptFile(const std::string &nPath) {
    std::string nPathFormatted = "";
    for (size_t i = 0; i < nPath.length(); ++i){
        nPathFormatted += nPath[i];
        if (nPath[i] == '.') break;
    }
    std::string output = nPathFormatted;
    char scan;
    std::ifstream readFile(nPath.c_str(), std::ios::binary);
        std::ofstream outFile(output.c_str(), std::ios::binary);
        while (!readFile.eof()){
            readFile >> std::noskipws >>scan;
            int temp = (scan + key);
            outFile << char(temp);
        }
        readFile.close();
    outFile.close();
    remove(nPath.c_str());
    nPathFormatted.pop_back();
    #ifdef DEBUG
    std::cout << "Succesfully encrypted the file '" << nPath << "' to '" << nPathFormatted << "'\n";
    #endif // DEBUG
}

void EDassets::decryptFile(const std::string &nPath){
    std::string output ="Assets/sprite.png";
    char scan;
    int temp;
    std::ifstream readFile(nPath.c_str(), std::ios::binary);
        std::ofstream outFile(output.c_str(), std::ios::binary);
        while (!readFile.eof()){
            readFile >> std::noskipws >>scan;
            temp = (scan - key);
            outFile << char(temp);
        }
        readFile.close();
    outFile.close();
    #ifdef DEBUG
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); std::cout << "EDassets";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    std::cout << " : Succesfully decrypted the file '" << nPath << "' to 'sprite.png'\n";
    #endif // DEBUG
}



void increaseBar(sf::RectangleShape &bar) {bar.setSize(sf::Vector2f(bar.getSize().x + float((sf::VideoMode::getDesktopMode().width * 0.50)/49), bar.getSize().y));}
sf::RectangleShape BARUI::barload = sf::RectangleShape(sf::Vector2f(0.0f, 0.05859375f * sf::VideoMode::getDesktopMode().height));
sf::RectangleShape BARUI::barlimit = sf::RectangleShape(sf::Vector2f(0.0f, 0.0f));
void BARUI::SETPOSITION(const sf::RenderWindow &window){
	unsigned short r = 30, g = 144, b = 255, a = 1020;
	barlimit.setSize(sf::Vector2f(window.getSize().x, 0.05859375f * sf::VideoMode::getDesktopMode().height));
	barlimit.setPosition(0, window.getSize().y - barlimit.getSize().y);
	barlimit.setFillColor(sf::Color(211,211,211));
	barload.setPosition(0,window.getSize().y - barload.getSize().y);
	barload.setFillColor(sf::Color(r,g,b,a));
}
