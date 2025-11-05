#include "Texture.h"
#include "Variables.h"
#include "constant.h"
#include "Buttons.h"
#include "function.h"
#include "Timer.h"


using namespace std;
vector <vector<LButton> > Buttons(3, vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;
LTimer turnTimer;
Uint32 aiStartTime = 0;


//initialization func
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadmedia()
{
	bool success = true;
	//Open image of tiles
	if (!Tiles_image.loadFromFile("duLieu/images/tiles5.jpg"))
	{
		printf("Can't load this image from file!");
		success = false;
	}
	else
	{
		//Set sprites
		for (int i = 0;i < 13;++i)
		{
			Tilesprites[i].x = i * TILE_SIZE;
			Tilesprites[i].y = 0;
			Tilesprites[i].w = TILE_SIZE;
			Tilesprites[i].h = TILE_SIZE;
		}
	}
	//load digits
	if (!Digits.loadFromFile("duLieu/images/Untitled1.png"))
	{
		printf("Fail");
		success = false;
	}
	else
	{
		//Set sprites
		for (int i = 0;i < 10;i++)
		{
			Digitsprites[i].x = i * 28;
			Digitsprites[i].y = 0;
			Digitsprites[i].w = 28;
			Digitsprites[i].h = 46;
		}
	}

	if (!Flag_image.loadFromFile("duLieu/images/flag.png"))
	{
		printf("Fail");
		success = false;
	}

	//load easy table
	if (!easyTable.loadFromFile("duLieu/images/easy.png"))
	{
		printf("Fail");
		success = false;
	}
	//load medium table
	if (!mediumTable.loadFromFile("duLieu/images/medium.png"))
	{
		printf("Fail");
		success = false;
	}
	//load hard table
	if (!hardTable.loadFromFile("duLieu/images/hard.png"))
	{
		printf("Fail");
		success = false;
	}

	if (!aiTable.loadFromFile("duLieu/images/medium.png"))
	{
		printf("Fail");
		success = false;
	}

	//load face
	if (!winFace.loadFromFile("duLieu/images/winface.png"))
	{
		printf("Fail");
		success = false;
	}
	if (!loseFace.loadFromFile("duLieu/images/loseface.png"))
	{
		printf("Fail");
		success = false;
	}
	if (!playingFace.loadFromFile("duLieu/images/playingface.png"))
	{
		printf("Fail");
		success = false;
	}
	if (!back.loadFromFile("duLieu/images/backicon.png"))
	{
		success = false;
	}
	if (!sound_on.loadFromFile("duLieu/images/unmute.png"))
	{
		success = false;
	}
	if (!sound_off.loadFromFile("duLieu/images/mute.png"))
	{
		success = false;
	}
	//Open the font
	gFont = TTF_OpenFont("duLieu/font.ttf", 20);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	//load text
	SDL_Color textcolor1 = { 255,255,255 };
	if (!menu.loadFromRenderedText("START", textcolor1))
	{
		printf("Fail");
	}
	if (!menu1.loadFromRenderedText("EXIT", textcolor1))
	{
		printf("fail!");
	}
	SDL_Color color = { 255,0,0 };
	if (!menuColor.loadFromRenderedText("START", color))
	{
		printf("Fail");
		success = false;
	}
	if (!menu1Color.loadFromRenderedText("EXIT", color))
	{
		printf("Fail");
		success = false;
	}
	//Load music
	loseMusic = Mix_LoadMUS("duLieu/audio/scratch.wav");
	if (loseMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	winMusic = Mix_LoadMUS("duLieu/audio/beat.wav");
	if (winMusic == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	click = Mix_LoadWAV("duLieu/audio/click.wav");
	if (click == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

bool loadMenuMedia()
{
	bool success = true;
	//load background of menu
	if (!menuTheme.loadFromFile("duLieu/images/menu.jpg"))
	{
		printf("Fail!");
		success = false;
	}
	//load level choice
	if (!levelTheme.loadFromFile("duLieu/images/mode.jpg"))
	{
		printf("Fail");
		success = false;
	}
	if (!customStart.loadFromFile("duLieu/images/custom.png"))
	{
		printf("Fail");
		success = true;
	}
	//load choice text
	SDL_Color textColor = { 255,255,255 };
	if (!easyChoice.loadFromRenderedText("EASY MODE", textColor))
	{
		printf("Fail");
		success = false;
	}
	if (!mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor))
	{
		printf("Fail");
		success = false;
	}
	if (!hardChoice.loadFromRenderedText("HARD MODE", textColor))
	{
		printf("Fail");
		success = false;
	}
	if (!customChoice.loadFromRenderedText("CUSTOM MODE", textColor))
	{
		printf("Fail");
		success = false;
	}
    if (!aiChoice.loadFromRenderedText("AI MODE", textColor))
	{
		printf("Fail");
		success = false;
	}
	SDL_Color textcolor = { 255,0,0 };
	if (!easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor))
	{
		printf("Fail");
		success = false;
	}
	if (!mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor))
	{
		printf("Fail");
		success = false;
	}
	if (!hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor))
	{
		printf("Fail");
		success = false;
	}
	if (!customChoiceColor.loadFromRenderedText("CUSTOM MODE", textcolor))
	{
		printf("Fail");
		success = false;
	}
	if (!aiChoiceColor.loadFromRenderedText("AI MODE", textcolor))
	{
		printf("Fail");
		success = false;
	}
	return success;
}

//initialization games
void CreateBoard()
{
	srand(time(0));
	int mine = 0;
	//Initialization
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			sBoard[i][j] = 10;
			board[i][j] = 0;
		}
	}

	//Random mines in board
	while (mine < NumberOfMines)
	{
		int i = rand() % BOARD_SIZE_X;
		int j = rand() % BOARD_SIZE_Y;
		if (board[i][j] == 9) continue;
		board[i][j] = 9;
		mine++;
	}

	//Calculate the number of mines around each cell
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			if (board[i][j] == 9) continue;
			for (int x = -1;x <= 1;x++)
			{
				for (int y = -1;y <= 1;y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos < 0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
					if (board[xpos][ypos] == 9) board[i][j]++;
				}
			}
		}
	}
}

