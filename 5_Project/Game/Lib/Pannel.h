#pragma once
class Pannel //: public Component
{
public:
	enum class Shape
	{
		_RECT,
		_CIRCLE,
	};
private:
	//그려줄 비트맵
	ID2D1Bitmap* m_pBitmap;
	D2D1::ColorF::Enum m_BitColor;
	D2D1_POINT_2F		m_Center;
	D2D1_POINT_2F		m_Pos;
	D2D1_RECT_F		m_BOX;
	const WCHAR* m_wText;

	bool m_BitDraw = false;
public:
	//클릭됬을때 체크용
	bool m_IsCheck;
public:
	void SetLoadBitmap(std::wstring& _bitmapName);
	void SetBitmapDraw(bool _v) { m_BitDraw = _v; }
	
	void SetPoint(D2D1_POINT_2F _pos, D2D1_SIZE_F _center);
	D2D1_POINT_2F GetCenter() { return m_Center;}
	ID2D1Bitmap* GetBitmap() { return m_pBitmap;}

	void GetCuserPosDraw(float _x, float _y, float _width, float _height);
public:
	//virtual void	OnRender();
	void	OnRender();
};

