#include "pch.h"
#include "Vector2.h"
#include "FMatrix3x2.h"

using namespace D2D1;

FMatrix3x2 FMatrix3x2::operator+(FMatrix3x2 _v)
{
	FMatrix3x2 result;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.m_Matrix[i][j] = m_Matrix[i][j] + _v.m_Matrix[i][j];
		}
	}

	return result;
}

FMatrix3x2 FMatrix3x2::operator-(FMatrix3x2 _v)
{
	FMatrix3x2 result;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.m_Matrix[i][j] = m_Matrix[i][j] - _v.m_Matrix[i][j];
		}
	}

	return result;
}

FMatrix3x2 FMatrix3x2::operator*(FMatrix3x2 _v)
{
	//   ex)���� ����
	//  |1__3| 1_|_5
	//	|2__4| 2_|_3	
	//	|5  7| 4 | 7
	//

	FMatrix3x2 result;

	result.m_Matrix[0][0] = ((m_Matrix[0][0] * _v.m_Matrix[0][0]) + (m_Matrix[0][1] * _v.m_Matrix[1][0]));

	result.m_Matrix[0][1] = ((m_Matrix[0][0] * _v.m_Matrix[0][1]) + (m_Matrix[0][1] * _v.m_Matrix[1][1]));

	result.m_Matrix[1][0] = ((m_Matrix[1][0] * _v.m_Matrix[0][0]) + (m_Matrix[1][1] * _v.m_Matrix[1][0]));

	result.m_Matrix[1][1] = ((m_Matrix[1][0] * _v.m_Matrix[0][1]) + (m_Matrix[1][1] * _v.m_Matrix[1][1]));


	//���� ������ �迭���ڸ� ������ ������ ���⺤��x1������ x1�� �ǹ̰���� +�� ���־���.

	result.m_Matrix[2][0] = ((m_Matrix[2][0] * _v.m_Matrix[0][0]) + (m_Matrix[2][1] * _v.m_Matrix[1][0])) + _v.m_Matrix[2][0];

	result.m_Matrix[2][1] = ((m_Matrix[2][0] * _v.m_Matrix[0][1]) + (m_Matrix[2][1] * _v.m_Matrix[1][1])) + _v.m_Matrix[2][1];

	return result;
}

FMatrix3x2 FMatrix3x2::operator*(float _n)
{
	FMatrix3x2 result;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.m_Matrix[i][j] * _n;
		}
	}

	return result;
}

FMatrix3x2 FMatrix3x2::operator*(D2D1_POINT_2F _v)
{
	D2D1_POINT_2F result;

	result.x = (m_Matrix[0][0] * _v.x + m_Matrix[0][1] * _v.y) + m_Matrix[2][0];
	result.y = (m_Matrix[1][0] * _v.x + m_Matrix[1][1] * _v.y) + m_Matrix[2][1];

	return FMatrix3x2();
}

FMatrix3x2 FMatrix3x2::operator=(FMatrix3x2 _v)
{
	//���� ��Ʈ�������� ���Կ����� �����Ѵ�.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			this->m_Matrix[i][j] = this->m_Matrix[i][j] + _v.m_Matrix[i][j];
		}
	}
	return *this;
}
Vector2 FMatrix3x2::operator*(Vector2 _v)
{
	Vector2 _tempVec;
	//
	//�������� ���͸� ��ȯ�Ѵ�.
	//������ ����(���)�� ������ ����(������ ����? �׷����� z���� �ְ����..)�� �����ش�.

	//{m[0][0],m[0][1]}   {x}
	//{m[1][0],m[1][1]} * {y}
	//{m[2][0],m[2][1]}

	_tempVec.x = (m_Matrix[0][0] * _v.x) + (m_Matrix[0][1] * _v.x);
	_tempVec.y = (m_Matrix[1][0] * _v.y) + (m_Matrix[1][1] * _v.y);



	return _tempVec;
}
//(10) ���⺤�͸�ŭ �����ش�
//(01)
//(wh)
FMatrix3x2 FMatrix3x2::Translate(D2D1_SIZE_F _size)
{
	FMatrix3x2 translate;

	translate.m_Matrix[0][0] = 1.0f;
	translate.m_Matrix[0][1] = 0.0f;
	translate.m_Matrix[1][0] = 0.0f;
	translate.m_Matrix[1][1] = 1.0f;
	translate.m_Matrix[2][0] = _size.width;
	translate.m_Matrix[2][1] = _size.height;

	return translate;

}

FMatrix3x2 FMatrix3x2::Translate(float _x, float _y)
{
	return Translate(D2D1::SizeF(_x, _y));
}

FMatrix3x2 FMatrix3x2::Rotate(float _angle, D2D1_POINT_2F _center)
{
	//������ ��� �ʱ�ȭ
	FMatrix3x2 translateMatrix_1 = Identy();
	translateMatrix_1.m_Matrix[2][0] = _center.x; //���� ����
	translateMatrix_1.m_Matrix[2][1] = _center.y;

	FMatrix3x2 translateMatrix_2 = Identy();
	translateMatrix_2.m_Matrix[2][0] = _center.x;
	translateMatrix_2.m_Matrix[2][1] = _center.y;

	/// <summary>
	/// { cos sin}
	/// {-cos sin}
	/// {x     y }
	/// <returns></returns>
	FMatrix3x2 rotateMatrix;
	rotateMatrix.m_Matrix[0][0] = cosf((_angle / 180) * (float)PI);
	rotateMatrix.m_Matrix[0][1] = sinf((_angle / 180) * (float)PI);
	rotateMatrix.m_Matrix[1][0] = -cosf((_angle / 180) * (float)PI);
	rotateMatrix.m_Matrix[1][1] = sinf((_angle / 180) * (float)PI);


	return (translateMatrix_2 * (rotateMatrix * translateMatrix_1));;
}

FMatrix3x2 FMatrix3x2::Scale(D2D1_SIZE_F size, D2D1_POINT_2F center)
{
	FMatrix3x2 scale;

	/// <summary>
	/// {w , 0}
	/// {0 , h}
	/// {vx,vy}
	/// <returns></returns>
	scale.m_Matrix[0][0] = size.width;
	scale.m_Matrix[0][1] = 0;
	scale.m_Matrix[1][0] = 0;
	scale.m_Matrix[1][1] = size.height;
	scale.m_Matrix[2][0] = size.width * center.x;
	scale.m_Matrix[2][1] = size.height * center.y;


	return scale;
}

FMatrix3x2 FMatrix3x2::Scale(FLOAT x, FLOAT y, D2D1_POINT_2F center)
{
	return Scale(D2D1::SizeF(x, y), center);
}


/// <summary>
/// ����� �ʱ�ȭ���ִ� �Լ��̴�
/// </summary>
/// <returns></returns>
FMatrix3x2 FMatrix3x2::Identy()
{
	FMatrix3x2 identity;

	identity.m_Matrix[0][0] = 1.0f;
	identity.m_Matrix[0][1] = 0.0f;
	identity.m_Matrix[1][0] = 0.0f;
	identity.m_Matrix[1][1] = 1.0f;
	identity.m_Matrix[2][0] = 0.0f;
	identity.m_Matrix[2][1] = 0.0f;

	return identity;
}
