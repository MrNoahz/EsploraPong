#include "Ball.h"

// Ball::Ball(int x, int y, int height, int width) {

// }

void Ball::draw(TFT_ST7735* tft) {
	if(redraw) {
		tft->drawRect(lastX, lastY, width, height, BLACK);
		tft->drawRect(x, y, width, height, color);
		
		lastX = x;
		lastY = y;
		redraw = false;
	}
}

void Ball::setX(double _x) {
	if(clip) {
		if(_x < 0)
			_x = 0;
		else if(_x > 160 - height)
			_x = 160 - height;
	}

	x = _x;

	if(x != lastX) redraw = true;
}

void Ball::setY(double _y) {
	if(clip) {
		if(_y < 0)
			_y = 0;
		else if(_y > 128 - height)
			_y = 128 - height;
	}

	y = _y;

	if(y != lastY) redraw = true;
}

void Ball::changeX(double _x) {
	this->setX(x + _x);	
}

void Ball::changeY(double _y) {
	this->setY(y + _y);	
}

void Ball::setVelX(double _vX) {
	velX = _vX;
}

void Ball::setVelY(double _vY) {
	velY = _vY;
}

double Ball::getX() { return x; }

double Ball::getY() { return y; }

double Ball::getVelX() { return velX; }

double Ball::getVelY() { return velY; }

int Ball::getWidth() { return width; }

int Ball::getHeight() { return height; }

void Ball::forceRedraw() {
	redraw = true;
}