#pragma once

class ScalesResolutions {
private:
	float fullScreenSpriteScale;
	float scaleArrow;
	float scaleCircleCursor;

public:
	float getFullScreenSpriteScale() { return fullScreenSpriteScale; }
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
			scaleArrow = 0.30f;
			scaleCircleCursor = 0.07f;
		}
	}

};
ScalesResolutions scaleresol;