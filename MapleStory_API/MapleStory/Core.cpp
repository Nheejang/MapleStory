#include"Core.h"
#include"Timer.h"
#include"Input.h"
#include"PathManager.h"
#include"SceneManager.h"
#include"Camera.h"
#include"Debug.h"
#include"ResourceManager.h"
#include"Texture.h"
//#include "StageManager.h"


DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

CCore::CCore() :
	m_pBackBuffer(nullptr)
{
#ifdef _DEBUG
	//콘솔창 생성함수
	AllocConsole();
#endif //_DEBUG

	CDebug::OutputConsole("Console Test\n");
	CDebug::OutputVisual("Test Visual\n");

	m_hDC = 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(358);

}

CCore::~CCore()
{
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CResourceManager);
	DESTROY_SINGLE(CInput);
	SAFE_RELEASE(m_pBackBuffer);
	SAFE_DELETE(m_pTimer);
	//SAFE_RELEASE(m_pBackBuffer);

	if (m_hDC)
	{
		ReleaseDC(m_hWnd, m_hDC);
	}

#ifdef _DEBUG
	FreeConsole();
#endif //_DEBUG
}

bool CCore::Init(HINSTANCE hInst, unsigned int iWidth, unsigned int iHeight,
	const TCHAR* pTitle, const TCHAR* pClass, int iIconID)
{
	m_hInst = hInst;

	m_tResolution.iWidth = iWidth;
	m_tResolution.iHeight = iHeight;

	Register(pClass, iIconID);

	CreateWnd(pTitle, pClass);

	//현재 생성된 윈도우에 출력할 DC를 만들어준다.
	m_hDC = GetDC(m_hWnd);
	
	//타이머를 생성한다.
	m_pTimer = new CTimer;

	if (!m_pTimer->Init())
	{
		SAFE_DELETE(m_pTimer);
		return false;
	}

	// 경로관리자 초기화
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// 입력관리자 초기화
	if (!GET_SINGLE(CInput)->Init())
		return false;

	// 리소스 관리자 초기화
	if (!GET_SINGLE(CResourceManager)->Init())
		return false;


	// 카메라 초기화
	if (!GET_SINGLE(CCamera)->Init())
		return false;




	GET_SINGLE(CCamera)->SetResolution((float)iWidth, (float)iHeight);

	// 장면을 초기화한다.
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;


	// 백버퍼를 얻어온다.
	m_pBackBuffer = GET_SINGLE(CResourceManager)->FindTexture("BackBuffer");

	m_fTimeScale = 1.f;
}

int CCore::Run()
{
	MSG msg = {};

	// 기본 메시지 루프입니다.
	while (m_bLoop)
	{
		// PeekMessage : 메세지가 없을때는 FALSE를 반환하면서 바로 빠져나온다.
		// 메세지가 있을 경우 TRUE를 반환하게 된다.
		// 이 메세지를 이용하면 윈도우의 데드타임을 이용해서 게임을 제작할 수 있다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			// 실제 게임 구현부분은 여기에 들어와야 한다.
			Logic();
		}
	}

	return (int)msg.wParam;
}


void CCore::Logic()
{
	// 타이머를 업데이트 한다.
	m_pTimer->Update();

	float	fDeltaTime = m_pTimer->GetDeltaTime();

	// 입력관리자 업데이트
	GET_SINGLE(CInput)->Update(fDeltaTime);


	if (Input(fDeltaTime * m_fTimeScale) == 1)
		return;
	if (Update(fDeltaTime * m_fTimeScale) == 1)
		return;
	Collision(fDeltaTime * m_fTimeScale);
	Render(fDeltaTime * m_fTimeScale);
}

int CCore::Input(float fTime)
{
	int iRet = GET_SINGLE(CSceneManager)->Input(fTime);
	/*
		if (KEYPUSH("MoveUp"))
		{
			m_tRC.Move(0.f, -m_fRCSpeed * fTime);
		}

		if (KEYPUSH("MoveDown"))
		{
			m_tRC.Move(0.f, m_fRCSpeed * fTime);
		}

		if (KEYPUSH("MoveLeft"))
		{
			m_tRC.Move(-m_fRCSpeed * fTime, 0.f);
		}

		if (KEYPUSH("MoveRight"))
		{
			m_tRC.Move(m_fRCSpeed * fTime, 0.f);
		}

		if (KEYPUSH("Fire"))
		{
			RECTINFO	tInfo = m_tRC;

			tInfo.Move(m_tRC.GetWidth(), 0.f);

			m_BulletList.push_back(tInfo);
		}*/

	return iRet;
}

