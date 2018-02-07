#include <Esplora.h>
#include <SPI.h>
#include <TFT_ST7735.h>

#define CS 7
#define DC 0
#define RST 1

TFT_ST7735 tft = TFT_ST7735(CS, DC, RST);

void splash() {
	tft.clearScreen();

	tft.setTextScale(0);
	tft.setCursor(CENTER, CENTER);
	tft.print("Esplora Pong");
	delay(1000);
	tft.clearScreen();
}

void setup() {
	tft.begin();
	tft.setRotation(1);

	splash();
}

void loop() {

}