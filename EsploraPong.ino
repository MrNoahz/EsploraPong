// TFT is 160 x 128

#include <Esplora.h>
#include <SPI.h>
#include <TFT_ST7735.h>

#include "Paddle.h"

#define CS 7
#define DC 0
#define RST 1

enum State {
	SPLASH,
	GAME
};

// Global vars
TFT_ST7735 tft = TFT_ST7735(CS, DC, RST);

State currentState = SPLASH;

// Splash vars
unsigned long previousBlink = 0;
const long blinkInterval = 800;
bool blinkState = false;

// Game vars
Paddle p1(4, 54, 2, 20, WHITE);
Paddle p2(154, 54, 2, 20, WHITE);

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

void setup() {
	Serial.begin(9600);
	Serial.println("Beginning");

	tft.begin();
	tft.setRotation(3);

	p1.draw(&tft);

	splash();
}

void loop() {
	if(currentState == SPLASH) {
		unsigned long currentMillis = millis();

		if(currentMillis - previousBlink >= blinkInterval) {
			previousBlink = currentMillis;

			if(blinkState == true) {
				tft.setTextColor(WHITE);
			} else {
				tft.setTextColor(BLACK);
			}

			tft.setCursor(CENTER, 100);
			tft.print("Move the joystick to start...");

			blinkState = !blinkState;
		}

		if(Esplora.readJoystickX() > 60 || Esplora.readJoystickX() < -60 ||
			Esplora.readJoystickY() > 60 || Esplora.readJoystickY() < -60) {
			currentState = GAME;
			tft.clearScreen();
		}
	} else if(currentState == GAME) {

		//p1.setY(map(Esplora.readSlider(), 0, 1024, 110, 0));
		double joyY = Esplora.readJoystickY();
		joyY = joyY > 50 ? 0.3 : joyY  < -50 ? -0.3 : 0;

		Serial.println(p1.getY());

		p1.changeY(joyY);

		p1.draw(&tft);
	}
}