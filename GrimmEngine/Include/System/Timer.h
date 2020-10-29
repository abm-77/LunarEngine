#pragma once


class Timer
{

public:

	void Start();
	void Pause();
	void Unpause();
	void Reset();
	void Tick();
	
	double GetElapsed();
	bool IsPaused();
private:
	bool paused;
	double startTime;
	double  elapsedTime;
	double pausedTime;
	double totalPausedTime;
	double pausedStartTime;
};