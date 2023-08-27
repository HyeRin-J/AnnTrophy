#include "pch.h"
#include "framework.h"
#include "FTime.h"

/// <summary>
/// ������ Ÿ�̸� �����ڵ带 �̿��Ѵ�.
/// </summary>
FTime::FTime()
{
	// ī���� üũ. 1�ʴ� �� ���� ���� ���ΰ�?
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 1ī��Ʈ�� �� �ʳ� �ɸ���?
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
	// ���� double���� float�� �߸����� �װ��� �߿��� �Լ��� �ƴϴ�.
	// �и�������� ��ȯ �� �ش�.
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
	// ���ݱ����� �ɸ� �ð��� ���.
	Timer_End();
	CheckTime();

	if ((m_ElapsedTime * 1000) < GetDeltaTimeMS())
	{
		// ���� ���������� �� �� �ִ�.
		// �ð��� ��� �����Ѵ�.
		Timer_Start();
		//m_FixedDeltaTime = m_DeltaTime / m_CountsPerSec;
		return true;
	}

	return false;
}