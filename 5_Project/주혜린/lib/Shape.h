#pragma once

class BoundShape
{
protected:
	D2D1_POINT_2F m_CenterPoint{ 0, 0 };
	ColorF m_DrawColor{ 1, 1, 1 };
	double m_Angle = 0;

public:
	/// <summary>
	/// 화면에 도형을 출력한다
	/// </summary>
	/// <param name="m_pEngine">출력할 엔진</param>
	virtual void	Draw(RRYD2DEngine* m_pEngine) = 0;

	/// <summary>
	/// 중심좌표를 설정한다
	/// </summary>
	/// <param name="x">x Pos</param>
	/// <param name="y">y Pos</param>
	virtual void	SetCenter(int x, int y) { SetCenter(D2D1::Point2F(x, y)); }

	/// <summary>
	/// 중심좌표를 설정한다
	/// </summary>
	/// <param name="point">중심점</param>
	void			SetCenter(D2D1_POINT_2F point) { m_CenterPoint.x = point.x; m_CenterPoint.y = point.y; }

	/// <summary>
	/// 중심 좌표를 반환한다
	/// </summary>
	/// <returns>중심 좌표</returns>
	D2D1_POINT_2F	GetCenter() { return m_CenterPoint; }

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

	void			SetAngle(double angle) { m_Angle = angle; }
	double			GetAngle() { return m_Angle; }
};

