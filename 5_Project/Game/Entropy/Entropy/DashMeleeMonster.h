#pragma once

//�뽬�� �ٰŸ� ����
class DashMeleeMonster : public MeleeMonster
{
	//m_AttackReach �� �뽬 �Ÿ��� ���
	float m_DashSpeed;
	BoxCollider* m_pLeftShieldCollider;
	BoxCollider* m_pRightShieldCollider;

	BoxCollider* m_pUpShieldCollider;
	BoxCollider* m_pDownShieldCollider;

	//bool DashSoundOut = false;
	bool IsDefense = false;
	bool DefenseSoundOut = false;
	//test 
	bool IsAttack = false;
public:
	virtual void Awake();
	virtual void Update();
	virtual void OnDestroy();

	//testing
	virtual void OnRender();

	virtual void InitProperties();
	virtual void InitColliders();
	virtual void InitSprites();
	
public:

	void Dash(); //atk
	//virtual void Attack();
	virtual void Move();
	virtual void Dead();
	virtual void IsDetected();
	//virtual bool CheckAttacked();
	void CheckDefenseIN();
	void CheckDefenseOUT();

	void PushPlayer();

public:
	//virtual void FlipAnimation();
	virtual void StopAllAnimation();

};

