#pragma once

#include "FMatrix3x3.h"
class Component;

//������ ���ظ� �ҷ��� ����� �غ��Ҵµ� �̷��� �������ٺ���
//�� �ڽ��� ������ ���� ��� ����ǰ�̶�.
//�������� ������ �����ϸ鼭 �������.
//
class Transform : public Component
{
public:
	//������� 


public:
	//������ ����
	//Ȯ�强�� ����ؼ� �ϴ���..
	Transform(float _x, float _y);//2d
	Transform();//2d
	virtual ~Transform();

	virtual void	ToString();
	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	FixedUpdate() {};
	virtual void	Update() {};
	virtual void	OnRender() {};
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};

public:
	//�� �ڵ� �α���
	//�����Կ��� �������� ... ��� ���� �˰ڴµ�
	//�̰� ��ǻ�Ϳ��� ������ �Ǵ°� �ű��ϴ�.
	static D2D1_MATRIX_3X2_F MakeTranslationMatrix(D2D1_SIZE_F size);
	static D2D1_MATRIX_3X2_F MakeRotationMatrix(FLOAT angle, D2D1_POINT_2F center = D2D1::Point2F());
	static D2D1_MATRIX_3X2_F MakeScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center = D2D1::Point2F());

	// ���������� ȸ��, ������
	// �̶��� �ϳ� SetTransform�� �ϸ� �ٵ��ƹ���
	static D2D1_MATRIX_3X2_F MakeRotationMatrix_Origin(FLOAT angle);
	static D2D1_MATRIX_3X2_F MakeScaleMatrix_Origin(D2D1_SIZE_F size);

	static void SetTransform(const D2D1_MATRIX_3X2_F& transformMatrix);





public:
	D2D1_POINT_2F m_Position = { 0, 0 };
	double m_Rotate = 0;
	D2D1_SIZE_F m_Scale = { 1, 1 };


	void SetPos(float _x, float _y);
	void SetPos(D2D1_POINT_2F _pos);

	void Translate(float _x, float _y);
	void Translate(Vector2 _vec);



};

