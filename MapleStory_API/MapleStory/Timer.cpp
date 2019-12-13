#include"Timer.h"
#include"Debug.h"

CTimer::CTimer() :
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iTick(0),
	m_iLimitFrame(0)
{

}

CTimer::~CTimer()
{

}

bool CTimer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTick);
	QueryPerformanceCounter(&m_tSecondTick);

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTick = {};
	QueryPerformanceCounter(&tTick);

	//���� ƽ - ����ƽ�� �ʴ� ƽ���� �������ָ�
	//���� ���ʰ� �������� �� �� �ִ�.
	//�� 1�������� ������ �ð��� ������ �� �ְ� �ȴ�.

	m_fDeltaTime = (tTick.QuadPart - m_tTick.QuadPart) /
		(float)m_tSecond.QuadPart;

	//������ ���� �� ���� ƽ�� ���� ƽ���� �������ش�.
	m_tTick = tTick;

	if (m_tSecondTick.QuadPart - tTick.QuadPart >= m_tSecond.QuadPart)
	{
		QueryPerformanceFrequency(&m_tSecond);
		m_tSecondTick = tTick;
	}
	m_fFPSTime += m_fDeltaTime;
	++m_iTick;

	if (m_iTick == 60)
	{
		m_fFPS = m_iTick / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iTick = 0;

		char strText[128] = {};
		sprintf_s(strText, "FPS : %f, DeltaTime : %f", m_fFPS, m_fDeltaTime);

		CDebug::OutputTitle(strText);
	}
}