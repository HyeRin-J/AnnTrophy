#include "pch.h"
#include "FTime.h"

/// <summary>
/// 교수님 타이머 예제코드를 이용한다.
/// </summary>
FTime::FTime()
{
	// 카운터 체크. 1초당 몇 번을 세는 것인가?
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_CountsPerSec);

	// 1카운트당 몇 초나 걸리나?
	m_SecondsPerCount = 1.0 / (double)m_CountsPerSec;
}

FTime::~FTime()
{
}


float FTime::GetDeltaTimeMS()
{
	m_DeltaTime = m_DeltaCount * m_SecondsPerCount;

	// 값이 double에서 float로 잘리지만 그것이 중요한 함수는 아니다.
	// 밀리세컨드로 변환 해 준다.
	return (float)m_DeltaTime * 1000.0f;
}

float FTime::GetFPS()
{
	if (m_DeltaTime != 0)
	{
		return (float)(1.0 / m_DeltaTime);
	}
	return 0;
}

void FTime::FixedUpdate()
{
	//프레임 제어를 해주자
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentCount);

	m_DeltaCount = (m_CurrentCount - m_PreviousCount);

	m_DeltaTime = m_DeltaCount * m_SecondsPerCount;

	m_PreviousCount = m_CurrentCount;
	if (m_DeltaCount < 0)
	{
		m_DeltaCount = 0;
	}
}

void FTime::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentCount);

	// Time difference between this frame and the previous.
	m_DeltaCount = (m_CurrentCount - m_PreviousCount);

	// 카운트와 시간을 분리한다.
	m_DeltaTime = m_DeltaCount * m_SecondsPerCount;

	// Prepare for next frame.
	m_PreviousCount = m_CurrentCount;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (m_DeltaCount < 0)
	{
		m_DeltaCount = 0;
	}
}