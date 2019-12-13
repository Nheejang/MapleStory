
#include"Ref.h"


CRef::CRef():
	m_iRefCount(1),
	m_bEnable(true),
	m_bActive(true)
{
}

CRef::~CRef()
{

}
