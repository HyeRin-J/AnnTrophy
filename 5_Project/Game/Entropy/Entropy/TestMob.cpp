#include "GamePCH.h"
#include "TestMob.h"

void TestMob::Awake()
{
	this->m_GameObject->SetStringName("Mob");
	this->m_GameObject->SetStringTag("Mob");
	this->m_GameObject->SetPos(D2D1::Point2F(500.f, 300.f));
	this->m_GameObject->m_pTransform->SetScale(100, 100);

	m_Collider = this->m_GameObject->AddComponent<BoxCollider>();
	m_Collider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(100, 100));

	m_Rigidbody = this->m_GameObject->AddComponent<Rigidbody>();
	m_Rigidbody->SetCollisionMode(CollisionDetectionMode::AABB);
	m_Rigidbody->OnGravity();

	m_Collider->SetDebug();
	m_Collider->AddIgnoreTag("Weapon");


	//사거리
	m_Range = this->m_GameObject->AddComponent<BoxCollider>();
	m_Range->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(200, 200));

	m_Range->SetDebug();

	//test BT set
	BtRoot = new BTMob::Sequence();
	//BTMob::Sequence* Sequence = new BTMob::Sequence();
	BTMob::Node* RangeChecker = new BTMob::PlayerRangeChecker();
	BTMob::Node* MoveTask = new BTMob::MoveTask();

	BtRoot->AddChild(RangeChecker);
	BtRoot->AddChild(MoveTask);

	cout << "test Bob bt 생성" << endl;

}

void TestMob::Update()
{
	BtRoot->Invoke();
}

void TestMob::OnRender()
{
}
