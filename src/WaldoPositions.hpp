#pragma once
#include <array>
#include <unordered_map>
#include <SFML/Graphics.hpp>

struct WALDOPOSINITIALIZER{
	std::unordered_map<std::string, std::array<int16_t, 4>> MapResol;
	WALDOPOSINITIALIZER(){
		sf::Vector2f currResol(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
		MapResol["Map1"] = {
			static_cast<int16_t>(currResol.x * 0.7188872621),
			static_cast<int16_t>(currResol.x * 0.7554904832),
			static_cast<int16_t>(currResol.y * 0.4856770833),
			static_cast<int16_t> (currResol.y * 0.5572916667)
		};
		MapResol["Map2"] = {
			static_cast<int16_t>(currResol.x * 0.5988286969),
			static_cast<int16_t>(currResol.x * 0.635431918),
			static_cast<int16_t>(currResol.y * 0.3658854167),
			static_cast<int16_t>(currResol.y * 0.4283854167)
		};
		MapResol["Map3"] = {
			static_cast<int16_t>(currResol.x * 0.08857979502),
			static_cast<int16_t>(currResol.x * 0.1178623719),
			static_cast<int16_t>(currResol.y * 0.8958333333),
			static_cast<int16_t>(currResol.y * 0.9296875)
		};
		MapResol["Map4"] = {
			static_cast<int16_t>(currResol.x * 0.878477306),
			static_cast<int16_t>(currResol.x * 0.906295754),
			static_cast<int16_t>(currResol.y * 0.7265625),
			static_cast<int16_t>(currResol.y * 0.76953125)
		};
		MapResol["Map5"] = {
			static_cast<int16_t>(currResol.x * 0.8426061493),
			static_cast<int16_t>(currResol.x * 0.8653001464),
			static_cast<int16_t>(currResol.y * 0.80078125),
			static_cast<int16_t>(currResol.y * 0.8463541667)
		};
		MapResol["Map6"] = {
			static_cast<int16_t>(currResol.x * 0.616398243),
			static_cast<int16_t>(currResol.x * 0.6390922401),
			static_cast<int16_t>(currResol.y * 0.69140625),
			static_cast<int16_t>(currResol.y * 0.7174479167)
		};
	}
}waldopositions;