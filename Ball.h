#ifndef Ball_h
#define Ball_h

#include <TFT_ST7735.h>

class Ball {
public:
	Ball(double _x, double _y, int _width, int _height, uint16_t _color) :
		x(_x), y(_y),
		lastX(_x), lastY(_y),
		width(_width), height(_height),
		color(_color),
		redraw(false),
		clip(false) {};

	void draw(TFT_ST7735*);

	double getX();
	double getY();

	int getWidth();
	int getHeight();

	void setX(double);
	void setY(double);

	void changeX(double);
	void changeY(double);

	void forceRedraw();
private:
	double x, y;
	double lastX, lastY;
	int width, height;
	uint16_t color;

	bool redraw;
	bool clip;
};

#endif