void setButtonPosition()
{
	face.setPosition(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	goBack.setPosition(0, 0);
	sound.setPosition(timeDigit_x - 10, 0);
	for (int i = 0;i < BOARD_SIZE_X;++i)
	{
		for (int j = 0;j < BOARD_SIZE_Y;++j)
		{
			Buttons[i][j].setPosition(i * TILE_SIZE + distance_x, j * TILE_SIZE + distance_y);
		}
	}
}

// viet lai

void createMenu()
{
	menuTheme.render(0, 0);
	menu.render(300, 400);
	menu1.render(450, 400);
	SDL_RenderPresent(renderer);
}

void createModeMenu()
{
	levelTheme.render(0, 0);
	easyChoice.render(300, 150);
	mediumChoice.render(300, 200);
	hardChoice.render(300, 250);
	customChoice.render(300, 300);
	aiChoice.render(300, 350);
}

void showMenu()
{
	bool startInside = false;
	bool exitInside = false;
	bool isMenuShowing = true;
	SDL_Event event;
	createMenu();
	while (isMenuShowing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isMenuShowing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 300 && x < 300 + menu.getWidth() && y > 400 && y < 400 + menu.getHeight()) startInside = true;
				else startInside = false;
				if (x > 450 && x < 450 + menu1.getWidth() && y > 400 && y < 400 + menu1.getHeight()) exitInside = true;
				else exitInside = false;
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (startInside == true)
						{
							start = true;
							isMenuShowing = false;
						}
						if (exitInside == true)
						{
							mainLoop = false;
							isMenuShowing = false;

						}
					}
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					if (startInside == true)
					{
						menuColor.render(300, 400);
					}
					else menu.render(300, 400);
					if (exitInside == true)
					{
						menu1Color.render(450, 400);

					}
					else menu1.render(450, 400);
				}

			}
			SDL_RenderPresent(renderer);
		}
	}
}

