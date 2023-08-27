#pragma once

class Component;

class Transform : public Component
{
public:
	D2D1_POINT_2F m_Position = { 0, 0 };
	double m_Rotate = 0;
	D2D1_SIZE_F m_Scale = { 1, 1 };

	Transform();

	virtual void	Update();

	void			SetPosition(D2D1_POINT_2F pos) { m_Position = pos; }
	void			SetPosition(double x, double y) { SetPosition(D2D1::Point2F(x, y)); }
	D2D1_POINT_2F	GetPosition() { return m_Position; }

	void		SetRotation(double x) { m_Rotate = x; }
	double		GetRotation() { return m_Rotate; }

	void		SetScale(D2D1_SIZE_F scale) { m_Scale = scale; }
	void		SetScale(double x, double y) { SetScale(D2D1::SizeF(x, y)); }
	D2D1_SIZE_F GetScale() { return m_Scale; }

	void		Translate(Vector2 vec);
	void		Rotate(float angle);
};
