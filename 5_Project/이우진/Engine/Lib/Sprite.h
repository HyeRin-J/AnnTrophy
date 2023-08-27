#pragma once

#include "Vector2.h"
#include "SpriteData.h"


class Sprite : public Component
{
public:
	D2D1_POINT_2F m_OriginPos = { 0,0 };

	int m_SheetIndex;

	//현재 스프라이트를 움직이는지의 여부
	ID2D1Bitmap* m_BitMap;
	std::vector<SpriteData> m_SpriteSheets;

	bool m_IsPlay  = true;

	void LoadSprite(PCWSTR _path,float _width,float _height);
	void SetPosition(Vector2 _pos);
	void SetPosition(float _x , float _y);

	void StartSprite() { m_IsPlay = true; }
	void StopSprite() { m_IsPlay = false; }

	virtual void	ToString();
	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	Update(float _dtime);
	virtual void	FixedUpdate() {};
	virtual void	OnRender() {};
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};

};