void showModeChoice()
{
	bool easyInside = false;
	bool mediumInside = false;
	bool hardInside = false;
	bool customInside = false;
    bool aiInside = false;

	SDL_Event event;
	createModeMenu();
	while (isChoosing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isChoosing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 300 && x < 300 + easyChoice.getWidth() && y > 150 && y < 150 + easyChoice.getHeight()) easyInside = true;
				else easyInside = false;
				if (x > 300 && x < 300 + mediumChoice.getWidth() && y > 200 && y < 200 + mediumChoice.getHeight()) mediumInside = true;
				else mediumInside = false;
				if (x > 300 && x < 300 + hardChoice.getWidth() && y > 250 && y < 250 + hardChoice.getHeight()) hardInside = true;
				else hardInside = false;
				if (x > 300 && x < 300 + customChoice.getWidth() && y > 300 && y < 300 + customChoice.getHeight()) customInside = true;
				else customInside = false;
				if (x > 300 && x < 300 + aiChoice.getWidth() && y > 350 && y < 350 + aiChoice.getHeight()) aiInside = true;
				else aiInside = false;
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (easyInside == true)
						{
							isRunning = true;
							isChoosing = false;
							customMode = false;
							aiMode = false;
							timer.start();
							easy = true;
							medium = false;
							hard = false;
							cus = false;
							ai = false;
							SDL_SetWindowSize(window, 294, 436);
							setGameMode(9, 9, 10, 21, 163, 25, 80, 235, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
						if (mediumInside == true)
						{
							isRunning = true;
							isChoosing = false;
							customMode = false;
							aiMode = false;
							timer.start();
							easy = false;
							medium = true;
							hard = false;
							cus = false;
							ai = false;
							SDL_SetWindowSize(window, 488, 630);
							setGameMode(16, 16, 40, 21, 163, 25, 80, 430, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
						if (hardInside == true)
						{
							isRunning = true;
							isChoosing = false;
							customMode = false;
							aiMode = false;
							timer.start();
							easy = false;
							medium = false;
							hard = true;
							cus = false;
							ai = false;
							SDL_SetWindowSize(window, 880, 632);
							setGameMode(30, 16, 99, 21, 163, 25, 80, 820, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							CreateBoard();
						}
						if (customInside == true)
						{
							isChoosing = false;
							customMode = true;
							aiMode = false;
							easy = false;
							medium = false;
							hard = false;
							cus = true;
							ai = false;
						}
						if (aiInside == true)
                        {
                            // viet lai

							isChoosing = false;
							customMode = false;
							aiMode = true;

							easy = false;
							medium = false;
							hard = false;
							cus = false;
							ai = true;

                        }
					}
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					if (easyInside == true) easyChoiceColor.render(300, 150);
					else easyChoice.render(300, 150);
					if (mediumInside == true) mediumChoiceColor.render(300, 200);
					else mediumChoice.render(300, 200);
					if (hardInside == true) hardChoiceColor.render(300, 250);
					else hardChoice.render(300, 250);
					if (customInside == true) customChoiceColor.render(300, 300);
					else customChoice.render(300, 300);
					if (aiInside == true) aiChoiceColor.render(300, 350);
					else aiChoice.render(300, 350);
				}
			}
			SDL_RenderPresent(renderer);
		}
	}
}

void CustomMode()
{
	SDL_Event e{};
	SDL_Color black = { 0,0,0,0 };
	SDL_SetWindowSize(window, 400, 600);
	customStart.render(0, 0);
	string width, height, mine;
	int w = 0, h = 0, m = 0;
	char inputChar;
	bool widthInside = false;
	bool heightInside = false;
	bool mineInside = false;
	bool play = false;
	while (customMode)
	{
		SDL_StartTextInput();
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				customMode = false;
				mainLoop = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 200 && x < 267 && y>374 && y < 394) widthInside = true;
				else widthInside = false;
				if (x > 200 && x < 267 && y>400 && y < 420) heightInside = true;
				else heightInside = false;
				if (x > 200 && x < 267 && y>427 && y < 447) mineInside = true;
				else mineInside = false;
				if (x > 150 && x < 250 && y>488 && y < 526) play = true;
				else play = false;
				break;
			case SDL_TEXTINPUT:
				inputChar = e.text.text[0];
				if (inputChar >= '0' && inputChar <= '9')
				{
					if (widthInside && width.length() < 6)
					{
						width += e.text.text;
						w *= 10;
						w += (int)(inputChar - 48);
						wInput.loadFromRenderedText(width.c_str(), black);
					}
					else if (heightInside && height.length() < 6)
					{
						height += e.text.text;
						h *= 10;
						h += (int)(inputChar - 48);
						hInput.loadFromRenderedText(height.c_str(), black);
					}
					else if (mineInside && mine.length() < 6)
					{
						mine += e.text.text;
						m *= 10;
						m += (int)(inputChar - 48);
						mInput.loadFromRenderedText(mine.c_str(), black);
					}
				}
				break;
			default:
				break;
			}
		}

		wInput.render(201, 370);
		hInput.render(201, 397);
		mInput.render(201, 423);

		if (play == true)
		{
			isRunning = true;
			customMode = false;
			play = false;
			timer.start();
			SDL_SetWindowSize(window, w * TILE_SIZE, h * TILE_SIZE + 110);
			setGameMode(w, h, m, 0, 110, 10, 60, w * TILE_SIZE - 40 , BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
			CreateBoard();
		}
		SDL_StopTextInput();
		SDL_RenderPresent(renderer);
	}

	width = "";
	height = "";
	mine = "";
	widthInside = false;
	heightInside = false;
	mineInside = false;
	wInput.free();
	hInput.free();
	mInput.free();
}

