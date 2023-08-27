#pragma once

class FMatrix3x3
{
public:
	float m_Matrix[3][3] = { 0.f };


	FMatrix3x3();
	FMatrix3x3(FLOAT m11, FLOAT m12, FLOAT m13,
		FLOAT m21, FLOAT m22, FLOAT m23,
		FLOAT m31, FLOAT m32, FLOAT m33);

	void operator=(const float(&matrix)[3][3]);
	FMatrix3x3 operator+(const FMatrix3x3& m);
	FMatrix3x3 operator-(const FMatrix3x3& m);
	FMatrix3x3 operator*(const float& f);
	FMatrix3x3 operator*(const FMatrix3x3& m);

	//단위 행렬확인
	BOOL IsIdentity();
	BOOL IsInvertible();
	BOOL Invert();

	static FMatrix3x3 Translation(float x, float y);
	static FMatrix3x3 Rotation(float angle, D2D1_POINT_2F center);
	static FMatrix3x3 Scale(D2D1_SIZE_F size, D2D1_POINT_2F center);

	//++추가구현	
	D2D_MATRIX_3X2_F ConvertD2D();

	//미구현
	FMatrix3x3 Skew(float angleX, float angleY, D2D1_POINT_2F center);
};

