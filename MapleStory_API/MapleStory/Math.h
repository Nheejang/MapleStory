#pragma once
#include"Game.h"

class CMath
{
public:
	static float GetDistance(const POSITION& tSrc, const POSITION& tDest);
	static float GetDegree(const POSITION& tSrc, const POSITION& tDest);
	static float RadianToDegree(float fRadian);
	static float DegreeToRadian(float fDegree);
};