void AiMode()
{

    isRunning = true;
    turnTimer.startCountdown(8000);
    SDL_SetWindowSize(window, 488, 630);
    setGameMode(16, 16, 40, 21, 163, 25, 80, 430, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
    CreateBoard();
    isPlayerTurn = true;
    isAITurn = false;
    aiThinking = false;
}

void nextTurn()
{
    if (isPlayerTurn) {
        isPlayerTurn = false;
        isAITurn = true;
    } else {
        isPlayerTurn = true;
        isAITurn = false;
    }
    playerHasMoved = false;
    aiThinking = false;
    aiStartTime = 0;
    turnTimer.startCountdown(8000);
}

void openRandomCellForAI()
{
    int x, y;
    do {
        x = rand() % BOARD_SIZE_X;
        y = rand() % BOARD_SIZE_Y;
    } while (sBoard[x][y] != 10);

    reveal(x, y);
    if (board[x][y] == 9) {
        lose = true;
    }
}

void checkFinalWinner()
{
    int playerFlags = 0, aiFlags = 0;

    for (int i = 0; i < BOARD_SIZE_X; ++i)
    for (int j = 0; j < BOARD_SIZE_Y; ++j)
    {
        if (board[i][j] == 9) { // bom thật
            if (sBoard[i][j] == 11)
                playerFlags++;
            if (sBoard[i][j] == 12)
                aiFlags++;
        }
    }

    if (playerFlags > aiFlags) {
        isWinning = true;
    } else if (aiFlags > playerFlags) {
        lose = true;
    }
}

void aiMakeMove()
{


    int x, y;
    do {
        x = rand() % BOARD_SIZE_X;
        y = rand() % BOARD_SIZE_Y;
    } while (sBoard[x][y] != 10);

    reveal(x, y);

    if (board[x][y] == 9)
    {
        isWinning = true;
        Mix_PlayMusic(winMusic, 1);  

        // Hiển thị mặt cười
        winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);

        revealAll = true; // báo hiệu cần lật toàn bộ bàn

        turnTimer.pause();

        // Ngừng cho AI đi tiếp
        isAITurn = false;
        isPlayerTurn = false;
        aiThinking = false;

        return;
    }

    Mix_PlayChannel(-1, click, 0);
}


//ingame func
void handleEvent()
{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
				mainLoop = false;
			}
			face.handleEventAgain(&e);
			goBack.handleEventBack(&e);
			sound.handleEventMute(&e);

			if (ai == true)
            {
                if (!isPlayerTurn) continue;    // nếu không phải lượt người -> bỏ qua xử lý ô (nhưng không return)
                if (playerHasMoved) continue;   // nếu người đã đi -> bỏ qua
            }
			//viet lai
			for (int i = 0; i < BOARD_SIZE_X; i++)
			{
				for (int j = 0; j < BOARD_SIZE_Y; j++)
				{
					Buttons[i][j].handleEvent(&e);


				}
			}

		}
}



void reveal(int i, int j)
{
	if (sBoard[i][j] == 10 || sBoard[i][j] == 11 || sBoard[i][j] == 12)
	{
		if (sBoard[i][j] == 11 || sBoard[i][j] == 12)
		{
			return;
		}
		sBoard[i][j] = board[i][j];
		if (sBoard[i][j] != 9) CountTileLeft--;
		if (sBoard[i][j] == 0)
		{
			for (int x = -1;x <= 1;x++)
			{
				for (int y = -1;y <= 1;y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos<0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
					reveal(xpos, ypos);
				}
			}
		}
	}
}

void chordOpen(int i, int j)
{

    if (sBoard[i][j] >= 1 && sBoard[i][j] <= 8)
    {
        int flagCount = 0;


        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                int nx = i + x;
                int ny = j + y;
                if (nx < 0 || nx >= BOARD_SIZE_X || ny < 0 || ny >= BOARD_SIZE_Y) continue;
                if (sBoard[nx][ny] == 11 || sBoard[nx][ny] == 12) flagCount++;
            }
        }


        if (flagCount == sBoard[i][j])
        {
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int nx = i + x;
                    int ny = j + y;
                    if (nx < 0 || nx >= BOARD_SIZE_X || ny < 0 || ny >= BOARD_SIZE_Y) continue;


                    if (sBoard[nx][ny] == 10)
                    {

                        if (board[nx][ny] == 9)
                        {
                            lose = true;
                            return;
                        }


                        reveal(nx, ny);
                    }
                }
            }
        }
    }
}


