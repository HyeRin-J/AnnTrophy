#include "pch.h"
#include "Vector2.h"


/*
����Ŭ���� ���α���

����� ����Ƽ������ �����Լ� ����� ���� �����غ�

*/

//�����ڿ��� ���� �ʱ�ȭ��������
Vector2::Vector2() 
{
}

Vector2::Vector2(float _x, float _y) :

	m_magnitude(0),
	m_normalized(0),
	m_sqrMagnitude(0)
{
	x = _x;
	y = _y;
	
}

Vector2::Vector2(Vector2& _v2)
{
}


Vector2::Vector2(const Vector2 _v1, const Vector2 _v2)
{
}

Vector2::~Vector2()
{
}
Vector2 Vector2::operator+(Vector2 _a)
{
	Vector2 result =
	{
		this->x + _a.x,
		this->y + _a.y
	};

	return result;
}
Vector2 Vector2::operator+=(Vector2 _a)
{
	Vector2 result =
	{
		this->x + _a.x,
		this->y + _a.y
	};

	return result;
}
Vector2 Vector2::operator-(Vector2 _a)
{
	Vector2 result =
	{
		this->x - _a.x,
		this->y - _a.y
	};

	return result;
}
Vector2 Vector2::operator-=(Vector2 _a)
{
	Vector2 result =
	{
		this->x - _a.x,
		this->y - _a.y
	};

	return result;
}
Vector2 Vector2::operator*(float _v)
{
	Vector2 result =
	{
		this->x * _v,
		this->y * _v
	};

	return result;
}
Vector2 Vector2::operator*=(float _v)
{
	Vector2 result =
	{
		this->x * _v,
		this->y * _v
	};

	return result;
}
Vector2 Vector2::operator/(float _b)
{
	Vector2 result =
	{
		this->x / _b,
		this->y / _b
	};

	return result;
}
Vector2 Vector2::operator/=(float _b)
{
	Vector2 result =
	{
		this->x / _b,
		this->y / _b
	};
	return result;
}
//
bool Vector2::operator!=(const Vector2 _v)
{
	//���������ϳ��� �ȸ����� FALSE�� ��ȯ
	if (this->x != _v.x || this->y != _v.y)
	{
		return FALSE;
	}

	return TRUE;
}

bool Vector2::operator==(const Vector2 _v)
{
	//����� ���� �¾ƾ� TRUE�� ��ȯ
	if (this->x == _v.x && this->y == _v.y)
	{
		return TRUE;
	}

	return FALSE;
}



float Vector2::GetMagnitude()
{
	float maginitude =

		powf(this->x, this->x)
		+
		powf(this->y, this->y);


	return maginitude;
}

float Vector2::GetSqrMagnitude()
{

	float maginitude =
		sqrtf
		(
			powf(this->x, this->x)
			+
			powf(this->y, this->y)
		);

	return maginitude;
}

Vector2 Vector2::Normalized(Vector2 _v)
{
	Vector2 norml;

	norml.x /= GetSqrMagnitude();
	norml.y /= GetSqrMagnitude();

	return norml;
}

float Vector2::Angle(Vector2 _a, Vector2 _b)
{
	//atan2�� double���̹Ƿ� �ڷ����� �����ش�.
	float x = _b.x - _a.x;
	float y = _b.y - _a.y;
	float radian = atan2f(y, x);
	float degree = radian * 180 / (float)PI;

	float angle = degree;
	
	return angle;
}

float Vector2::Distance(Vector2 _a, Vector2 _b)
{
	//������ ��ǥ�� ���ϴ� �������� ����ϰ� ��ȯ

	float dis = (_b - _a).GetSqrMagnitude();

	return dis;
}

float Vector2::Distance(float _myX, float _myY, float _targetX, float _targetY)
{
	return (float)sqrt(pow(_targetX - _myX, 2) + pow(_targetY - _myY, 2));
}

Vector2 Vector2::Min(Vector2 _a, Vector2 _b)
{
	Vector2 result;
	//_a�� _b�� �񱳸��Ѵ�.
	float min_x = (_a.x > _b.x) ? _a.x : _b.x;
	float min_y = (_a.y > _b.y) ? _a.y : _b.y;
	result.x = min_x;
	result.y = min_y;

	return result;
}

Vector2 Vector2::Max(Vector2 _a, Vector2 _b)
{
	Vector2 result;
	//_a�� _b�� �񱳸��Ѵ�.
	float max_x = (_a.x < _b.x) ? _a.x : _b.x;
	float max_y = (_a.y < _b.y) ? _a.y : _b.y;
	result.x = max_x;
	result.y = max_y;

	return result;
}

float Vector2::Dot(Vector2 _a, Vector2 _b)
{
	double _dot =
		_a.x * _a.x
		+
		_a.y * _b.y;

	return _dot;
}

Vector2 Vector2::Set(float _x, float _y)
{
	Vector2 scale;

	x = _x;
	y = _y;
	return scale;
}

Vector2 Vector2::Scale(Vector2 _a, Vector2 _b)
{
	Vector2 scale;

	x = _a.x * _b.x;
	y = _a.y * _b.y;

	return scale;
}

void Vector2::MoveToword(Vector2& _start, Vector2& _end, float _moveDeleta)
{
	//float���̹Ƿ� ��Ȯ�� ���� ��ġ���� �����������Ƿ� int�� ����ĳ������ ���־���
	//a�� b������ �̵��Ÿ��� ���ϰ� _moveDelta���� ŭ ���ؼ� �����δ�.
	while (true)
	{
		float dis = Distance(_start, _end);

		//�� �� �����ǰ����� 0���� ũ�ų� ������
		if (dis <= 0)
		{
			break;
		}
		else
		{
			//�� ��ǥ�� �ϳ��� ū���
			if (_start.x < _end.x || _start.y < _end.y)
			{
				_start += _start;
			}

			//�ݴ��ΰ��
			else
			{
				_start -= _end;
			}
		}
	}

}