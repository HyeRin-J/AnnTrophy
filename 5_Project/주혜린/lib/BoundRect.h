#pragma once

class BoundRect : public BoundShape
{
private:
	D2D1_POINT_2F m_Corner[4] = 
	{	D2D1::Point2F(m_GameObject->m_Transform->m_Position.x - m_GameObject->m_Transform->m_Scale.width / 2, 
m_GameObject->m_Transform->m_Position.y - m_GameObject->m_Transform->m_Scale.height / 2),
		D2D1::Point2F(m_GameObject->m_Transform->m_Position.x + m_GameObject->m_Transform->m_Scale.width / 2, 
m_GameObject->m_Transform->m_Position.y - m_GameObject->m_Transform->m_Scale.height / 2),
		D2D1::Point2F(m_GameObject->m_Transform->m_Position.x - m_GameObject->m_Transform->m_Scale.width / 2, 
m_GameObject->m_Transform->m_Position.y + m_GameObject->m_Transform->m_Scale.height / 2),
		D2D1::Point2F(m_GameObject->m_Transform->m_Position.x + m_GameObject->m_Transform->m_Scale.width / 2, 
			m_GameObject->m_Transform->m_Position.y + m_GameObject->m_Transform->m_Scale.height / 2)
	};
	D2D1_POINT_2F m_IdentityCorner[4];

public:
	virtual void	OnRender();
	virtual void	Update();

	virtual void	SetCenter(int x, int y) { m_GameObject->m_Transform->SetPosition(x, y); SetCorner(); }

	bool			IsCheckAABBCollision(BoundRect r);
	bool			IsCheckOBBCollision(BoundRect r);

	void			SetCorner();
	D2D1_POINT_2F*	GetCorner() { return m_Corner; }

	void			CalculateCorner();
};

