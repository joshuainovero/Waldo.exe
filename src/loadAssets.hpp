#pragma once

struct SpriteLoader {
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void SetSpriteScale() = 0;
	SpriteLoader(const std::string &path){
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
};

struct ARROWCURSOR : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
	}
	ARROWCURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(68, 23);
		}
};

struct HANDCURSOR : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
	}
	HANDCURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(110, 30);
		}
};

struct CIRCLECURSOR : public SpriteLoader {
	StaticObjAnimation AnimationCircle;
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleCircleCursor(), scaleresol.getScaleCircleCursor()));
	}
	CIRCLECURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(187, 180);
			AnimationCircle = StaticObjAnimation(&texture, sf::Vector2u(9,1), 0.06f);
		}
};

struct EXITICON : public SpriteLoader {
	int clickableX[2], clickableY[2];
	float exitWidth, exitHeight;
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleExitIcon(), scaleresol.getScaleExitIcon()));
	}
	EXITICON(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			exitWidth = (sprite.getTexture()->getSize().x) * scaleresol.getScaleExitIcon();
			exitHeight = (sprite.getTexture()->getSize().y) * scaleresol.getScaleExitIcon();
			sprite.setOrigin(sprite.getTexture()->getSize().x, 0);
			clickableX[0] = (sf::VideoMode::getDesktopMode().width) - exitWidth;
			clickableX[1] = sf::VideoMode::getDesktopMode().width;
			clickableY[0] = 0;
			clickableY[1] = exitHeight;
			sprite.setPosition(sf::VideoMode::getDesktopMode().width, 0);
		}
};

struct PAUSESCREEN : public SpriteLoader {
	sf::Vector2i screenSize;
	int rRangeClickX[2], rRangeClickY[2];
	//615 -> 791         353 -> 403
	int qRangeClickX[2], qRangeClickY[2];
	//615 -> 791         460 -> 510
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
		screenSize.x = sf::VideoMode::getDesktopMode().width;
		screenSize.y = sf::VideoMode::getDesktopMode().height;

		// Range Resume
		rRangeClickX[0] = screenSize.x * 0.4502196193;
		rRangeClickX[1] = screenSize.x * 0.5790629575;
		rRangeClickY[0] = screenSize.y * 0.4596354167;
		rRangeClickY[1] = screenSize.y * 0.5247395833;

		//Range Quit
		qRangeClickX[0] = screenSize.x * 0.4502196193;
		qRangeClickX[1] = screenSize.x * 0.5790629575;
		qRangeClickY[0] = screenSize.y * 0.5989583333;
		qRangeClickY[1] = screenSize.y * 0.6640625;
	}
	PAUSESCREEN(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
		}
	bool resumeInRange(const sf::Vector2i &mousePos){
		return ((mousePos.x >= rRangeClickX[0] && mousePos.x <= rRangeClickX[1]) && 
			(mousePos.y >= rRangeClickY[0] && mousePos.y <= rRangeClickY[1]));
	}
	bool quitInRange(const sf::Vector2i &mousePos) {
		return ((mousePos.x >= qRangeClickX[0] && mousePos.x <= qRangeClickX[1]) &&
			(mousePos.y >= qRangeClickY[0] && mousePos.y <= qRangeClickY[1]));
	}
};

struct MENULOGO : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	MENULOGO(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
		}
};

struct SOUNDEFFECT {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	SOUNDEFFECT(const std::string &path){
		buffer.loadFromFile(path);
		sound.setBuffer(buffer);
	}
};

struct GAMEMUSIC {
	sf::Music music;
	GAMEMUSIC(const std::string &path){
		music.openFromFile(path);
	}
};

// ASSETS
ARROWCURSOR ArrowCursorObj("Assets/Cursors/ArrowCursor.png");
HANDCURSOR HandCursorObj("Assets/Cursors/HandCursor.png");
CIRCLECURSOR CircleCursorObj("Assets/Cursors/redcirclesprite.png");
EXITICON ExitIconObj("Assets/Icon/InIcons/exit.png");
MENULOGO MenuLogoObj("Assets/Maps/MenuUI.png");
PAUSESCREEN PauseScreenObj("Assets/Maps/Pause.png");

GAMEMUSIC Intromusic("Assets/Audio/music/MenuMusic.wav");
SOUNDEFFECT WrongClickEffect("Assets/Audio/SoundEffects/WrongClick.wav");
SOUNDEFFECT WallyFoundEffect("Assets/Audio/SoundEffects/WallyFound.wav");


// MAPS
MapProperty MAP1("Assets/Maps/Map1.png", "Map1", GameTimer::m1TimeCounts);
MapProperty MAP2("Assets/Maps/Map2.png", "Map2", GameTimer::m2TimeCounts);
MapProperty MAP3("Assets/Maps/Map3.png", "Map3", GameTimer::m3TimeCounts);
MapProperty MAP4("Assets/Maps/Map4.png", "Map4", GameTimer::m4TimeCounts);
MapProperty MAP5("Assets/Maps/Map5.png", "Map5", GameTimer::m5TimeCounts);
MapProperty MAP6("Assets/Maps/Map6.png", "Map6", GameTimer::m6TimeCounts);