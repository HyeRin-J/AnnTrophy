#pragma once

#include "Vector.h"
#include "SpriteData.h"


class Sprite : public Component
{
public:
	ID2D1Bitmap* m_BitMap;
	std::vector<SpriteData> m_SpriteSheets;
	PCWSTR m_DataPath;

	int		m_SheetIndex = 0;
	bool	m_IsPlaying  = true;	//���� ��������Ʈ�� �����̴� ������
	bool	m_IsInversePlay  = false;	//���� ��������Ʈ�� �����̴����� ����
	float	startTime = 0.f;
	float	currTime = 0.f;
	bool	m_IsFinish = false;
	bool	m_IsPlayOnce = false;

	Sprite() {};
	Sprite(PCWSTR _path) { m_DataPath = _path; };
	void LoadSprite(PCWSTR _path, PCWSTR _folder = _T(""));
	void LoadSprite(PCWSTR _dataName, PCWSTR _imageName, PCWSTR _folder = _T(""));
	void StartAnimation() { m_IsPlaying = true; }
	void StopAnimation();
	void DrawOpenSprite(std::wstring _fileName);

	virtual void Awake();
	virtual void OnRender();
	//virtual void Update(float _dtime = 100.f);
};

