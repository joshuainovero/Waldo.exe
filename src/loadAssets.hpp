#pragma once
#include <thread>

struct SpriteLoader {
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void SetSpriteScale() = 0;
	SpriteLoader(const std::string &path){
		try{
			std::ifstream checkSpriteLoader(path);
			if (!checkSpriteLoader.good())
				throw path;
			EDassets::decryptFile(path);
			increaseBar(BARUI::barload);
			texture.loadFromFile("Assets/sprite.png");
			sprite.setTexture(texture);
			increaseBar(BARUI::barload);
		} catch (const std::string &threwPath){
			if (MessageBoxA(NULL,"An asset has been corrupted or deleted. Please reinstall", "Waldo", MB_ICONERROR) == IDOK)
				abort();
		}

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
	}
	PAUSESCREEN(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
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
	bool resumeInRange(const sf::Vector2i &mousePos){
		return ((mousePos.x >= rRangeClickX[0] && mousePos.x <= rRangeClickX[1]) && 
			(mousePos.y >= rRangeClickY[0] && mousePos.y <= rRangeClickY[1]));
	}
	bool quitInRange(const sf::Vector2i &mousePos) {
		return ((mousePos.x >= qRangeClickX[0] && mousePos.x <= qRangeClickX[1]) &&
			(mousePos.y >= qRangeClickY[0] && mousePos.y <= qRangeClickY[1]));
	}
};

struct GAMEEND : public SpriteLoader {
	sf::Vector2i screenSize;
	int cRangeClickX[2], cRangeClickY[2];
	//606 -> 759         454 -> 495
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	GAMEEND(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			screenSize.x = sf::VideoMode::getDesktopMode().width;
			screenSize.y = sf::VideoMode::getDesktopMode().height;

			// Range continue
			cRangeClickX[0] = screenSize.x * 0.4436310395;
			cRangeClickX[1] = screenSize.x * 0.555636896;
			cRangeClickY[0] = screenSize.y * 0.5911458333;
			cRangeClickY[1] = screenSize.y * 0.64453125;
		}
	bool continueInRange(const sf::Vector2i &mousePos){
		return ((mousePos.x >= cRangeClickX[0] && mousePos.x <= cRangeClickX[1]) &&
			(mousePos.y >= cRangeClickY[0] && mousePos.y <= cRangeClickY[1]));
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

struct MAPOPTIONS : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	MAPOPTIONS(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
		}
};

struct UKMAP : public SpriteLoader {
	std::array<std::array<float,2>, 6> ukscales {{{0.2510416667, 0.1962962963},{0.5463541667, 0.1962962963}, {0.2510416667, 0.437037037}, {0.5463541667, 0.437037037}, {0.2510416667, 0.6787037037}, {0.5463541667, 0.6787037037}}};
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	UKMAP(const std::string &pathA)
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
		increaseBar(BARUI::barload);
	}
};

struct GAMEMUSIC {
	sf::Music music;
	GAMEMUSIC(const std::string &path){
		music.openFromFile(path);
		increaseBar(BARUI::barload);
	}
};

ARROWCURSOR *ArrowCursorObj;
HANDCURSOR *HandCursorObj;
CIRCLECURSOR *CircleCursorObj;
EXITICON *ExitIconObj;
MENULOGO *MenuLogoObj;
MENULOGO *OpeningObj;
PAUSESCREEN *PauseScreenObj;
GAMEEND *WaldoFoundObj;
GAMEEND *GameOverObj;
MAPOPTIONS *MapOptionsObj;
UKMAP *UkMapObj;

GAMEMUSIC *Intromusic;
SOUNDEFFECT *WrongClickEffect;
SOUNDEFFECT *WallyFoundEffect;
SOUNDEFFECT *MenuSelectionEffect;

MapProperty *MAP1;
MapProperty *MAP2;
MapProperty *MAP3;
MapProperty *MAP4;
MapProperty *MAP5;
MapProperty *MAP6;

const std::array<std::string, 3> openingDialogues{
	"Hello there, gamer! My name is Waldo, and I'm from\nthe Land of Waldos, a land populated by Waldos just\nlike me. You've probably come across me in one of your\nbooks where I'm hidden in various pages",
	"You had a hard time finding me before, didn't you?\nAnyways, I am always ready for an adventure with my\nwalking stick in hand, and my trusty dog Woof by my\nside. I've gotten a little more sophisticated, and I'm\nnow lurking and hidden behind your computer screen.",
	"The rule is straightforward gamer. All you have to do is\nto find me on each map of the game. Simple isn't it? Be\nsure to find me before the clock runs out or else there\nwill be consequences. Best of luck gamer!"
};

TypeWriter openingWriter("", 0.02, 360.0f, 305.0f, 25);
static bool done = false;

void loadAssets(){
	ArrowCursorObj = new ARROWCURSOR("Assets/001/001-ac");
	HandCursorObj = new HANDCURSOR("Assets/001/001-hc");
	CircleCursorObj = new CIRCLECURSOR("Assets/001/001-rcs");
	ExitIconObj = new EXITICON("Assets/002/002-ex");
	MenuLogoObj = new MENULOGO("Assets/004/004-mui");
	OpeningObj = new MENULOGO("Assets/004/004-opg");
	PauseScreenObj = new PAUSESCREEN("Assets/004/004-pse");
	WaldoFoundObj = new GAMEEND("Assets/004/004-fnd");
	GameOverObj = new GAMEEND("Assets/004/004-go");
	MapOptionsObj = new MAPOPTIONS("Assets/004/004-mo");
	UkMapObj = new UKMAP("Assets/004/004-uk");

	Intromusic = new GAMEMUSIC("Assets/Audio/music/MenuMusic.wav");
	WrongClickEffect = new SOUNDEFFECT("Assets/Audio/SoundEffects/WrongClick.wav");
	WallyFoundEffect = new SOUNDEFFECT("Assets/Audio/SoundEffects/WallyFound.wav");
	MenuSelectionEffect = new SOUNDEFFECT("Assets/Audio/SoundEffects/MenuSelection.wav");

	MAP1 = new MapProperty("Assets/003/003-m1", "Map1", GameTimer::m1TimeCounts);
	MAP2 = new MapProperty("Assets/003/003-m2", "Map2", GameTimer::m2TimeCounts);
	MAP3 = new MapProperty("Assets/003/003-m3", "Map3", GameTimer::m3TimeCounts);
	MAP4 = new MapProperty("Assets/003/003-m4", "Map4", GameTimer::m4TimeCounts);
	MAP5 = new MapProperty("Assets/003/003-m5", "Map5", GameTimer::m5TimeCounts);
	MAP6 = new MapProperty("Assets/003/003-m6", "Map6", GameTimer::m6TimeCounts);

	done = true;
}

void windowLoad(){
	std::unique_ptr<sf::Texture> textureLoading = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::Sprite> spriteLoading = std::make_unique<sf::Sprite>();
	float spriteScale = (sf::VideoMode::getDesktopMode().height * 0.50) / 1080.0f;
	EDassets::decryptFile("Assets/004/004-ld");
	increaseBar(BARUI::barload);
	textureLoading->loadFromFile("Assets/sprite.png");
	spriteLoading->setTexture(*textureLoading);
	increaseBar(BARUI::barload);
	spriteLoading->setScale(spriteScale, spriteScale);
	
	sf::RenderWindow loadWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.50, sf::VideoMode::getDesktopMode().height * 0.50), "Where's Wally?", sf::Style::None);

	BARUI::SETPOSITION(loadWindow);
	std::thread threadLoadAssets(loadAssets);
	while (loadWindow.isOpen()){
		sf::Event evnt;
		while (loadWindow.pollEvent(evnt)){
		if (evnt.type == sf::Event::Closed)
			loadWindow.close();
		}
		loadWindow.clear();
		loadWindow.draw(*spriteLoading);
		loadWindow.draw(BARUI::barlimit);
		loadWindow.draw(BARUI::barload);
		loadWindow.display();

		if (done)
			loadWindow.close();
	}
	threadLoadAssets.join();

}