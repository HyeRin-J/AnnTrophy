#include "pch.h"
#include "FMatrix3x3.h"


FMatrix3x3::FMatrix3x3()
{
}

FMatrix3x3::FMatrix3x3(FLOAT m11, FLOAT m12, FLOAT m13, FLOAT m21, FLOAT m22, FLOAT m23, FLOAT m31, FLOAT m32, FLOAT m33)
{
	m_Matrix[0][0] = m11;
	m_Matrix[0][1] = m12;
	m_Matrix[0][2] = m13;

	m_Matrix[1][0] = m21;
	m_Matrix[1][1] = m22;
	m_Matrix[1][2] = m23;

	m_Matrix[2][0] = m31;
	m_Matrix[2][1] = m32;
	m_Matrix[2][2] = m33;
}

void FMatrix3x3::operator=(const float(&matrix)[3][3])
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_Matrix[i][j] = matrix[i][j];
		}
	}
}

FMatrix3x3 FMatrix3x3::operator+(const FMatrix3x3& m)
{
	FMatrix3x3 result;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.m_Matrix[i][j] = m_Matrix[i][j] + m.m_Matrix[i][j];
		}
	}

	return result;
}

FMatrix3x3 FMatrix3x3::operator-(const FMatrix3x3& m)
{
	FMatrix3x3 result;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.m_Matrix[i][j] = m_Matrix[i][j] - m.m_Matrix[i][j];
		}
	}

	return result;
}

FMatrix3x3 FMatrix3x3::operator*(const FMatrix3x3& m)
{

	FMatrix3x3 result;

	for (int i = 0; i < 3; i++) //행
	{
		for (int j = 0; j < 3; j++) //열
		{
			for (int k = 0; k < 3; k++) // 곱할 것의 열과 행
			{
				result.m_Matrix[i][j] += m_Matrix[i][k] * m.m_Matrix[k][j];
			}
		}
	}


	return result;
}

FMatrix3x3 FMatrix3x3::operator*(const float& f)
{
	FMatrix3x3 result;

	for (int i = 0; i < 3; i++) //행
	{
		for (int j = 0; j < 3; j++) //열
		{
			result.m_Matrix[i][j] *= f;
		}
	}

	return result;
}


BOOL FMatrix3x3::IsIdentity()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((m_Matrix[i][j] != 1) && (m_Matrix[j][i] != 0))
			{
				return false;
			}
		}

	}

	return true;
}

BOOL FMatrix3x3::IsInvertible()
{
	float det;
	/*A = {
			{a , b , c},
			{d , e , f},
			{g , h , i}
			}
	*/
	//det(A) = a(ei-fh)-b(di-fg)+c(dh-eg)
	//det(A) 가 0 이면 역행렬 없음

	det = m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[2][2] - m_Matrix[1][2] * m_Matrix[2][1]) \
		- m_Matrix[0][1] * (m_Matrix[1][0] * m_Matrix[2][2] - m_Matrix[1][2] * m_Matrix[2][0]) \
		+ m_Matrix[0][2] * (m_Matrix[1][0] * m_Matrix[2][1] - m_Matrix[1][1] * m_Matrix[2][0]);

	if (det == 0)
	{
		return false;
	}

	return true;
}

