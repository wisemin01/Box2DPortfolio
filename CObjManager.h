#pragma once
#include "CSingleton.h"

class CObject;
class CObjManager final:
	public CSingleton<CObjManager>
{
public:
	// CObjManager::OBJ_LIST 로 접근
	enum OBJ_LIST
	{
		TILE,
		PLAYER,
		ENEMY,
		EFFECT,
		END,

		// UI는 렌더할때 D3DXSPRITE_OBJECTSPACE 를 켜지 않고 렌더해야
		// 화면에 고정되게 렌더된다.
		UI
	};

private:
	
	class CCollisionAdmin;

	vector<CObject*> m_vecObjs[OBJ_LIST::END];
	vector<CObject*> m_vecUiObjs;

	CCollisionAdmin* m_pCollision;

public:
	CObjManager();
	virtual ~CObjManager();

	CObject* Insert(OBJ_LIST _eType, CObject* _pObj);
	CObject* FindObjectWithTag(const string& _sTag);

	void ResetList(OBJ_LIST _eType);
	void ResetAllList(bool _bIsLast = false);

	void UpdateObjects();
	void RenderObjects();

	void RegisterCollider(CObject* _pBase);
	void UnRegisterCollider(CObject* _pBase);

private:

	class CCollisionAdmin
	{
	private:
		std::list<CCollider*> m_listColliders;

	public:

		CCollisionAdmin() {}
		~CCollisionAdmin() { m_listColliders.clear(); }

		void InsertCollider(CCollider* collider);
		void DeleteCollider(CCollider* collider);

		void UpdatingColliders();
	};

};

#define OBJMANAGER CObjManager::GetInst()