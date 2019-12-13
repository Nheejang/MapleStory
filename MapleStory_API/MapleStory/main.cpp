#include"Core.h"
#include"resource.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	if (!GET_SINGLE(CCore)->Init(hInstance, 1280, 720, TEXT("MapleStory"),
		TEXT("MapleStory"),
		IDI_ICON1))
	{
		DESTROY_SINGLE(CCore);
		return 0;
	}

	int iRet = GET_SINGLE(CCore)->Run();

	DESTROY_SINGLE(CCore);

	return iRet;
}