BOOL FMatrix3x3::Invert()
{
	FMatrix3x3 temp;
	temp = m_Matrix;

	float det =	+ m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[2][2] - m_Matrix[1][2] * m_Matrix[2][1]) \
				- m_Matrix[0][1] * (m_Matrix[1][0] * m_Matrix[2][2] - m_Matrix[1][2] * m_Matrix[2][0]) \
				+ m_Matrix[0][2] * (m_Matrix[1][0] * m_Matrix[2][1] - m_Matrix[1][1] * m_Matrix[2][0]);

	float invdet = 1 / det;

	if (det != 0) // 역행렬이있으면
	{
		m_Matrix[0][0] =  (temp.m_Matrix[1][1] * temp.m_Matrix[2][2] - temp.m_Matrix[2][1] * temp.m_Matrix[1][2]) * invdet;
		m_Matrix[1][0] = -(temp.m_Matrix[0][1] * temp.m_Matrix[2][2] - temp.m_Matrix[0][2] * temp.m_Matrix[2][1]) * invdet;
		m_Matrix[2][0] =  (temp.m_Matrix[0][1] * temp.m_Matrix[1][2] - temp.m_Matrix[0][2] * temp.m_Matrix[1][1]) * invdet;
		m_Matrix[0][1] = -(temp.m_Matrix[1][0] * temp.m_Matrix[2][2] - temp.m_Matrix[1][2] * temp.m_Matrix[2][0]) * invdet;
		m_Matrix[1][1] =  (temp.m_Matrix[0][0] * temp.m_Matrix[2][2] - temp.m_Matrix[0][2] * temp.m_Matrix[2][0]) * invdet;
		m_Matrix[2][1] = -(temp.m_Matrix[0][0] * temp.m_Matrix[1][2] - temp.m_Matrix[1][0] * temp.m_Matrix[0][2]) * invdet;
		m_Matrix[0][2] =  (temp.m_Matrix[1][0] * temp.m_Matrix[2][1] - temp.m_Matrix[2][0] * temp.m_Matrix[1][1]) * invdet;
		m_Matrix[1][2] = -(temp.m_Matrix[0][0] * temp.m_Matrix[2][1] - temp.m_Matrix[2][0] * temp.m_Matrix[0][1]) * invdet;
		m_Matrix[2][2] =  (temp.m_Matrix[0][0] * temp.m_Matrix[1][1] - temp.m_Matrix[1][0] * temp.m_Matrix[0][1]) * invdet;
																  
		return true;
	}
	

	return false;
}

FMatrix3x3 FMatrix3x3::Translation(float x, float y)
{
	FMatrix3x3 operand;
	operand =	
	{
		{1.f,0.f,x},
		{0.f,1.f,y},
		{0.f,0.f,1.f}
	};


	return operand;
}

FMatrix3x3 FMatrix3x3::Rotation(float angle, D2D1_POINT_2F center)
{

	float seta = DegreeToRadian(angle);


	FMatrix3x3 Rmatrix;
	Rmatrix = {
				{cosf(seta),sinf(seta),0.f},
				{-sinf(seta),cosf(seta),0.f},
				{0.f		,0.f		,1.f}
	};

	FMatrix3x3 T1matrix;
	FMatrix3x3 T2matrix;

	T1matrix = FMatrix3x3::Translation(-center.x, -center.y);
	T2matrix = FMatrix3x3::Translation(center.x, center.y);


	//DMatrix_33 ResultMatrix;
	//ResultMatrix = T1matrix*this


	return T2matrix*(Rmatrix*T1matrix);
}

FMatrix3x3 FMatrix3x3::Scale(D2D1_SIZE_F size, D2D1_POINT_2F center)
{
	FMatrix3x3 Smatrix;

	//is it correct?
	float width = center.x + (size.width/2);
	float height = center.y + (size.height/2);

	Smatrix = {
				{width	,0.f	,0.f},
				{0.f	,height	,0.f},
				{0.f	,0.f	,1.f}
	};



	return Smatrix;
}

D2D_MATRIX_3X2_F FMatrix3x3::ConvertD2D()
{

	D2D_MATRIX_3X2_F result;
	result._11 = m_Matrix[0][0];
	result._12 = m_Matrix[0][1];
		   
	result._21 = m_Matrix[1][0];
	result._22 = m_Matrix[1][1];

	result._31 = m_Matrix[2][0];
	result._32 = m_Matrix[2][1];


	return result;
}

//미구현
FMatrix3x3 FMatrix3x3::Skew(float angleX, float angleY, D2D1_POINT_2F center)
{
	return FMatrix3x3();
}