#pragma once
/// <summary>
/// 교수님 예제안의 타이머 클래스를 응용합니다
/// 
/// 타임클래스를 만들어줍니다.
/// 주로 게임엔진 내부에서 동작을 하기 위해
/// 정의를 만들어줍니다.
/// </summary>
/// 
class FTime
{
public:
	FTime();
	~FTime();
public:
	__int64 m_CountsPerSec;
	double m_SecondsPerCount;

	__int64 m_PreviousCount;
	__int64 m_CurrentCount;
	__int64 m_DeltaCount;
	double m_DeltaTime;

	float GetDeltaTimeMS();
	float GetFPS();

	void FixedUpdate();
	void Update();

};

