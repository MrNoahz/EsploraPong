#ifndef Ball_h
#define Ball_h

#include <TFT_ST7735.h>

class Ball {
public:
	Ball(double _x, double _y, int _width, int _height, uint16_t _color) :
		x(_x), y(_y),
		lastX(_x), lastY(_y),
		velX(0), velY(0),
		width(_width), height(_height),
		color(_color),
		redraw(false),
		clip(false) {};

	void draw(TFT_ST7735*);

	int getWidth();
	int getHeight();

	double getX();
	double getY();

	void setX(double);
	void setY(double);

	void changeX(double);
	void changeY(double);
	
	double getVelX();
	double getVelY();

	void setVelX(double);
	void setVelY(double);


	void forceRedraw();
private:
	double x, y;
	double lastX, lastY;
	double velX, velY;
	int width, height;
	uint16_t color;

	bool redraw;
	bool clip;
};

#endif