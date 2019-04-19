#pragma once

class CObject abstract
{
public:
	enum OBJ_STATE
	{
		IDLE,
		WALK,
		ATTACK,
		DEATH
	};
protected:
	INFO m_tInfo;

	CTexture *m_pTexture;
	CFrame    m_tFrame;
	CCollider m_tCollider;

	int m_eState	  = IDLE;
	int m_iFlip		  = 1;
	
	bool m_bDeleteTag = false;
	bool m_bVisible   = true;

public:

	CObject() : m_tCollider(this) {}
	CObject(const INFO& _tInfo) : m_tInfo(_tInfo), m_tCollider(this) {}
	virtual ~CObject() {}

	inline INFO* GetInfo() { return &m_tInfo; }
	inline CCollider* GetCollider() { return &m_tCollider; }

	virtual void Init	() PURE;
	virtual void Update	() PURE;
	virtual void Render	() PURE;
	virtual void Destroy() PURE;

	virtual void OnCollision(CCollider* _tCol) {}

public:
	// GET_SET_ACCESSOR

	inline void SetVisible(bool _bFlag)					{ m_bVisible = _bFlag;   }
	inline bool GetVisible()							{ return m_bVisible;     }

	inline void SetDelete(bool _bFlag = true)			{ m_bDeleteTag = _bFlag; }
	inline bool GetIsDeleted()							{ return m_bDeleteTag;   }

	inline void SetState(int _iState)					{ m_eState = _iState;	 }
	inline int  GetState()								{ return m_eState;		 }

	inline void SetFlip(int _iFlip)						{ m_iFlip = _iFlip;		 }
	inline int  GetFlip()								{ return m_iFlip;		 }
};

