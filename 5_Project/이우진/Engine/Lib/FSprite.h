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
	
	// 연결할 특정 인덱스(키)
	int Index;

	int m_frm;//현재 그려질 프레임
	int DelayFrame;		// 애니메이션 내의 딜레이(프레임)
	int m_Length;//그려줄 이미지 개수
	//비트맵//
	//모션 저장을 저장할 리스트나 벡터를 써보자..
	vector<FSprite/*bitmap*/> m_Mostion;
public:
	//비트맵 좌표,사이즈
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
public:
	void Sprite_Info();
};

