#pragma once
class Board : public Component
{
public:
	//보드를 그려줄 비트맵
	ID2D1Bitmap* m_pBitmap;
	//

public:

	virtual void	Awake();
	virtual void	FixedUpdate();
	virtual void	OnRender();
};

