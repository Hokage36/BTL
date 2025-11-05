#pragma once
#include<SDL.h>
class LTimer
{
public:
	LTimer();
	void start();
	void stop();
	void pause();
	unsigned int getTicks();
	bool isStarted();
	bool isPaused();

	//Thêm phần đếm ngược
    void startCountdown(unsigned int countdownMs);
    unsigned int getRemainingTime();
    bool isTimeUp();

private:
	unsigned int mStartTicks;
	unsigned int mPausedTicks;
	bool mPaused;
	bool mStarted;

	unsigned int mCountdownDuration;
};
