#pragma once

using namespace std;
/// <summary>
/// 콘솔창에서 
/// 로그를 출력해주는 클래스입니다.
/// 그리는 함수는 별도입니다.
/// </summary>
class Debug
{
public:
	Debug();
	~Debug();
public:
	//스태틱으로 전역함수로 설정
	
	//일반적인 문자열 출력합니다
	static void Log(const char* _msg);
	//해당 로그에 대한 표시 정보를 표시를 가변인자로 받을때 사용합니다.
	static void LogFormat(const char* _msg,...);
	//에러로 표시되는 문자열을 출력합니다 . 
	static void LogError(const char* _msg);


	//로그에 대한 라인을 그릴때 사용합니다.
	//static void DrawLine(Vector2 _start,Vector2 _end, D2D1_COLOR_F _color,float _duration);

};

