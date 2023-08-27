#pragma once

class SpriteData
{
public:
	D2D_POINT_2F	m_BitmapPos = { 0, 0 };
	D2D_SIZE_F		m_BitmapSize = { 100, 100 };
	D2D_POINT_2F	m_Pivot = { 0, 0 };
	D2D_RECT_F		m_Boundary = { 0, 0, 0, 0 };

	float			delay = 0;
};

