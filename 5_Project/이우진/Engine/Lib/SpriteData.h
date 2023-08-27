#pragma once

//메인플머 혜린좌의 자료저장 방식
//스프라이트 시트를 저장할 데이터구조
//json파일형식으로 저장할것이다

struct SpriteData
{
	//고정 피벗
	D2D1_POINT_2F m_Pivot = { 0,0 };
	//보여줄 비트맵의 움직임 위치
	D2D1_POINT_2F m_BitmapPos = { 0,0 };
	//보여줄 사이즈
	D2D1_SIZE_F m_BitmapSize = { 0,0 };

	//충돌영역같은데 .. 콜라이더를 쓰면되지않을까라고
	//생각은 했지만 한장의 이미지 파일안의 추가 바운더리
	//박스를 더 넣는다. 충돌박스가 하나만있지는 않을것이기 때문에..
	D2D1_RECT_F m_Boundary = { 0,0,0,0 };
	//프레임 딜레이를 나타내주는 멤버변수
	float m_delay;

};