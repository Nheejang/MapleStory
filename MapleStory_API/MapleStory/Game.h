#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WS2tcpip.h>
#include<Windows.h>
#include<list>
#include<vector>
#include<unordered_map>
#include<crtdbg.h>
#include<string>
#include<typeinfo>
#include<math.h>
#include<functional>
#include<conio.h>

#include<thread>

using namespace std;

#include"Macro.h"
#include"Type.h"
#include"Protocol.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"msimg32.lib")

#define WM_SOCKET WM_USER+1

#ifdef UNICODE
typedef wstring MyString;
#else
typedef string MyString;
#endif //UNICODE

#define ROOT_PATH "RootPath"
#define TEXTURE_PATH "TexturePath"
#define DATA_PATH "DataPath"
#define SOUND_PATH "SoundPath"

template<typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	p.clear();
}

template<typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	
	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	
	p.clear();
}

template<typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	p.clear();
}

template<typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
	
	p.clear();
}