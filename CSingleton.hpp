#include "CSingleton.h"

template<class Manager>
inline Manager * CSingleton<Manager>::GetInst()
{
	if (!Inst)
		Inst = new Manager;
	return Inst;
}

template<class Manager>
inline void CSingleton<Manager>::DestroyInst()
{
	if (Inst)
	{
		delete Inst;
		Inst = nullptr;
	}
}