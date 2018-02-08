#ifndef Paddle_h
#define Paddle_h

#include <TFT_ST7735.h>

class Paddle {
public:
	Paddle(double _x, double _y, int _width, int _height, uint16_t _color) :
		x(_x), y(_y),
		lastX(_x), lastY(_y),
		width(_width), height(_height),
		color(_color),
		redraw(false),
		clip(true) {};

	void draw(TFT_ST7735*);

	double getX();
	double getY();

	int getWidth();
	int getHeight();

	void setX(double);
	void setY(double);

	void changeX(double);
	void changeY(double);
private:
	double x, y;
	double lastX, lastY;
	int width, height;
	unsigned short color;

	bool redraw;
	bool clip;
};

#endif