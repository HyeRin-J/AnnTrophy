#pragma once

#define ToDegree(radian) ( (rad)/PI* 180.0f ) //이게 되네?
#define ToRadian(degree) ( (degree)/ 180.0f ) * PI //

class Vector2
{
public:
	float x, y;
public:

public:
	//기본생성자 ,소멸자
	Vector2();
	Vector2(float  _x, float _y);
	Vector2(Vector2& _v2);
	Vector2(const Vector2 _v1,const Vector2 _v2);
	~Vector2();
public:
	//연산 오버로딩


	Vector2  operator +(Vector2 _a);
	Vector2  operator +=(Vector2 _a);
	Vector2  operator -(Vector2 _a);
	Vector2  operator -=(Vector2 _a);

	Vector2  operator *(float _v);
	Vector2  operator *=(float _v);

	Vector2  operator / (float _b);
	Vector2  operator /=(float _b);


	//논리 오버로딩
	bool operator != (const Vector2 _v);//같지않으면 false를 반환
	bool operator ==(const Vector2 _v);//맞으면 true를 반화


private:
	//정적변수

	
public:
	//get , set이 많아져서 아직은 고민중 
private:
	//변수
	float m_magnitude;//벡터의길이를 반환(읽기전용)
	float m_sqrMagnitude;//벡터의길이의 제곱한 값을 반환을 저장할 변수
	float m_normalized; //해당벡터의 magnitude가 1인 벡터를 반환하는 변수.

public:
	//반환함수

	
	Vector2 Normalized(Vector2 _v);//벡터2 클래스성분을 정규화 시킵니다.

	Vector2 Min(Vector2 _a, Vector2 _b);//두 벡터의 최소 성분에서 벡터를 반환합니다.
	Vector2 Max(Vector2 _a, Vector2 _b);//두 벡터의 최대 성분에서 벡터를 반환합니다.
	Vector2 Set(float _x, float _y);
	Vector2 Scale(Vector2 _a, Vector2 _b);//	두 벡터 구성요소를 곱합니다.

	float Angle(Vector2 _a, Vector2 _b);//to와 to사이의 각도를 반환한다.
	float Distance(Vector2 _a, Vector2 _b);//두 벡터의 사이의 거리값
	static float Distance(float _myX, float _myY, float _targetX, float _targetY);//두 벡터의 사이의 거리값

	float Dot(Vector2 _a, Vector2 _b);//두 벡터의 내적의 값 구한다.

	//벡터의 크기만 비교할때 사용한다
	//벡터의 크기를 _maxlength까지만 제한하여 벡터를 조정한다.
	float GetMagnitude();//벡터의 길이를 반환 (읽기전용)
	float GetSqrMagnitude();

public:
	//반환이 없는 함수
	

	void MoveToword(Vector2& _start, Vector2& _end, float _moveDeleta);//현재점부터 끝점까지 이동한다.


	Vector2 Lerp(Vector2 _a, Vector2 _b , float _time);//두 벡터사이를 선형보간 한다.
	
													
	//반사벡터											
	//iV:반사시킬 벡터 
	//nV:평면의 노말벡터
	Vector2 Reflect(Vector2 iV, Vector2 nV);
	//iV:굴절시킬 벡터 
	//nV:평면의 노말벡터
	//rl:굴절율
	Vector2 Reflect(Vector2 iV, Vector2 nV ,double rl);


	//상속받을 예정
	//void ToString();//해당 객체를 가진 벡터x,y를 문자열로 출력해준다.
	
};

