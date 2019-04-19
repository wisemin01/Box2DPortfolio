#include "DXUT.h"
#include "CObjManager.h"

#include "CObject.h"

CObjManager::CObjManager() {
	m_pCollision = new CCollisionAdmin;
}


CObjManager::~CObjManager()
{
	ResetAllList();
	SAFE_DELETE(m_pCollision);
}

CObject * CObjManager::Insert(OBJ_LIST _eType, CObject * _pObj)
{
	if (!_pObj)
	{
		MESSAGE_LOG("CObjManager::Insert() - ºó ¿ÀºêÁ§Æ® »ðÀÔ");
		return nullptr;
	}

	_pObj->Init();

	if (_eType == OBJ_LIST::UI)
		m_vecUiObjs.push_back(_pObj);
	else
		m_vecObjs[_eType].push_back(_pObj);

	return _pObj;
}

CObject * CObjManager::FindObjectWithTag(const string & _sTag)
{
	for (auto iter : m_vecObjs)
	{
		for (auto _iter : iter)
		{
			if (_iter->GetInfo()->sTag == _sTag)
				return _iter;
		}
	}
	for (auto iter : m_vecUiObjs)
	{
		if (iter->GetInfo()->sTag == _sTag)
			return iter;
	}

	return nullptr;
}

void CObjManager::ResetList(OBJ_LIST _eType)
{
	if (_eType == OBJ_LIST::END) return;

	if (_eType == OBJ_LIST::UI) {
		for (auto iter : m_vecUiObjs)
		{
			iter->Destroy();
			SAFE_DELETE(iter);
		}
	
		m_vecUiObjs.clear();
		return;
	}

	for (auto iter : m_vecObjs[_eType])
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}

	m_vecObjs[_eType].clear();
	return;
}

void CObjManager::ResetAllList(bool _bIsLast)
{
	for (int i = 0; i < OBJ_LIST::END; i++)
	{
		ResetList((OBJ_LIST)i);
	}
	ResetList(OBJ_LIST::UI);
}

void CObjManager::UpdateObjects()
{
	for (int i = 0; i < OBJ_LIST::END; i++)
	{
		std::vector<CObject*>& vecRef = m_vecObjs[i];

		for (auto iter = vecRef.begin(); iter != vecRef.end();)
		{
			CObject* pObj = *iter;
			bool deleteTag = pObj->GetIsDeleted();
			if (!deleteTag)
			{
				pObj->Update();
				iter++;
			}
			else
			{
				pObj->Destroy();
				SAFE_DELETE(pObj);
				iter = vecRef.erase(iter);
			}
		}
	}
	for (auto iter = m_vecUiObjs.begin(); iter != m_vecUiObjs.end();)
	{
		CObject* pObj = *iter;
		bool deleteTag = pObj->GetIsDeleted();
		if (!deleteTag)
		{
			pObj->Update();
			iter++;
		}
		else
		{
			pObj->Destroy();
			SAFE_DELETE(pObj);
			iter = m_vecUiObjs.erase(iter);
		}
	}

	m_pCollision->UpdatingColliders();
}

void CObjManager::RenderObjects()
{
	IMAGEMANAGER->ReBegin(false);
	for (auto &iter : m_vecObjs)
	{
		for (auto &_iter : iter)
		{
			if (_iter && _iter->GetVisible() && !_iter->GetIsDeleted())
				_iter->Render();
		}
	}

	IMAGEMANAGER->ReBegin(true);
	for (auto iter : m_vecUiObjs)
	{
		if (iter && iter->GetVisible() && !iter->GetIsDeleted())
			iter->Render();
	}

	IMAGEMANAGER->ReBegin(false);
}

void CObjManager::RegisterCollider(CObject * _pBase)
{
	m_pCollision->InsertCollider(_pBase->GetCollider());
}

void CObjManager::UnRegisterCollider(CObject * _pBase)
{
	m_pCollision->DeleteCollider(_pBase->GetCollider());
}

void CObjManager::CCollisionAdmin::InsertCollider(CCollider * collider)
{
	m_listColliders.push_back(collider);
}

void CObjManager::CCollisionAdmin::DeleteCollider(CCollider * collider)
{
	m_listColliders.remove(collider);
}

void CObjManager::CCollisionAdmin::UpdatingColliders()
{

	for (auto col1 : m_listColliders)
	{
		for (auto col2 : m_listColliders)
		{
			if (col1 == col2)
				continue;

			if (CCollider::Inspection(col1, col2))
			{
				col1->GetOwner()->OnCollision(col2);
			}
		}
	}
}
