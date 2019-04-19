#pragma once
#include "CScene.h"
class CLoadingScene final:
	public CScene
{
public:
	struct strBun
	{
		string key;
		string path;
		int count;
		strBun(const string& _key, const string& _path, int _count)
			: key(_key), path(_path), count(_count) {}
	};
private:
	vector<strBun> m_vecTexPaths;

	int m_iNowLoading;
	int m_iLastLoading;
public:
	CLoadingScene();
	virtual ~CLoadingScene();

	virtual void Init	() override;
	virtual void Update	() override;
	virtual void Render	() override;
	virtual void Destroy() override;

	inline void Load(const string& key, const string& path, int count = 0)
	{
		m_vecTexPaths.push_back(strBun(key, path, count));
	}
};

