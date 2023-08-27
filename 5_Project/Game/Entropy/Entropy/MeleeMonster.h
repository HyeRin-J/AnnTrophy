#pragma once

//근거리 몬스터
class MeleeMonster : public BaseMonster
{
protected:
	D2D1_SIZE_F		m_AttackReach;

	Sprite* m_MoveSprite;
	Sprite* m_AttackSprite;
	Sprite* m_HitedSprite;
	Sprite* m_DeadSprite;


	
	bool IsMeleeAttack = false;
	
	float m_HitTime = 0.5f;
	bool m_IsHited = false;
	bool m_HitFinish = true;

	bool m_DeadSoundOut = false;
	bool m_DetectSoundOut = false;
public:
	~MeleeMonster() { OnDestroy(); };
	virtual void Awake();
	virtual void Update();
	virtual void OnDestroy();
	//testing
	virtual void OnRender();

	virtual void InitColliders();
	virtual void InitProperties();
	virtual void InitSprites();

public:
	bool IsDead();
	virtual bool CheckAttacked();
	virtual bool IsInReach();
	virtual void IsDetected();



	virtual void Dead();
	virtual void Attack();
	virtual void Move();

public:
	virtual void FlipAnimation();
	virtual void StopAllAnimation();

};
