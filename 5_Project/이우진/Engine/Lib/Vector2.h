#pragma once

#define ToDegree(radian) ( (rad)/PI* 180.0f ) //�̰� �ǳ�?
#define ToRadian(degree) ( (degree)/ 180.0f ) * PI //

class Vector2
{
public:
	float x, y;
public:

public:
	//�⺻������ ,�Ҹ���
	Vector2();
	Vector2(float  _x, float _y);
	Vector2(Vector2& _v2);
	Vector2(const Vector2 _v1,const Vector2 _v2);
	~Vector2();
public:
	//���� �����ε�


	Vector2  operator +(Vector2 _a);
	Vector2  operator +=(Vector2 _a);
	Vector2  operator -(Vector2 _a);
	Vector2  operator -=(Vector2 _a);

	Vector2  operator *(float _v);
	Vector2  operator *=(float _v);

	Vector2  operator / (float _b);
	Vector2  operator /=(float _b);


	//�� �����ε�
	bool operator != (const Vector2 _v);//���������� false�� ��ȯ
	bool operator ==(const Vector2 _v);//������ true�� ��ȭ


private:
	//��������

	
public:
	//get , set�� �������� ������ ����� 
private:
	//����
	float m_magnitude;//�����Ǳ��̸� ��ȯ(�б�����)
	float m_sqrMagnitude;//�����Ǳ����� ������ ���� ��ȯ�� ������ ����
	float m_normalized; //�ش纤���� magnitude�� 1�� ���͸� ��ȯ�ϴ� ����.

public:
	//��ȯ�Լ�

	
	Vector2 Normalized(Vector2 _v);//����2 Ŭ���������� ����ȭ ��ŵ�ϴ�.

	Vector2 Min(Vector2 _a, Vector2 _b);//�� ������ �ּ� ���п��� ���͸� ��ȯ�մϴ�.
	Vector2 Max(Vector2 _a, Vector2 _b);//�� ������ �ִ� ���п��� ���͸� ��ȯ�մϴ�.
	Vector2 Set(float _x, float _y);
	Vector2 Scale(Vector2 _a, Vector2 _b);//	�� ���� ������Ҹ� ���մϴ�.

	float Angle(Vector2 _a, Vector2 _b);//to�� to������ ������ ��ȯ�Ѵ�.
	float Distance(Vector2 _a, Vector2 _b);//�� ������ ������ �Ÿ���
	static float Distance(float _myX, float _myY, float _targetX, float _targetY);//�� ������ ������ �Ÿ���

	float Dot(Vector2 _a, Vector2 _b);//�� ������ ������ �� ���Ѵ�.

	//������ ũ�⸸ ���Ҷ� ����Ѵ�
	//������ ũ�⸦ _maxlength������ �����Ͽ� ���͸� �����Ѵ�.
	float GetMagnitude();//������ ���̸� ��ȯ (�б�����)
	float GetSqrMagnitude();

public:
	//��ȯ�� ���� �Լ�
	

	void MoveToword(Vector2& _start, Vector2& _end, float _moveDeleta);//���������� �������� �̵��Ѵ�.


	Vector2 Lerp(Vector2 _a, Vector2 _b , float _time);//�� ���ͻ��̸� �������� �Ѵ�.
	
													
	//�ݻ纤��											
	//iV:�ݻ��ų ���� 
	//nV:����� �븻����
	Vector2 Reflect(Vector2 iV, Vector2 nV);
	//iV:������ų ���� 
	//nV:����� �븻����
	//rl:������
	Vector2 Reflect(Vector2 iV, Vector2 nV ,double rl);


	//��ӹ��� ����
	//void ToString();//�ش� ��ü�� ���� ����x,y�� ���ڿ��� ������ش�.
	
};

