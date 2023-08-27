#pragma once

#if _XM_VECTORCALL_
#define XM_CALLCONV __vectorcall
#else
#define XM_CALLCONV __fastcall
#endif

//constexpr 상수식
//explicit 암시적인 형변환을 막기위해 사용

namespace D3D11Math
{
	const float PI = 3.1415926535f;
	float ConvertToRadian(float _Degree);
}
namespace D3D11Color
{
	//Vector4 g_Color = { 0.0f,0.0f,0.0f,0.0f };
}

class Vector2
{
public:
	Vector2();
	Vector2(const Vector2& _v3);
	Vector2(float _x, float _y, float _z);

	float x;
	float y;
	float z;

	Vector2 operator+(const Vector2&);
	Vector2 operator+=(const Vector2&);
	Vector2 operator-(const Vector2&);
	Vector2 operator-=(const Vector2&);
	Vector2 operator*(const Vector2&);
	Vector2 operator*=(const Vector2&);
	Vector2 operator/(const Vector2&);
	Vector2 operator/=(const Vector2&);
	Vector2 operator=(const Vector2&);

	void Noramlize();
};


class FMatrix3x3;
class FMatrix4x4;

class Vector3
{
public:
	Vector3();
	Vector3(const Vector3& _v3);
	Vector3(float _x, float _y, float _z);

	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3&);
	Vector3 operator+=(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3 operator-=(const Vector3&);
	Vector3 operator*(const Vector3&);
	Vector3 operator*=(const Vector3&);
	Vector3 operator/(const Vector3&);
	Vector3 operator/=(const Vector3&);
	Vector3 operator=(const Vector3&);

	void Noramlize();

	Vector3 operator*(const FMatrix3x3&);
};

class Vector4
{
public:
	Vector4();
	Vector4(const Vector4&);
	Vector4(float _x, float _y, float _z, float _w);
	float x;
	float y;
	float z;
	float w;

	Vector4 operator+(const Vector4&);
	Vector4 operator+=(const Vector4&);
	Vector4 operator-(const Vector4&);
	Vector4 operator-=(const Vector4&);
	Vector4 operator*(const Vector4&);
	Vector4 operator*=(const Vector4&);
	Vector4 operator/(const Vector4&);
	Vector4 operator/=(const Vector4&);
	Vector4 operator=(const Vector4&);
	Vector4 operator*(const FMatrix4x4&);


	Vector4 Noramlize();
	Vector4 Normalize3();



	//외적
	Vector4 Cross(Vector4& v);
	//내적
	float Dot(const Vector3&);
	//
	Vector4 DivideW();

};

class FMatrix4x4
{
public:
	FMatrix4x4();
	FMatrix4x4(const FMatrix4x4&);

	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m_Matrix[4][4];
	};


	FMatrix4x4 operator*(const FMatrix4x4&);
	FMatrix4x4 operator*=(const FMatrix4x4&);
	FMatrix4x4 operator+(const FMatrix4x4&);
	FMatrix4x4 operator+=(const FMatrix4x4&);
	FMatrix4x4 operator-(const FMatrix4x4&);
	FMatrix4x4 operator-=(const FMatrix4x4&);

	FMatrix4x4& operator=(const FMatrix4x4&);
	


	FMatrix4x4 Identity(void);
	FMatrix4x4 WorldMatrix(void);
	FMatrix4x4 Translate(const Vector3&);
	FMatrix4x4 Scale(const Vector3&);
	FMatrix4x4 Rotation(float _angle);
	FMatrix4x4 RotationAxis(float _Angle);

};

class Vertex
{
public:
	Vertex();
	Vertex(const Vector3& _pos, const Vector4& _colors);
	
	Vector3 m_Pos;

	Vector4 m_Color;

};