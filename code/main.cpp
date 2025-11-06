#include "Texture.h"
#include "Buttons.h"
#include "Variables.h"
#include "constant.h"
#include "function.h"

using namespace std;


int main(int argc, char* argv[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (loadmedia())
		{
			if (loadMenuMedia())
			{
				showMenu();
				while (mainLoop)
				{
					if (isChoosing)
					{
						showModeChoice();
					}
					if(customMode) CustomMode();
					if(aiMode) AiMode();
					while (isRunning)
					{
						handleEvent();
						setButtonPosition();
						renderGame();
					}
				}
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
