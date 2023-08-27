#pragma once
class FText //: public Component
{
public:
	//그려줄 텍스트
	D2D1::ColorF::Enum m_TxtColor;
	
	D2D1_POINT_2F		m_TxTBoxPos;
	D2D1_SIZE_F			m_TxTBoxSize;
	const WCHAR* m_wText;//출력 할 메세지
	const WCHAR* m_wFont;//출력 할 폰트설정

	bool m_IsCheck = false;
	bool m_FontDraw;
public:
	void SetText(const WCHAR* _msg);
	void SetTextDraw(float _posX, float _posY, const WCHAR* _Font,const WCHAR* _msg, D2D1::ColorF::Enum _TxtColor);
public:
	//virtual void	OnRender();
	void	OnRender();
};

