#pragma once

#include "FMatrix3x3.h"
class Component;

//스스로 이해를 할려고 노력은 해보았는데 이렇게 질질끌다보면
//내 자신의 발전도 팀의 노고도 물거품이라.
//성민이형 예제를 참고하면서 만들었다.
//
class Transform : public Component
{
public:
	//멤버변수 


public:
	//생성자 관련
	//확장성을 고려해서 일단은..
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
	//이 코드 부근은
	//교수님예제 기준으로 ... 행렬 식은 알겠는데
	//이게 컴퓨터에게 적용이 되는게 신기하다.
	static D2D1_MATRIX_3X2_F MakeTranslationMatrix(D2D1_SIZE_F size);
	static D2D1_MATRIX_3X2_F MakeRotationMatrix(FLOAT angle, D2D1_POINT_2F center = D2D1::Point2F());
	static D2D1_MATRIX_3X2_F MakeScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center = D2D1::Point2F());

	// 원점에서의 회전, 스케일
	// 이라고는 하나 SetTransform을 하면 다돌아버림
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

