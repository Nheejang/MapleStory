#include"Player.h"
#include"Input.h"
#include"Math.h"
#include"Camera.h"
CPlayer::CPlayer()
{
	SetTag("Player");
	m_eType = OT_PLAYER;
	m_bGravity = false;
}

CPlayer::CPlayer(const CPlayer& player)
	:CCharacter(player)
{

}
CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
	SetMoveSpeed(300.f);
	//SetTexture("Teemo", TEXT("Teemo.bmp"));

	//AddAnimationClip("Walk", ACT_ATLAS, AO_LOOP, 45, 60, 14, 1, 21, 8, 0, 1, 1.0, "AnimTest", TEXT("Left.bmp"));
	AddAnimationClip("Walk", ACT_ATLAS, AO_LOOP, 256, 256, 3, 1, 3, 1, 0, 0, 1.0, "AnimTest", TEXT("Player_Stand_Right.bmp"),true, RGB(255, 255, 255));
	
	//LoadAnimation("PlayerIdle.txt");
	//SetPos(720, 360.f);
	SetSize(300.f, 300.f);
//	SetPivot(0.0f, 0.0f);

	//SetGravity(true);
	return true;
}


int CPlayer::Input(float fTime)
{


	//if (KEYPUSH("MoveLeft"))
	//{
	//	//Rotation(fTime);
	//	Move(-m_fMoveSpeed, 0.f, fTime);
	//}
	//
	//if (KEYPUSH("MoveRight"))
	//{
	//	//Rotation(-fTime);
	//	Move(m_fMoveSpeed, 0.f, fTime);
	//}

	//if (KEYPUSH("MoveUp"))
	//{
	//	Move(0.f, -m_fMoveSpeed, fTime);
	//	//MoveByAngle(fTime);
	//}

	//if (KEYPUSH("MoveDown"))
	//{
	//	Move(0.f, m_fMoveSpeed, fTime);
	//	//MoveByAngle(-fTime);
	//}

	//if (KEYPRESS("Jump"))
	//{
	//	SetForce(300.f);
	//}
	//if (KEYPUSH("Fast"))
	//{
	//	m_fMoveSpeed+=50;
	//}
	//if (KEYPUSH("Slow"))
	//{
	//	m_fMoveSpeed -= 50;
	//}

	return 0;
}


int CPlayer::Update(float fTime)
{
	CCharacter::Update(fTime);

	// 이전에 위치해 있던 곳과 현재 위치를 비교하여준다.
	// 이전 위치를 구해준다.
//	POSITION	tPrevPos = m_tPos - m_tMove;
	
	return 0;
}

int CPlayer::LateUpdate(float fTime)
{
	CCharacter::LateUpdate(fTime);

	return 0;
}

void CPlayer::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CPlayer::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	//POSITION	tCameraPos = GET_SINGLE(CCamera)->GetPos();

	//POSITION	tCenter = m_tPos - tCameraPos;


	//// 방향을 표시할 선을 그려준다.
	//MoveToEx(hDC, tCenter.x, tCenter.y, nullptr);

	//POSITION	tLineEnd;
	//tLineEnd.x = tCenter.x + cosf(CMath::DegreeToRadian(m_fAngle)) * 80.f;
	//tLineEnd.y = tCenter.y + sinf(CMath::DegreeToRadian(m_fAngle)) * 80.f;

	//LineTo(hDC, tLineEnd.x, tLineEnd.y);

	//POSITION	tLT = m_tPos - m_tSize * m_tPivot;
	//Rectangle(hDC, tLT.x, tLT.y, tLT.x + m_tSize.x, tLT.y + m_tSize.y);
//	TextOutA(hDC, m_tPos.x, m_tPos.y, "Test", strlen("Test"));
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}
