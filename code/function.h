#pragma once
#pragma once
#include "Timer.h"
#include "AI.h"
#include <SDL.h>
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
void AiMode();
void showMenu();
void showModeChoice();
void setButtonPosition();

//ingame func
void isPlayerWinning();
void MineManager();
void PlayAgain();
void GameManager();
void TimeManager(bool isCountdownMode);
void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);
void renderButton();
void handleEvent();
void reveal(int i, int j);

void renderGame();

void nextTurn();
void openRandomCell();
void checkFinalWinner();
bool aiMakeMoveSmart();
