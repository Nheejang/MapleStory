#include"Debug.h"
#include"Core.h"

void CDebug::OutputConsole(const char* pText)
{
#ifdef _DEBUG
	_cprintf(pText);
#endif
}

void CDebug::OutputVisual(const char* pText)
{
	OutputDebugStringA(pText);
}

void CDebug::OutputTitle(const char* pTitle)
{
	SetWindowTextA(WINDOWHANDLE, pTitle);
}