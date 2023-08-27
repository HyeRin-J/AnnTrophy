#pragma once
class FText : public Component
{
public:
	//그려줄 텍스트
	std::wstring m_Text;
	D2D1::ColorF::Enum m_TxtColor;
	
	D2D1_POINT_2F		m_TxTBoxPos;
	D2D1_SIZE_F			m_TxTBoxSize;
	const WCHAR* m_wText;
	bool m_TxtDraw = false;
	float m_FontSize;
public:
	void SetText(const WCHAR* _msg);
	void SetTestDraw(float _x, float _y, float _width, float _height, float _size, const WCHAR* _msg);
public:
	virtual void	Awake();
	virtual void	Update();
	virtual void	OnRender();

};

