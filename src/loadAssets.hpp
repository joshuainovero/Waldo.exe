#pragma once

const float fullScreenSprite720 = 0.714f;
const float fullScreenSprite1080 = 1;

//Jumpscare pictures
struct structJumpscare {
	sf::Texture texture;
	sf::Sprite sprite;
	structJumpscare(std::string path) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.714f, 0.714f));
	}
};

//Music
struct SoundEffect {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	SoundEffect(std::string path) {
		buffer.loadFromFile(path);
		sound.setBuffer(buffer);
	}
};

struct GameMusic {
	sf::Music music;
	GameMusic(std::string path) {
		music.openFromFile(path);
	}
};

//CircleCursor
struct structCircle {
	sf::Texture circleTexture;
	sf::Sprite circleSprite;
	StaticObjAnimation AnimationCircle;
	structCircle()
	:AnimationCircle() {
		circleTexture.loadFromFile("Assets/Cursors/redcirclesprite.png");
		circleSprite.setTexture(circleTexture);
		circleSprite.setScale(sf::Vector2f(scaleresol.getScaleCircleCursor(), scaleresol.getScaleCircleCursor()));
		circleSprite.setOrigin(187, 180);
		AnimationCircle = StaticObjAnimation(&circleTexture, sf::Vector2u(9,1), 0.06f);
	}
};


//Arrow Cursor
struct structArrow {
	sf::Texture arrowCursorTexture;
	sf::Sprite  arrowCursorSprite;

	structArrow() {
		arrowCursorTexture.loadFromFile("Assets/Cursors/ArrowCursor.png");
		arrowCursorSprite.setTexture(arrowCursorTexture);
		//0.30f for 768p
		// std::cout << "scale arrow : " << scaleresol.getScaleArrow() << std::endl;
		arrowCursorSprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
		arrowCursorSprite.setOrigin(68, 23);
	}
};


//Hand Cursor
struct structHandCursor {
	sf::Texture handCursorTexture;
	sf::Sprite  handCursorSprite;

	structHandCursor() {
		handCursorTexture.loadFromFile("Assets/Cursors/HandCursor.png");
		handCursorSprite.setTexture(handCursorTexture);
		handCursorSprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
		handCursorSprite.setOrigin(110, 30);
	}
};

//Exit icon
struct structExitIcon {
	sf::Texture exitIconTexture;
	sf::Sprite exitIconSprite;
	int clickableX[2], clickableY[2];
	float exitWidth, exitHeight;
	structExitIcon(){
		exitIconTexture.loadFromFile("Assets/Icon/InIcons/exit.png");
		exitIconSprite.setTexture(exitIconTexture);
		exitWidth = (exitIconSprite.getTexture()->getSize().x) * scaleresol.getScaleExitIcon();
		exitHeight = (exitIconSprite.getTexture()->getSize().y) * scaleresol.getScaleExitIcon();
		exitIconSprite.setScale(sf::Vector2f(scaleresol.getScaleExitIcon(), scaleresol.getScaleExitIcon()));
		exitIconSprite.setOrigin(exitIconSprite.getTexture()->getSize().x, 0);
		
		clickableX[0] = (sf::VideoMode::getDesktopMode().width) - exitWidth;
		clickableX[1] = sf::VideoMode::getDesktopMode().width;
		clickableY[0] = 0;
		clickableY[1] = exitHeight;
		exitIconSprite.setPosition(sf::VideoMode::getDesktopMode().width, 0);
	}
};


//Menu
struct structMenu {
	sf::Texture textureMenuLogo;
	sf::Sprite spriteMenuLogo;

	structMenu() {
		textureMenuLogo.loadFromFile("Assets/Maps/MenuUI.png");
		spriteMenuLogo.setTexture(textureMenuLogo);
		spriteMenuLogo.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
};



structMenu MenuLogo;
structExitIcon ExitIcon;
structArrow ArrowCursor;
structHandCursor HandCursor;
structCircle circleCursor;

GameMusic intro("Assets/Audio/music/MenuMusic.wav");
SoundEffect WrongClick("Assets/Audio/SoundEffects/WrongClick.wav");
SoundEffect WallyFound("Assets/Audio/SoundEffects/WallyFound.wav");
SoundEffect Scream("Assets/Audio/SoundEffects/Scream.wav");

structJumpscare Jumpscare1("Assets/Jumpscares/Jumpscare1.png");


//Maps
Map1 MAP1("Assets/Maps/Map1.png");
Map2 MAP2("Assets/Maps/Map2.png");
Map3 MAP3("Assets/Maps/Map3.png");
Map4 MAP4("Assets/Maps/Map4.png");
Map5 MAP5("Assets/Maps/Map5.png");
Map6 MAP6("Assets/Maps/Map6.png");