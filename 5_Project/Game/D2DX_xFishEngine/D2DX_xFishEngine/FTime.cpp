#include "pch.h"
#include "framework.h"
#include "FTime.h"

/// <summary>
/// 교수님 타이머 예제코드를 이용한다.
/// </summary>
FTime::FTime()
{
	// 카운터 체크. 1초당 몇 번을 세는 것인가?
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 1카운트당 몇 초나 걸리나?
	m_CountsPerSec = frequency.QuadPart;
	m_ElapsedTime = 1.0f / m_frm;
	Timer_Start();
}

FTime::~FTime()
{
}

void FTime::Timer_Start()
{
	LARGE_INTEGER timer;
	QueryPerformanceCounter(&timer);
	m_StartTick = timer.QuadPart;
}

void FTime::Timer_End()
{
	LARGE_INTEGER timer;
	QueryPerformanceCounter(&timer);
	m_CurrTick = timer.QuadPart;
}

float FTime::GetDeltaTimeMS()
{
	// 값이 double에서 float로 잘리지만 그것이 중요한 함수는 아니다.
	// 밀리세컨드로 변환 해 준다.
	return (m_DeltaTime / m_CountsPerSec) * 1000.f;
}

float FTime::GetRenderFixedDeltaTimeSec()
{
	return m_FixedDeltaTime;
}

float FTime::GetEngineFixedDeltaTimeSec()
{
	return m_FixedDeltaTime * m_EngineDeltaTimeScale;
}

float FTime::GetObjectFixedDeltaTimeSec()
{ 
	return m_FixedDeltaTime * m_ObjectDeltaTimeScale;
}

void FTime::SetFixedDeltaTimeSec()
{
	m_FixedDeltaTime = (m_DeltaTime / m_CountsPerSec);
}

int FTime::GetFPS()
{
	return (1000 / GetDeltaTimeMS());
}

void FTime::CheckTime()
{
	m_DeltaTime = m_CurrTick - m_StartTick;
	
	// scale Calculte
	//m_DeltaTime *= m_DeltaTimeScale;
}

bool FTime::FixedUpdate()
{
	// 지금까지의 걸린 시간을 잰다.
	Timer_End();
	CheckTime();

	if ((m_ElapsedTime * 1000) < GetDeltaTimeMS())
	{
		// 다음 프레임으로 갈 수 있다.
		// 시간을 재기 시작한다.
		Timer_Start();
		//m_FixedDeltaTime = m_DeltaTime / m_CountsPerSec;
		return true;
	}

	return false;
}