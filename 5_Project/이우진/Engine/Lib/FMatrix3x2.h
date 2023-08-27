#pragma once
class FMatrix3x2
{
public:
	//double m_Matrix[3]][2] = { 0, };

	/*
	�츮���ƴ� 3x2  ��ǻ���� 3x2
	{0,0},	         {0,0,0},
	{0,0},			 {0,0,0},
	{0,0}
	*/

	float m_Matrix[3][2] = { 0, };


public:
	//��� ���� �𸣴� �ϴ� void
	//�����
	//�������
	//�̵����
	//��ġ���
	//�������(������)
	//ȸ�����
	FMatrix3x2 Translate(D2D1_SIZE_F _size);
	FMatrix3x2 Translate(float _x, float _y);
	FMatrix3x2 Rotate(float _angle, D2D1_POINT_2F _center = D2D1::Point2F());
	FMatrix3x2 Scale(D2D1_SIZE_F size, D2D1_POINT_2F center = D2D1::Point2F());
	FMatrix3x2 Scale(FLOAT x, FLOAT y, D2D1_POINT_2F center = D2D1::Point2F());

	//�ʱ�ȭ
	FMatrix3x2 Identy();//����� �ʱ�ȭ���ִ� �Լ�


	FMatrix3x2 operator + (FMatrix3x2 _v);

	FMatrix3x2 operator - (FMatrix3x2 _v);

	FMatrix3x2 operator * (FMatrix3x2 _v);

	FMatrix3x2 operator * (float _n);

	FMatrix3x2 operator * (D2D1_POINT_2F _v);

	FMatrix3x2 operator = (FMatrix3x2 _v);


	Vector2 operator * (Vector2 _v);

};

