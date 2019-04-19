#pragma once

template <class Manager>
class CSingleton
{
private:
	static Manager* Inst;
public:

	CSingleton() {}
	virtual ~CSingleton() {}

	static Manager* GetInst();
	static void DestroyInst();
};

template <class Manager>
Manager* CSingleton<Manager>::Inst = nullptr;

#include "CSingleton.hpp"
