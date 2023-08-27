#pragma once

class BoundShape : public Component
{
protected:
	D2D1::ColorF m_DrawColor{ 1, 1, 1 };

	bool		m_IsCollision = false;

public:
	/// <summary>
	/// ȭ�鿡 ������ ����Ѵ�
	/// </summary>
	/// <param name="m_pEngine">����� ����</param>
	virtual void	OnRender() {};

	/// <summary>
	/// ������ �����Ѵ�.
	/// </summary>
	/// <param name="color">������ ����</param>
	void			SetColor(ColorF color) { m_DrawColor = color; }

	/// <summary>
	/// ������ �����Ѵ�.
	/// </summary>
	void			SetColor(float r, float g, float b, float a = 1.0f) { SetColor(ColorF(r, g, b, a)); }

	/// <summary>
	/// ������ �޾ƿ´�
	/// </summary>
	ColorF			GetColor() { return m_DrawColor; }
};

