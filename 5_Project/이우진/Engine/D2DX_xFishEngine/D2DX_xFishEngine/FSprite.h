#pragma once
class D2DGrahpics;

#include <vector>

using namespace std;
class FSprite
{
public:
	FSprite();
	~FSprite();
public:
	
	// ������ Ư�� �ε���(Ű)
	int Index;

	int m_frm;//���� �׷��� ������
	int DelayFrame;		// �ִϸ��̼� ���� ������(������)
	int m_Length;//�׷��� �̹��� ����
	//��Ʈ��//
	//��� ������ ������ ����Ʈ�� ���͸� �Ẹ��..
	vector<FSprite/*bitmap*/> m_Mostion;
public:
	//��Ʈ�� ��ǥ,������
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
public:
	void Sprite_Info();
};

