#include "Math.h"

float CMath::GetDistance(const POSITION& tSrc, const POSITION& tDest)
{
	float fWidth = tSrc.x - tDest.x;
	float fHeight = tSrc.y - tDest.y;
	return sqrtf(fWidth * fWidth + fHeight * fHeight);
}

//tSrc : 현재위치
//tDest : 대상위치
float CMath::GetDegree(const POSITION& tSrc, const POSITION& tDest)
{
	//abs : 절대값을 구해주는 함수이다.
	float fWidth = tDest.x - tSrc.x;

	float fLength = GetDistance(tSrc, tDest);
	
	//코사인 세타값을 구함.
	float fAngle = fWidth / fLength;

	//구해준 코사인 세타값을 역함수를 이용하여 라디안값으로 변환
	fAngle = acosf(fAngle);
	//라디안을 디그리로 변경
	fAngle = RadianToDegree(fAngle);
	
	if (tDest.y < tSrc.y)
		fAngle = 360.f - fAngle;
	
	return fAngle;
}

float CMath::RadianToDegree(float fRadian)
{
	return fRadian * 180.f / PI;
}

float CMath::DegreeToRadian(float fDegree)
{
	return fDegree * PI / 180.f;
}