int CCore::Update(float fTime)
{
	int iRet = GET_SINGLE(CSceneManager)->Update(fTime);

	if (iRet == 1)
		return 1;

	iRet = GET_SINGLE(CSceneManager)->LateUpdate(fTime);

	// 카메라를 업데이트한다.
	GET_SINGLE(CCamera)->Update(fTime);

	//list<RECTINFO>::iterator	iter;
	//list<RECTINFO>::iterator	iterEnd = m_BulletList.end();

	//for (iter = m_BulletList.begin(); iter != iterEnd; ++iter)
	//{
	//	(*iter).Move(500.f * fTime, 0.f);
	//}

	//// 몬스터를 움직인다.
	//m_tMonsterRC.Move(0.f, 200.f * m_iMonsterDir * fTime);

	//// 몬스터가 아래나 위에 부딪혔는지 판단한다.
	//if (m_tMonsterRC.b >= m_tResolution.iHeight)
	//{
	//	m_tMonsterRC.b = m_tResolution.iHeight;
	//	m_tMonsterRC.t = m_tMonsterRC.b - 100.f;
	//	m_iMonsterDir = -1;
	//}

	//else if (m_tMonsterRC.t <= 0.f)
	//{
	//	m_tMonsterRC.b = 100.f;
	//	m_tMonsterRC.t = 0.f;
	//	m_iMonsterDir = 1;
	//}

	//// 총알을 움직인다.
	//iterEnd = m_MonsterBulletList.end();

	//for (iter = m_MonsterBulletList.begin(); iter != iterEnd; ++iter)
	//{
	//	(*iter).Move(-500.f * fTime, 0.f);
	//}

	//// 몬스터 총알 발사
	//m_fFireTime += fTime;

	//if (m_fFireTime >= 1.f)
	//{
	//	m_fFireTime -= 1.f;

	//	RECTINFO	tInfo = m_tMonsterRC;

	//	tInfo.Move(-m_tMonsterRC.GetWidth(), 0.f);

	//	m_MonsterBulletList.push_back(tInfo);
	//}

	return iRet;
}

int CCore::Collision(float fTime)
{
	return 0;
}

int CCore::Render(float fTime)
{
	// 화면크기만한 사각형을 그려서 잔상을 없애준다.
	Rectangle(m_pBackBuffer->GetDC(), 0, 0, m_pBackBuffer->GetWidth(), m_pBackBuffer->GetHeight());

	// 더블버퍼링 : 현재 화면을 구성하는 오브젝트를 백버퍼 DC에 그려주고 프레임이 끝날때 1번만
	// 화면DC에 그려준다. 이작업을 매 프레임마다 반복해서 해준다.
	GET_SINGLE(CSceneManager)->Render(m_pBackBuffer->GetDC(), fTime);

	// 마지막으로 마우스를 그려준다.
	GET_SINGLE(CInput)->RenderMouse(m_pBackBuffer->GetDC(), fTime);

	// 모든 오브젝트가 그려진 백버퍼를 화면버퍼에 그려준다.
	BitBlt(m_hDC, 0, 0, m_tResolution.iWidth, m_tResolution.iHeight,
		m_pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	/*m_tRC.Render(m_hDC);

	list<RECTINFO>::iterator	iter;
	list<RECTINFO>::iterator	iterEnd = m_BulletList.end();

	for (iter = m_BulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter).RenderEllipse(m_hDC);
	}

	m_tMonsterRC.Render(m_hDC);

	iterEnd = m_MonsterBulletList.end();

	for (iter = m_MonsterBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter).RenderEllipse(m_hDC);
	}*/

	return 0;
}


void CCore::Register(const TCHAR* pClass, int iIconID)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(iIconID));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY180629);
	wcex.lpszClassName = pClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iIconID));

	RegisterClassEx(&wcex);
}