void isPlayerWinning()
{
	if (CountTileLeft == NumberOfMines) isWinning = true;
}

/*void isPlayerWinningWithAi()
{
    if()
}*/
//viet lai quan ly choi voi ai
void GameManager()
{

	if (playAgain == true) {
            PlayAgain();
	}
	//if we lose
	if (lose == true)
	{
	    if(ai == true) {turnTimer.pause();}
		else timer.pause();
		loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
		for (int i = 0;i < BOARD_SIZE_X;i++)
		{
			for (int j = 0;j < BOARD_SIZE_Y;j++)
			{
				Buttons[i][j].loseRender(i, j);
			}
		}

	}
	//if we win
	if (isWinning == true )
	{
	    if(ai == true) {turnTimer.pause();}
	    else timer.pause();
		winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);

        if (revealAll)
        {
            for (int i = 0; i < BOARD_SIZE_X; i++)
            {
                for (int j = 0; j < BOARD_SIZE_Y; j++)
                {
                    Buttons[i][j].loseRender(i, j);
                }
            }
        }
	}

}
void PlayAgain()
{
	//timer.stop();
    if(ai == true) {
        turnTimer.startCountdown(8000);
        aiThinking = false;
        aiStartTime = 0;
    } else timer.start();
	CreateBoard();
	Mix_HaltMusic();
	mineCountLeft = NumberOfMines;
	CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
	isWinning = false;
	lose = false;
	playAgain = false;
}
void MineManager()
{
	int n = mineCountLeft;
	if (mineCountLeft < 10)
	{
		Digits.render(digit_x, digit_y, &Digitsprites[0]);
		for (int i = 0;i <= 9;i++)
		{
			if (i == mineCountLeft) Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
		}
	}

	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}

void TimeManager(bool isCountdownMode)
{
    int n;

    if (isCountdownMode)
        n = turnTimer.getRemainingTime() / 1000; // đếm ngược
    else
        n = timer.getTicks() / 1000;         // đếm tiến

    if (n < 0) n = 0;


    if (n < 10)
    {
        for (int i = 0; i <= 9; i++)
        {
            if (i == n)
                Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
        }
    }
    else
    {

        int i = 0;
        while (n > 0)
        {
            int x = n % 10;
            n /= 10;
            Digits.render(timeDigit_x - i * 28, digit_y, &Digitsprites[x]);
            i++;
        }
    }
}


void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x)
{
	BOARD_SIZE_X = x;
	BOARD_SIZE_Y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;
	digit_x = d1x;
	digit_y = d1y;
	timeDigit_x = dtx;

	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		Buttons[i].resize(BOARD_SIZE_Y);
	}
	sBoard.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		sBoard[i].resize(BOARD_SIZE_Y);
	}
	board.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		board[i].resize(BOARD_SIZE_Y);
	}
}

