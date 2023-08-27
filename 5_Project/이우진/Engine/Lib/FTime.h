#pragma once
/// <summary>
/// ������ �������� Ÿ�̸� Ŭ������ �����մϴ�
/// 
/// Ÿ��Ŭ������ ������ݴϴ�.
/// �ַ� ���ӿ��� ���ο��� ������ �ϱ� ����
/// ���Ǹ� ������ݴϴ�.
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

