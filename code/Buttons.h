#pragma once
#pragma once
#include "Timer.h"
#include <SDL.h>

class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//set button in game
	void handleEventAgain(SDL_Event* e);
	void handleEventBack(SDL_Event* e);
	void handleEventMute(SDL_Event* e);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(int i, int j);

	//Shows button sprite when we lose
	void loseRender(int i, int j);

private:
	//Top left position
	SDL_Point mPosition;
};

//initialization func
bool init();
bool loadmedia();
bool loadMenuMedia();

//close SDL
void close();

//initialization games
void CreateBoard();
void createMenu();
void createModeMenu();
void CustomMode();
void showMenu();
void showModeChoice();
void setButtonPosition();

//ingame func
void isPlayerWinning();
void chordOpen(int i, int j);
void MineManager();
void PlayAgain();
void GameManager();
void TimeManager();
void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);
void renderButton();
void handleEvent();
void reveal(int i, int j);
void renderGame();
