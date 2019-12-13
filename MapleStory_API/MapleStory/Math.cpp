#include "Math.h"

float CMath::GetDistance(const POSITION& tSrc, const POSITION& tDest)
{
	float fWidth = tSrc.x - tDest.x;
	float fHeight = tSrc.y - tDest.y;
	return sqrtf(fWidth * fWidth + fHeight * fHeight);
}

//tSrc : ������ġ
//tDest : �����ġ
float CMath::GetDegree(const POSITION& tSrc, const POSITION& tDest)
{
	//abs : ���밪�� �����ִ� �Լ��̴�.
	float fWidth = tDest.x - tSrc.x;

	float fLength = GetDistance(tSrc, tDest);
	
	//�ڻ��� ��Ÿ���� ����.
	float fAngle = fWidth / fLength;

	//������ �ڻ��� ��Ÿ���� ���Լ��� �̿��Ͽ� ���Ȱ����� ��ȯ
	fAngle = acosf(fAngle);
	//������ ��׸��� ����
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
