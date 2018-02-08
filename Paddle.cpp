#include "Paddle.h"

// Paddle::Paddle(int x, int y, int height, int width) {

// }

void Paddle::draw(TFT_ST7735* tft) {
	if(redraw) {
		tft->drawRect(lastX, lastY, width, height, BLACK);
		tft->drawRect(x, y, width, height, color);
		
		lastX = x;
		lastY = y;
		redraw = false;
	}
}

void Paddle::setX(double _x) {
	if(clip) {
		if(_x < 0)
			_x = 0;
		else if(_x > 160 - height)
			_x = 160 - height;
	}

	x = _x;

	if(x != lastX) redraw = true;
}

void Paddle::setY(double _y) {
	if(clip) {
		if(_y < 0)
			_y = 0;
		else if(_y > 128 - height)
			_y = 128 - height;
	}

	y = _y;

	if(y != lastY) redraw = true;
}

void Paddle::changeX(double _x) {
	this->setX(x + _x);	
}

void Paddle::changeY(double _y) {
	this->setY(y + _y);	
}

double Paddle::getX() { return x; }

double Paddle::getY() { return y; }

int Paddle::getWidth() { return width; }

int Paddle::getHeight() { return height; }