void CCore::CreateWnd(const TCHAR* pTitle, const TCHAR* pClass)
{
	m_hWnd = CreateWindow(pClass, pTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_tResolution.iWidth, m_tResolution.iHeight,
		nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return;

	RECT		rc = { 0, 0, m_tResolution.iWidth, m_tResolution.iHeight };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static POINT	ptMousePos;
	//static list<RECT>	rcList;
	//static list<RECT>	circleList;

	switch (message)
	{
		// WM_PAINT : 윈도우창의 내용을 새로 그릴때 호출되는 메세지이다.
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// BeginPaint 함수를 이용해서 해당 윈도우에 그릴 수 있는 그리기 도구를 만들어
		// 낸다. HDC 가 화면에 그리기 위한 도구인데 여기서는 이 윈도우의 핸들(HWND)을
		// 대입해주어서 현재 윈도우에 출력할 수 있는 그리기 도구를 만들어낸다.
		HDC hdc = BeginPaint(hWnd, &ps);

		//TCHAR	strText[256] = {};

		//lstrcpy(strText, TEXT("Test Text"));

		//int		iNum = 9191;

		//// wsprintf : 문자열을 만들어주는 함수이다.
		//wsprintf(strText, TEXT("Test Text %d"), iNum);

		//// 사각형을 그려주는 함수이다.
		//Rectangle(hdc, 100, 100, 200, 200);

		//// 원을 그려주는 함수이다.
		//Ellipse(hdc, 100, 100, 200, 200);

		//// MoveToEx : 선의 시작점을 정의한다.
		//// LineTo : 선의 끝점을 정의한다.
		//MoveToEx(hdc, 300, 100, nullptr);
		//LineTo(hdc, 400, 200);
		//LineTo(hdc, 500, 200);

		//MoveToEx(hdc, 300, 400, nullptr);
		//LineTo(hdc, 350, 450);
		//LineTo(hdc, 400, 450);

		//// 문자열을 출력할때 배경을 투명으로 만들어준다.
		//SetBkMode(hdc, TRANSPARENT);
		//// SetBkColor를 이용해서 배경 컬러를 바꿔줄 수 있다.
		////SetBkColor(hdc, RGB(255, 255, 0));
		//// 문자열을 원하는 좌표에 출력한다.
		//TextOut(hdc, 100, 100, strText, lstrlen(strText));

		//for (int i = 0; i < 100; ++i)
		//{
		//	SetPixel(hdc, 100 + i, 300, RGB(255, 0, 0));
		//}

		//TCHAR	strMousePos[256] = {};
		//wsprintf(strMousePos, TEXT("x : %d y : %d"), ptMousePos.x, ptMousePos.y);

		//TextOut(hdc, 600, 50, strMousePos, lstrlen(strMousePos));

		//list<RECT>::iterator	iter;
		//list<RECT>::iterator	iterEnd = rcList.end();

		//for (iter = rcList.begin(); iter != iterEnd; ++iter)
		//{
		//	Rectangle(hdc, (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
		//}

		//iterEnd = circleList.end();
		//for (iter = circleList.begin(); iter != iterEnd; ++iter)
		//{
		//	Ellipse(hdc, (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
		//}


		//Rectangle(hdc, ptMousePos.x - 30, ptMousePos.y - 30,
		//	ptMousePos.x + 30, ptMousePos.y + 30);

		// EndPaint를 이용해서 그리기를 종료한다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		GET_SINGLE(CCore)->ResizeWindow();
		break;
		// WM_KEYDOWN : 키를 누를때 들어온다.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
		// WM_KEYUP : 누르고 있던 키가 올라갈때 들어온다.
	//case WM_KEYUP:
	//	break;
	//	// WM_CHAR : 문자키를 누를때 들어오는 메세지다.
	//case WM_CHAR:
	//	switch (wParam)
	//	{
	//	case 'A':
	//		MessageBox(nullptr, TEXT("A Push"), TEXT("Key Push"), MB_OK);
	//		break;
	//	}
	//	break;
	//	// 왼쪽버튼 클릭 메세지.
	//case WM_LBUTTONDOWN:
	//{
	//	ptMousePos.x = LOWORD(lParam);
	//	ptMousePos.y = HIWORD(lParam);
	//	RECT	rc = { ptMousePos.x - 30, ptMousePos.y - 30, ptMousePos.x + 30,
	//		ptMousePos.y + 30 };

	//	rcList.push_back(rc);
	//	InvalidateRect(hWnd, nullptr, TRUE);
	//}
	//break;
	//// 왼쪽버튼을 클릭 후 버튼이 올라갈때 메세지.
	//case WM_LBUTTONUP:
	//	break;
	//	// 위의 3개 외에도 RButton, MButton이 있다.
	//case WM_RBUTTONDOWN:
	//	if (!rcList.empty())
	//	{
	//		rcList.pop_back();
	//		InvalidateRect(hWnd, nullptr, TRUE);
	//	}
	//	break;
	//case WM_MBUTTONDOWN:
	//{
	//	ptMousePos.x = LOWORD(lParam);
	//	ptMousePos.y = HIWORD(lParam);
	//	RECT	rc = { ptMousePos.x - 30, ptMousePos.y - 30, ptMousePos.x + 30,
	//		ptMousePos.y + 30 };

	//	circleList.push_back(rc);
	//	InvalidateRect(hWnd, nullptr, TRUE);
	//}
	//	break;

	//	// 마우스 휠을 굴릴때 들어오는 메세지.
	//case WM_MOUSEWHEEL:
	//	break;
	//	// 마우스를 움직일때 들어오는 메세지.
	//case WM_MOUSEMOVE:
	//	ptMousePos.x = LOWORD(lParam);
	//	ptMousePos.y = HIWORD(lParam);

	//	// 1번인자 : 대상 윈도우 핸들
	//	// 2번인자 : 대상 윈도우에서의 다시 그릴 영역(nullptr : 전체영역)
	//	// 3번인자 : TRUE -> 화면을 모두 지우고 다시 그린다. FALSE -> 안지우고 덮어서 그린다.
	//	InvalidateRect(hWnd, nullptr, TRUE);
	//	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}