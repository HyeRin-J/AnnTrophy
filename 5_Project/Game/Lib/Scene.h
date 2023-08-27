#pragma once

class Scene
{
public:
	MapData			m_Data;
	std::wstring	m_Name;
	std::wstring	m_BackGroundPath;
	std::wstring	m_TileMapPath;

	float			m_ChangeBackgroundTime = 0.6f;

	int m_BackgroundIndex = 0;
	std::vector<ID2D1Bitmap*>	m_BackGroundBitmap = { nullptr, nullptr };
	ID2D1Bitmap*	m_TileBitmap;

	float	m_LoadTime = 2.0f;
	bool	m_IsLoadFinish = true;
	bool	m_ChangeState = false;
	bool	m_ChangeFinish = false;

	Scene(std::wstring newName, std::wstring tileName);
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void PostRender();
	virtual void Release();
	void	ChangeState();
};

