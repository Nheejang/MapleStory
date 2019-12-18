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
	//�ܼ�â �����Լ�
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

	//���� ������ �����쿡 ����� DC�� ������ش�.
	m_hDC = GetDC(m_hWnd);
	
	//Ÿ�̸Ӹ� �����Ѵ�.
	m_pTimer = new CTimer;

	if (!m_pTimer->Init())
	{
		SAFE_DELETE(m_pTimer);
		return false;
	}

	// ��ΰ����� �ʱ�ȭ
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// �Է°����� �ʱ�ȭ
	if (!GET_SINGLE(CInput)->Init())
		return false;

	// ���ҽ� ������ �ʱ�ȭ
	if (!GET_SINGLE(CResourceManager)->Init())
		return false;


	// ī�޶� �ʱ�ȭ
	if (!GET_SINGLE(CCamera)->Init())
		return false;




	GET_SINGLE(CCamera)->SetResolution((float)iWidth, (float)iHeight);

	// ����� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;


	// ����۸� ���´�.
	m_pBackBuffer = GET_SINGLE(CResourceManager)->FindTexture("BackBuffer");

	m_fTimeScale = 1.f;
}

int CCore::Run()
{
	MSG msg = {};

	// �⺻ �޽��� �����Դϴ�.
	while (m_bLoop)
	{
		// PeekMessage : �޼����� �������� FALSE�� ��ȯ�ϸ鼭 �ٷ� �������´�.
		// �޼����� ���� ��� TRUE�� ��ȯ�ϰ� �ȴ�.
		// �� �޼����� �̿��ϸ� �������� ����Ÿ���� �̿��ؼ� ������ ������ �� �ִ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			// ���� ���� �����κ��� ���⿡ ���;� �Ѵ�.
			Logic();
		}
	}

	return (int)msg.wParam;
}


void CCore::Logic()
{
	// Ÿ�̸Ӹ� ������Ʈ �Ѵ�.
	m_pTimer->Update();

	float	fDeltaTime = m_pTimer->GetDeltaTime();

	// �Է°����� ������Ʈ
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

	// ī�޶� ������Ʈ�Ѵ�.
	GET_SINGLE(CCamera)->Update(fTime);

	//list<RECTINFO>::iterator	iter;
	//list<RECTINFO>::iterator	iterEnd = m_BulletList.end();

	//for (iter = m_BulletList.begin(); iter != iterEnd; ++iter)
	//{
	//	(*iter).Move(500.f * fTime, 0.f);
	//}

	//// ���͸� �����δ�.
	//m_tMonsterRC.Move(0.f, 200.f * m_iMonsterDir * fTime);

	//// ���Ͱ� �Ʒ��� ���� �ε������� �Ǵ��Ѵ�.
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

	//// �Ѿ��� �����δ�.
	//iterEnd = m_MonsterBulletList.end();

	//for (iter = m_MonsterBulletList.begin(); iter != iterEnd; ++iter)
	//{
	//	(*iter).Move(-500.f * fTime, 0.f);
	//}

	//// ���� �Ѿ� �߻�
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
	// ȭ��ũ�⸸�� �簢���� �׷��� �ܻ��� �����ش�.
	Rectangle(m_pBackBuffer->GetDC(), 0, 0, m_pBackBuffer->GetWidth(), m_pBackBuffer->GetHeight());

	// ������۸� : ���� ȭ���� �����ϴ� ������Ʈ�� ����� DC�� �׷��ְ� �������� ������ 1����
	// ȭ��DC�� �׷��ش�. ���۾��� �� �����Ӹ��� �ݺ��ؼ� ���ش�.
	GET_SINGLE(CSceneManager)->Render(m_pBackBuffer->GetDC(), fTime);

	// ���������� ���콺�� �׷��ش�.
	GET_SINGLE(CInput)->RenderMouse(m_pBackBuffer->GetDC(), fTime);

	// ��� ������Ʈ�� �׷��� ����۸� ȭ����ۿ� �׷��ش�.
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
		// WM_PAINT : ������â�� ������ ���� �׸��� ȣ��Ǵ� �޼����̴�.
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// BeginPaint �Լ��� �̿��ؼ� �ش� �����쿡 �׸� �� �ִ� �׸��� ������ �����
		// ����. HDC �� ȭ�鿡 �׸��� ���� �����ε� ���⼭�� �� �������� �ڵ�(HWND)��
		// �������־ ���� �����쿡 ����� �� �ִ� �׸��� ������ ������.
		HDC hdc = BeginPaint(hWnd, &ps);

		//TCHAR	strText[256] = {};

		//lstrcpy(strText, TEXT("Test Text"));

		//int		iNum = 9191;

		//// wsprintf : ���ڿ��� ������ִ� �Լ��̴�.
		//wsprintf(strText, TEXT("Test Text %d"), iNum);

		//// �簢���� �׷��ִ� �Լ��̴�.
		//Rectangle(hdc, 100, 100, 200, 200);

		//// ���� �׷��ִ� �Լ��̴�.
		//Ellipse(hdc, 100, 100, 200, 200);

		//// MoveToEx : ���� �������� �����Ѵ�.
		//// LineTo : ���� ������ �����Ѵ�.
		//MoveToEx(hdc, 300, 100, nullptr);
		//LineTo(hdc, 400, 200);
		//LineTo(hdc, 500, 200);

		//MoveToEx(hdc, 300, 400, nullptr);
		//LineTo(hdc, 350, 450);
		//LineTo(hdc, 400, 450);

		//// ���ڿ��� ����Ҷ� ����� �������� ������ش�.
		//SetBkMode(hdc, TRANSPARENT);
		//// SetBkColor�� �̿��ؼ� ��� �÷��� �ٲ��� �� �ִ�.
		////SetBkColor(hdc, RGB(255, 255, 0));
		//// ���ڿ��� ���ϴ� ��ǥ�� ����Ѵ�.
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

		// EndPaint�� �̿��ؼ� �׸��⸦ �����Ѵ�.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		GET_SINGLE(CCore)->ResizeWindow();
		break;
		// WM_KEYDOWN : Ű�� ������ ���´�.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
		// WM_KEYUP : ������ �ִ� Ű�� �ö󰥶� ���´�.
	//case WM_KEYUP:
	//	break;
	//	// WM_CHAR : ����Ű�� ������ ������ �޼�����.
	//case WM_CHAR:
	//	switch (wParam)
	//	{
	//	case 'A':
	//		MessageBox(nullptr, TEXT("A Push"), TEXT("Key Push"), MB_OK);
	//		break;
	//	}
	//	break;
	//	// ���ʹ�ư Ŭ�� �޼���.
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
	//// ���ʹ�ư�� Ŭ�� �� ��ư�� �ö󰥶� �޼���.
	//case WM_LBUTTONUP:
	//	break;
	//	// ���� 3�� �ܿ��� RButton, MButton�� �ִ�.
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

	//	// ���콺 ���� ������ ������ �޼���.
	//case WM_MOUSEWHEEL:
	//	break;
	//	// ���콺�� �����϶� ������ �޼���.
	//case WM_MOUSEMOVE:
	//	ptMousePos.x = LOWORD(lParam);
	//	ptMousePos.y = HIWORD(lParam);

	//	// 1������ : ��� ������ �ڵ�
	//	// 2������ : ��� �����쿡���� �ٽ� �׸� ����(nullptr : ��ü����)
	//	// 3������ : TRUE -> ȭ���� ��� ����� �ٽ� �׸���. FALSE -> ������� ��� �׸���.
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