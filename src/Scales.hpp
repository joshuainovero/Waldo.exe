#pragma once

class ScalesResolutions {
private:
	float fullScreenSpriteScale;
	float scaleExitIcon;
	float scaleArrow;
	float scaleCircleCursor;

public:
	float getFullScreenSpriteScale() { return fullScreenSpriteScale; }
	float getScaleExitIcon() { return scaleExitIcon; }
	float getScaleArrow() { return scaleArrow; }
	float getScaleCircleCursor() { return scaleCircleCursor; }
	ScalesResolutions() {
		int screenHeight = sf::VideoMode::getDesktopMode().height;
		if (screenHeight == 1080) {
			fullScreenSpriteScale = 1.0f;
			scaleArrow = 0.42f;
			scaleCircleCursor = 0.09803921569f;
		}

		else if (screenHeight == 768) {
			fullScreenSpriteScale = 0.714f;
			scaleExitIcon = 0.14f;
			scaleArrow = 0.30f;
			scaleCircleCursor = 0.33f;
		}
	}

};
ScalesResolutions scaleresol;