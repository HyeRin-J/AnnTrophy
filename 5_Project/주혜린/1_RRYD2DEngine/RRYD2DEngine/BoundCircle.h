#pragma once

class BoundCircle : public BoundShape
{
private:
	double m_Radius = 25;

public:
	virtual void	OnRender();
	virtual void	Update();

	bool			IsCheckCollision(BoundCircle* c);

	void			SetRadius(double r) { m_Radius = r; }
	double			GetRadius() { return m_Radius * m_GameObject->m_Transform->m_Scale.width; }
};

