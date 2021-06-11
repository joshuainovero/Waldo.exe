#pragma once

class ScalesResolutions {
private:
	float fullScreenSpriteScale;
	float scaleExitIcon;
	float scaleArrow;
	float scaleCircleCursor;
	const float maxResolution = 1080;

public:
	float getFullScreenSpriteScale() { return fullScreenSpriteScale; }
	float getScaleExitIcon() { return scaleExitIcon; }
	float getScaleArrow() { return scaleArrow; }
	float getScaleCircleCursor() { return scaleCircleCursor; }
	ScalesResolutions() {
		float screenHeight = sf::VideoMode::getDesktopMode().height;
		fullScreenSpriteScale = /*0.714f;*/ screenHeight / maxResolution;
		scaleExitIcon = /*0.14f;*/ (screenHeight / maxResolution) * 0.1969f;
		scaleArrow = /* 0.30f; */ (screenHeight / maxResolution) * 0.42f;
		scaleCircleCursor = /* 0.33f; */ (screenHeight / maxResolution) * 0.4641f;
		
	}

};
ScalesResolutions scaleresol;