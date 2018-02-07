#ifndef Paddle_h
#define Paddle_h

class Paddle {
	int width, height;
	int x, y;
public:
	Paddle();
	Paddle(int, int, int, int);

	void update();
	void clear(TFT_ST7735);
	void render(TFT_ST7735);

	int getX() { return x; }
	int getY() { return y; }

	int getWidth() { return width; }
	int getHeight() { return height; }
}

#endif