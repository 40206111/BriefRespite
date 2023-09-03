#pragma once


class BarManager
{
private:
	unsigned int TimeTilClose;

public:
	float HappyMeter = 0;
	float EnergyMeter = 0;
	float SocialMeter = 0;
	float OpenMeter = 0;

	//Stop TimeTilClose going below zero (which as an unsigned int will just make it reallly big)
	void SetTimeTilClose(int value)
	{
		TimeTilClose = value < 0 ? 0 : value;
	}
	void ChangeTimeTilClose(int delta)
	{
		int value = TimeTilClose - delta;
		TimeTilClose = value < 0 ? 0 : value;
	}
	unsigned int GetTimeTilClose()
	{
		return TimeTilClose;
	}

};