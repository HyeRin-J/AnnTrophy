#pragma once

class BoundShape
{
protected:
	D2D1_POINT_2F m_CenterPoint{ 0, 0 };
	ColorF m_DrawColor{ 1, 1, 1 };
	double m_Angle = 0;

public:
	/// <summary>
	/// ȭ�鿡 ������ ����Ѵ�
	/// </summary>
	/// <param name="m_pEngine">����� ����</param>
	virtual void	Draw(RRYD2DEngine* m_pEngine) = 0;

	/// <summary>
	/// �߽���ǥ�� �����Ѵ�
	/// </summary>
	/// <param name="x">x Pos</param>
	/// <param name="y">y Pos</param>
	virtual void	SetCenter(int x, int y) { SetCenter(D2D1::Point2F(x, y)); }

	/// <summary>
	/// �߽���ǥ�� �����Ѵ�
	/// </summary>
	/// <param name="point">�߽���</param>
	void			SetCenter(D2D1_POINT_2F point) { m_CenterPoint.x = point.x; m_CenterPoint.y = point.y; }

	/// <summary>
	/// �߽� ��ǥ�� ��ȯ�Ѵ�
	/// </summary>
	/// <returns>�߽� ��ǥ</returns>
	D2D1_POINT_2F	GetCenter() { return m_CenterPoint; }

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

	void			SetAngle(double angle) { m_Angle = angle; }
	double			GetAngle() { return m_Angle; }
};

