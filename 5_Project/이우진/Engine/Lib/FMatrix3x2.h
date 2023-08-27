#pragma once
class FMatrix3x2
{
public:
	//double m_Matrix[3]][2] = { 0, };

	/*
	우리가아는 3x2  컴퓨터의 3x2
	{0,0},	         {0,0,0},
	{0,0},			 {0,0,0},
	{0,0}
	*/

	float m_Matrix[3][2] = { 0, };


public:
	//어떻게 될지 모르니 일단 void
	//역행렬
	//기준행렬
	//이동행렬
	//전치행렬
	//닮음행렬(스케일)
	//회전행렬
	FMatrix3x2 Translate(D2D1_SIZE_F _size);
	FMatrix3x2 Translate(float _x, float _y);
	FMatrix3x2 Rotate(float _angle, D2D1_POINT_2F _center = D2D1::Point2F());
	FMatrix3x2 Scale(D2D1_SIZE_F size, D2D1_POINT_2F center = D2D1::Point2F());
	FMatrix3x2 Scale(FLOAT x, FLOAT y, D2D1_POINT_2F center = D2D1::Point2F());

	//초기화
	FMatrix3x2 Identy();//행렬을 초기화해주는 함수


	FMatrix3x2 operator + (FMatrix3x2 _v);

	FMatrix3x2 operator - (FMatrix3x2 _v);

	FMatrix3x2 operator * (FMatrix3x2 _v);

	FMatrix3x2 operator * (float _n);

	FMatrix3x2 operator * (D2D1_POINT_2F _v);

	FMatrix3x2 operator = (FMatrix3x2 _v);


	Vector2 operator * (Vector2 _v);

};