void renderButton()
{
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

bool aiMakeMoveSmart()
{
    std::vector<std::pair<int,int>> safeCells;    // ô chắc chắn an toàn
    std::vector<std::pair<int,int>> bombCells;    // ô chắc chắn là bom
    std::vector<std::pair<int,int>> chordCells;   // ô có thể chord

    for (int i = 0; i < BOARD_SIZE_X; ++i)
    {
        for (int j = 0; j < BOARD_SIZE_Y; ++j)
        {
            int val = sBoard[i][j];

            if (val < 1 || val > 8) continue; // chỉ phân tích ô đã mở có số

            int flag = 0, hidden = 0;
            std::vector<std::pair<int,int>> hiddenList;

            // đếm số cờ & ô ẩn xung quanh
            for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
            {
                int x = i + dx;
                int y = j + dy;
                if (x < 0 || y < 0 || x >= BOARD_SIZE_X || y >= BOARD_SIZE_Y) continue;

                if (sBoard[x][y] == 11 || sBoard[x][y] == 12) flag++; 
                else if (sBoard[x][y] == 10) {
                    hidden++;
                    hiddenList.push_back({x,y});
                }
            }

            if (hidden == 0) continue;

            // quy tắc 1: đủ cờ, các ô chưa mở an toàn 
            if (flag == val)
                safeCells.insert(safeCells.end(), hiddenList.begin(), hiddenList.end());

            // quy tắc 2: nếu số cờ và số ô chưa mở = số trên ô -> các ô chưa mở là bom
            if (flag + hidden == val)
                bombCells.insert(bombCells.end(), hiddenList.begin(), hiddenList.end());

            // quy tắc 3: có thể mở các ô xung quanh khi đủ cờ
            if (flag == val)
                chordCells.push_back({i, j});
        }
    }


    //Mở các ô an toàn trước
    if (!safeCells.empty())
    {
        auto [x, y] = safeCells[rand() % safeCells.size()];
        bool hitBomb = revealUsingLogic(x, y);
        return hitBomb;
    }

    //Mở các ô xung quanh nếu cờ = số trên ô
    if (!chordCells.empty())
    {
        auto [cx, cy] = chordCells[rand() % chordCells.size()];
        chordOpen(cx, cy);

        if (lose) return true;  // AI mở trúng bom → người thắng

        Mix_PlayChannel(-1, click, 0);
        return false;
    }

    // Đặt cờ
    if (!bombCells.empty() && mineCountLeft > 0)
    {
        auto [x,y] = bombCells[rand() % bombCells.size()];
        sBoard[x][y] = 12;      // đặt cờ
        mineCountLeft--;
        Mix_PlayChannel(-1, click, 0);
        return false;
    }

    //random
    int x, y;
    do {
        x = rand() % BOARD_SIZE_X;
        y = rand() % BOARD_SIZE_Y;
    } while (sBoard[x][y] != 10);

    return revealUsingLogic(x, y);
}


// Hàm Máy mở ô
bool revealUsingLogic(int x, int y)
{
    reveal(x, y);

    if (board[x][y] == 9)
        return true;

    Mix_PlayChannel(-1, click, 0);
    return false;
}

void renderGame()
{
	if (mute == false)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		sound_on.render(timeDigit_x - 10, 0);
		loseMusic = Mix_LoadMUS("duLieu/audio/scratch.wav");
		winMusic = Mix_LoadMUS("duLieu/audio/beat.wav");
		click = Mix_LoadWAV("duLieu/audio/click.wav");
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		sound_off.render(timeDigit_x - 10, 0);
		click = NULL;
		winMusic = NULL;
		loseMusic = NULL;
	}
	if (easy == true || medium == true || hard == true || cus == true || ai == true)
	{
		if (easy == true)
		{
			easyTable.render(0, 50);
			TimeManager(false);
			isPlayerWinning();
		}
		if (medium == true)
		{
			mediumTable.render(0, 50);
			TimeManager(false);
			isPlayerWinning();
		}
		if (hard == true)
		{
			hardTable.render(0, 50);
			TimeManager(false);
			isPlayerWinning();
		}
		if (cus == true)
		{
			//SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			TimeManager(false);
			isPlayerWinning();
		}


		if (ai == true)
        {
            aiTable.render(0,50);
            TimeManager(true);

            if (turnTimer.isTimeUp()) {
                if (isPlayerTurn) openRandomCellForAI();
                nextTurn();
                return;
            }
            // Lượt của AI
            if (isAITurn)
            {
                // Bắt đầu tính thời gian "suy nghĩ" của AI
                if (!aiThinking)
                {
                    aiThinking = true;
                    aiStartTime = SDL_GetTicks(); 
                }

                // Nếu AI đang suy nghĩ và đã đủ 3 giây → AI đi
                else if (SDL_GetTicks() - aiStartTime >= 3000)
                {
                    bool aiHitMine = aiMakeMoveSmart();
                    aiThinking = false;

                    if (aiHitMine) { // AI chọn trúng bom => người chơi thắng
                        isWinning = true;
                        revealAll = true;
                        Mix_PlayMusic(winMusic, 1);
                        winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
                        turnTimer.pause();
                        isRunning = false;
                        return;
                    }

                    nextTurn(); // Kết thúc lượt AI
                    return;
                }
            }

            // Nếu chọn hết ô an toàn, so số cờ đã đánh
            if (CountTileLeft == 0 && !lose && !isWinning)
                checkFinalWinner();
        }
	}

	playingFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	renderButton();
	back.render(0, 0);
	MineManager();


	GameManager();
	SDL_RenderPresent(renderer);
}

//close SDL
void close()
{
	//Free loaded images
	Tiles_image.free();
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

