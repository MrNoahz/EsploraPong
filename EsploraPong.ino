// TFT is 160 x 128
// TODO More efficient paddle drawing
// TODO Use smaller variables

#include <Esplora.h>
#include <SPI.h>
#include <TFT_ST7735.h>

#include "Paddle.h"
#include "Ball.h"

#define CS 7
#define DC 0
#define RST 1

enum State {
	SPLASH,
	GAME
};

// Global vars
const TFT_ST7735 tft = TFT_ST7735(CS, DC, RST);

State currentState = SPLASH;

const uint8_t WIDTH = 160;
const uint8_t HEIGHT = 128;

// Splash vars
unsigned long previousBlink = 0;
const long blinkInterval = 800;
bool blinkState = false;

// Game vars
const Paddle p1(4, 54, 2, 20, WHITE);
const Paddle p2(154, 54, 2, 20, WHITE);
const Ball ball(78, 62, 4, 4, WHITE);

const double paddleSpeed = 0.3;
const double ballSpeed = 0.1;

void setup() {
	Serial.begin(9600);
	Serial.println("Beginning");

	tft.begin();
	tft.setRotation(3);

	changeState(SPLASH);
}

void splash() {
	tft.clearScreen();

	tft.setTextColor(RED);
	tft.setTextScale(2);
	tft.setCursor(25, 30);
	tft.print("Esplora Pong");

	tft.setTextColor(WHITE);
	tft.setTextScale(2);
	tft.setCursor(27, 29);
	tft.print("Esplora Pong");

	tft.setTextScale(1);
	tft.setCursor(CENTER, 60);
	tft.print("By Noah");

	tft.setCharSpacing(1);
	tft.setCursor(CENTER, 100);
	tft.print("Move the joystick to start...");
}

void changeState(State state) {
	switch(state) {
		case SPLASH:
			splash();
			break;
		case GAME:
			tft.clearScreen();
			p1.forceRedraw();
			p2.forceRedraw();
			ball.forceRedraw();

			ball.setVelX(ballSpeed);
			ball.setVelY(ballSpeed);
			break;
	}

	currentState = state;
}

/* Need a refresher on how basic collision works?
 * Mozilla has a great guide right here
 * https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection 
 */
bool rectCollision(int x1, int y1, 
					int width1, int height1,
					int x2, int y2,
					int width2, int height2) {
	if(x1 < x2 + width2 &&
		x1 + width1 > x2 &&
		y1 < y2 + height2 &&
		height1 + y1 > y2)
		return true;
	return false;
}

void input() {
	if(currentState == SPLASH) {
		if(Esplora.readJoystickX() > 60 || Esplora.readJoystickX() < -60 ||
			Esplora.readJoystickY() > 60 || Esplora.readJoystickY() < -60) {
			
			changeState(GAME);
		}
	} else if(currentState == GAME) {
		
	}
}

void update() {
	if(currentState == SPLASH) {
		unsigned long currentMillis = millis();

		if(currentMillis - previousBlink >= blinkInterval) {
			previousBlink = currentMillis;

			blinkState = !blinkState;
		}
	} else if(currentState == GAME) {
		//------Player 1-----///
		//p1.setY(map(Esplora.readSlider(), 0, 1024, 110, 0));
		double joyY = Esplora.readJoystickY();
		joyY = joyY > 50 ? paddleSpeed : joyY  < -50 ? -paddleSpeed : 0;

		p1.changeY(joyY);

		//------Player 2-----//
		p2.setY(map(Esplora.readSlider(), 0, 1024, 110, 0));

		//------Ball------//
		if(ball.getX() < 0) ball.setVelX(-ball.getVelX());
		if(ball.getY() < 0) ball.setVelY(-ball.getVelY());
		if(ball.getX() + ball.getWidth() > WIDTH) ball.setVelX(-ball.getVelX());
		if(ball.getY() + ball.getHeight() > HEIGHT) ball.setVelY(-ball.getVelY());

		// Collision between paddle and ball
		if(rectCollision(ball.getX(), ball.getY(),
							ball.getWidth(), ball.getHeight(),
							p1.getX(), p1.getY(),
							p1.getWidth(), p1.getHeight())) {
			ball.setVelX(-ball.getVelX());
			ball.setX(p1.getX() + p1.getWidth()); // Fixes clipping 

			p1.forceRedraw();
			//Esplora.tone(262, 100);
		}

		if(rectCollision(ball.getX(), ball.getY(),
							ball.getWidth(), ball.getHeight(),
							p2.getX(), p2.getY(),
							p2.getWidth(), p2.getHeight())) {
			ball.setVelX(-ball.getVelX());
			ball.setX(p2.getX()); // Fixes clipping 

			p2.forceRedraw();
			//Esplora.tone(262, 100);
		}


		ball.changeX(ball.getVelX());
		ball.changeY(ball.getVelY());
	}
}

void render() {
	if(currentState == SPLASH) {
		tft.setTextColor(blinkState ? WHITE : BLACK);

		tft.setCursor(CENTER, 100);
		tft.print("Move the joystick to start...");
	} else if(currentState == GAME) {
		ball.draw(&tft);
		p1.draw(&tft);
		p2.draw(&tft);
	}
}

void loop() {
	input();
	update();
	render();
}