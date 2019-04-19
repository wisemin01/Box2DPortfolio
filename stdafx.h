#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>

using namespace std;


#define WINSIZEX 1920
#define WINSIZEY 1080

#define GetNowTime() timeGetTime()

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;

typedef std::string String;
typedef D3DCOLOR	Color;

typedef struct tagInfo {

	Vector3 vPos;
	Vector3 vScale;
	string  sTag;
	Color	tColor;

	const Vector2& GetPosV2() { return Vector2(vPos); }
	const Vector2& GetScaleV2() { return Vector2(vScale); }

} INFO;


extern float g_fDeltaTime;
const Vector2 v2Center = Vector2(WINSIZEX / 2, WINSIZEY / 2);
const Vector3 v3Center = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0);

#include "CFrame.h"
#include "CCollider.h"
#include "Cauculate.h"

#if defined(DEBUG) | defined(_DEBUG)
#define CONSOLE_LOG(log) std::cout << log << std::endl
#define MESSAGE_LOG(log) MessageBoxA(DXUTGetHWND(), log, "[ MESSAGE LOG ]", MB_OK);
#else
#define CONSOLE_LOG(log)  
#define MESSAGE_LOG(log)  
#endif

// 매니저 추가
#include "CSceneManager.h"
#include "CImageManager.h"
#include "CInputManager.h"
#include "CObjManager.h"
#include "CCameraManager.h"