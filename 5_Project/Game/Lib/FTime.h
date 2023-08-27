#pragma once
/// <summary>
/// 시간관리
/// 
/// 특정 오브젝트의 시간을 관리하고싶으면
/// object deltaTime Setter 를 이용하여 사용후 reset 해줘야함
/// (다른 오브젝트도 같은 Scale 를 사용하도록 제작되어있음)
/// 
/// </summary>
/// 
class FTime : public SingletonManager<FTime>
{
public:
	FTime();
	~FTime();
	void Timer_Start();
	void Timer_End();
public:
	__int64 m_CountsPerSec;
public:
	//60프레임 고정 업데이트
	long long m_StartTick;
	long long m_CurrTick;
	float m_ElapsedTime;
	float m_DeltaTime;
	float m_FixedDeltaTime = 0.016f;
	float m_frm = 60;

	//Engine Time scale
	float m_EngineDeltaTimeScale = 1.0f;

	//Object Time Scale
	float m_ObjectDeltaTimeScale = 1.0f;

public:
	void	SetFrame(float _frm) { m_frm = _frm; };

	//Engine Delta times Setters

	void	SetEngineDeltaTimeScale(float _scale) { m_EngineDeltaTimeScale = _scale; };
	//Reset delta Time Scale to 1.0f // The use setter can have the same effect.
	void	ResetEngineDeltatTimeScale() { m_EngineDeltaTimeScale = 1.0f; };

	//Objects Delta time Setters

	void	SetObjectDeltaTimeScale(float _scale) { m_ObjectDeltaTimeScale = _scale; };
	//Reset delta Time Scale to 1.0f // The use setter can have the same effect.
	void	ResetObjectDeltatTimeScale() { m_ObjectDeltaTimeScale = 1.0f; };


	//Get Fixed Deltatime for render  
	float	GetRenderFixedDeltaTimeSec();

	// Get Engine Fixed Deltatime for Whole System  
	float	GetEngineFixedDeltaTimeSec();

	//Get Object Fixed Deltatime for Some Object Etc. player
	float	GetObjectFixedDeltaTimeSec();


	void	SetFixedDeltaTimeSec();
	float	GetDeltaTimeMS();
	int		GetFPS();

	void	CheckTime();
	bool	FixedUpdate();
};

