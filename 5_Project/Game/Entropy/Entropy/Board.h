#pragma once
class Board : public Component
{
public:
	//���带 �׷��� ��Ʈ��
	ID2D1Bitmap* m_pBitmap;
	//

public:

	virtual void	Awake();
	virtual void	FixedUpdate();
	virtual void	OnRender();
};

