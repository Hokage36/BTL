#include "Timer.h"


LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;

	mCountdownDuration = 0;
}
void LTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

unsigned int LTimer::getTicks()
{
	//The actual timer time
	unsigned int time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

		return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

void LTimer::startCountdown(unsigned int countdownMs)
{
    mCountdownDuration = countdownMs;
    start(); // dùng lại hàm start có sẵn
}

unsigned int LTimer::getRemainingTime()
{
    if (!mStarted)
        return 0;

    unsigned int elapsed = getTicks(); // đã trôi qua bao nhiêu ms
    if (elapsed >= mCountdownDuration)
        return 0; // hết giờ

    return mCountdownDuration - elapsed;
}

bool LTimer::isTimeUp()
{
    return mStarted && (getTicks() >= mCountdownDuration);
}
