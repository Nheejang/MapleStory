#pragma once

#define SAFE_DELETE(p) if(p) {delete p; p=nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p=nullptr;}
#define SAFE_RELEASE(p) if(p) {p->Release(); p=nullptr;}

#define DECLARE_SINGLE(Type) \
	private:\
		static Type* m_pInst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_pInst)\
				m_pInst = new Type;\
			return m_pInst;\
		}\
		static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
	private:\
		Type();\
		~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst=nullptr;
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()

#define _RESOLUTION GET_SINGLE(CCore)->GetResolution()
#define WINDOWINSTANCE GET_SINGLE(CCore)->GetWindowInstance()
#define WINDOWHANDLE GET_SINGLE(CCore)->GetWindowHandle()
#define WINDOWDC GET_SINGLE(CCore)->GetWindowDC()

#define KEYPRESS(key)	GET_SINGLE(CInput)->KeyPress(key)
#define KEYUP(key)		GET_SINGLE(CInput)->KeyUp(Key)
#define KEYPUSH(key)	GET_SINGLE(CInput)->KeyPush(key)

#define MOUSECLIENTPOS GET_SINGLE(CInput)->GetMouseCluent()
#define MOUSEWORLDPOS GET_SINGLE(CInput)->GetMouseWorld()
#define MOUSEGAP GET_SINGLE(CInput)->GetMouseGap()
#define CAMERAPOS GET_SINGLE(CCamera)->GetPos()
#define CAMERARESOLUTION GET_SINGLE(CCamera)->GetResolution()
