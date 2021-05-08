#include <string>
#include "MapProperties.hpp"
#include <iostream>

MapProperty::MapProperty(std::string fileName) {
	responsiveResolutionMap = sf::VideoMode::getDesktopMode().height;
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);

	if (responsiveResolutionMap == 1080)
		sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	else if (responsiveResolutionMap == 768)
		sprite.setScale(sf::Vector2f(0.714f, 0.714f));


}

Map1::Map1(std::string fileName)
	:MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];
	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
	

	}

Map2::Map2(std::string fileName)
	: MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];
	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
}

Map3::Map3(std::string fileName)
	: MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];

	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
}

Map4::Map4(std::string fileName)
	: MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];
	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
}

Map5::Map5(std::string fileName)
	: MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];
	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
}

Map6::Map6(std::string fileName)
	: MapProperty(fileName) {
	if (responsiveResolutionMap == 768) {
		wallyPosition[0] = wallyResol768Pos[0];
		wallyPosition[1] = wallyResol768Pos[1];
		wallyPosition[2] = wallyResol768Pos[2];
		wallyPosition[3] = wallyResol768Pos[3];
	}
	else if (responsiveResolutionMap == 1080) {
		wallyPosition[0] = wallyResol1080Pos[0];
		wallyPosition[1] = wallyResol1080Pos[1];
		wallyPosition[2] = wallyResol1080Pos[2];
		wallyPosition[3] = wallyResol1080Pos[3];
	}
}
