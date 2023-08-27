#pragma once

class BoundShape : public Component
{
protected:
	D2D1::ColorF m_DrawColor{ 1, 1, 1 };

	bool		m_IsCollision = false;

public:
	/// <summary>
	/// 화면에 도형을 출력한다
	/// </summary>
	/// <param name="m_pEngine">출력할 엔진</param>
	virtual void	OnRender() {};

	/// <summary>
	/// 색깔을 설정한다.
	/// </summary>
	/// <param name="color">설정할 색깔값</param>
	void			SetColor(ColorF color) { m_DrawColor = color; }

	/// <summary>
	/// 색깔을 설정한다.
	/// </summary>
	void			SetColor(float r, float g, float b, float a = 1.0f) { SetColor(ColorF(r, g, b, a)); }

	/// <summary>
	/// 색깔값을 받아온다
	/// </summary>
	ColorF			GetColor() { return m_DrawColor; }
};

