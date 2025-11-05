#pragma once
#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H
#include "Texture.h"
#include "constant.h"
#include "Buttons.h"


// initialization
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// loop variable
extern bool isRunning;
extern bool showmenu;
extern bool isChoosing;
extern bool mainLoop;
extern bool customMode;
extern bool aiMode;

//win or lose
extern bool isWinning;
extern bool lose;



// image use in game
extern LTexture menuTheme;
extern LTexture levelTheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;
extern LTexture customStart;
extern LTexture aiTable;

extern LTexture back;
extern LTexture sound_on;
extern LTexture sound_off;

// image face
extern LTexture winFace;
extern LTexture playingFace;
extern LTexture loseFace;

// Tiles in board
extern LTexture Tiles_image;
extern LTexture Flag_image;
extern SDL_Rect Tilesprites[13];
extern SDL_Rect Flag_sprite;

// text
extern LTexture menu;
extern LTexture menu1;
extern LTexture menuColor;
extern LTexture menu1Color;
extern LTexture easyChoice;
extern LTexture mediumChoice;
extern LTexture hardChoice;
extern LTexture customChoice;
extern LTexture aiChoice;
extern LTexture returnChoice;
extern LTexture easyChoiceColor;
extern LTexture mediumChoiceColor;
extern LTexture hardChoiceColor;
extern LTexture customChoiceColor;
extern LTexture aiChoiceColor;
extern LTexture returnChoiceColor;
extern LTexture wInput;
extern LTexture hInput;
extern LTexture mInput;
extern TTF_Font* gFont;

extern LTexture gTextTexture;

// Create board data
extern std::vector <std::vector<int> > sBoard;
extern std::vector <std::vector<int> > board;

// mines
extern int mineCountLeft;
extern int CountTileLeft;

// audio
extern bool mute;
extern Mix_Chunk* click;
extern Mix_Music* loseMusic;
extern Mix_Music* winMusic;

// distance
extern int distance_x;
extern int distance_y;
extern int digit_x;
extern int digit_y;
extern int timeDigit_x;

// digits image
extern LTexture Digits;
extern SDL_Rect Digitsprites[10];

// board size
extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int NumberOfMines;

// boolean
extern bool playAgain;
extern bool saveScore;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;
extern bool cus;
extern bool ai;

extern bool isPlayerTurn;
extern bool isAITurn;
extern bool aiThinking;
extern int playerFlags;
extern int aiFlags;
extern bool playerHasMoved;

extern bool revealAll;
extern bool revealUsingLogic(int x, int y);

#endif
