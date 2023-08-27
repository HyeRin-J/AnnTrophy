#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "BoundShape.h"
#include "BoundCircle.h"
#include "BoundRect.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"

void BoundRect::OnRender()
{
	RRYD2DEngine* m_pEngine = RRYD2DEngine::GetInstance();
	m_pEngine->RotateTransform(m_GameObject->m_Transform->m_Rotate, m_GameObject->m_Transform->m_Position);

	m_pEngine->
		DrawHollowRect(m_GameObject->m_Transform->m_Position.x - m_GameObject->m_Transform->m_Scale.width / 2,
			m_GameObject->m_Transform->m_Position.y - m_GameObject->m_Transform->m_Scale.height / 2,
			m_GameObject->m_Transform->m_Scale.width,
			m_GameObject->m_Transform->m_Scale.height, m_DrawColor);
	m_pEngine->DrawLine(-20, 0, 100, 0, D2D1::ColorF::Red);
	m_pEngine->DrawLine(0, -20, 0, 100, D2D1::ColorF::Green);

	m_pEngine->IdentityTransform();
}

void BoundRect::Update()
{
}

bool BoundRect::IsCheckAABBCollision(BoundRect r)
{
	D2D1_POINT_2F point = r.m_GameObject->m_Transform->GetPosition();

	// 실제로 겹쳐지는지 값 확인
	if (fabs(point.x - m_GameObject->m_Transform->GetPosition().x) < (r.m_GameObject->m_Transform->GetScale().width / 2 + m_GameObject->m_Transform->GetScale().width / 2) &&
		fabs(point.y - m_GameObject->m_Transform->GetPosition().y) < (r.m_GameObject->m_Transform->GetScale().height / 2 + m_GameObject->m_Transform->GetScale().height / 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoundRect::IsCheckOBBCollision(BoundRect target)
{
	CalculateCorner();
	target.CalculateCorner();

	//사영할 기저벡터 계산
	Vector2 e[4] = {
		Vector2(m_IdentityCorner[0], m_IdentityCorner[1]),
		Vector2(m_IdentityCorner[0], m_IdentityCorner[2]),
		Vector2(target.m_IdentityCorner[0], target.m_IdentityCorner[1]),
		Vector2(target.m_IdentityCorner[0], target.m_IdentityCorner[2]) };

	//위치 벡터
	Vector2 v1[4], v2[4];

	//min, max 값 각각 계산
	double min[4], minTar[4];
	double max[4], maxTar[4];

	//초기화
	for (int i = 0; i < 4; i++)
	{
		v1[i] = Vector2(m_IdentityCorner[i].x, m_IdentityCorner[i].y);
		v2[i] = Vector2(target.m_IdentityCorner[i].x, target.m_IdentityCorner[i].y);
		min[i] = minTar[i] = INT_MAX;
		max[i] = maxTar[i] = -INT_MAX;
	}

	// 내적하여 각각의 기저벡터에 대해 min max 계산
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			double dot1 = v1[j].Dot(e[i]);
			double dot2 = v2[j].Dot(e[i]);

			if (dot1 < min[i])
			{
				min[i] = dot1;
			}
			if (dot1 > max[i])
			{
				max[i] = dot1;
			}
			if (dot2 < minTar[i])
			{
				minTar[i] = dot2;
			}
			if (dot2 > maxTar[i])
			{
				maxTar[i] = dot2;
			}
		}
	}

	// 실제로 겹쳐지는지 값 확인
	int trueCount = 0;

	for (int i = 0; i < 4; i++)
	{
		if (min[i] <= maxTar[i]
			&& minTar[i] <= max[i])
		{
			trueCount++;
		}
	}

	// 4개의 축에 대해 전부 겹쳐지면 true
	if (trueCount == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BoundRect::SetCorner()
{
	m_Corner[0] =
		D2D1::Point2F(m_GameObject->m_Transform->GetPosition().x - m_GameObject->m_Transform->GetScale().width / 2, m_GameObject->m_Transform->GetPosition().y - m_GameObject->m_Transform->GetScale().height / 2);
	m_Corner[1] =
		D2D1::Point2F(m_GameObject->m_Transform->GetPosition().x + m_GameObject->m_Transform->GetScale().width / 2, m_GameObject->m_Transform->GetPosition().y - m_GameObject->m_Transform->GetScale().height / 2);
	m_Corner[2] =
		D2D1::Point2F(m_GameObject->m_Transform->GetPosition().x - m_GameObject->m_Transform->GetScale().width / 2, m_GameObject->m_Transform->GetPosition().y + m_GameObject->m_Transform->GetScale().height / 2);
	m_Corner[3] =
		D2D1::Point2F(m_GameObject->m_Transform->GetPosition().x + m_GameObject->m_Transform->GetScale().width / 2, m_GameObject->m_Transform->GetPosition().y + m_GameObject->m_Transform->GetScale().height / 2);
}

void BoundRect::CalculateCorner()
{
	Matrix3x2F axis = Matrix3x2F::Rotation(m_GameObject->m_Transform->GetRotation(), m_GameObject->m_Transform->GetPosition());

	for (int i = 0; i < 4; i++)
	{
		m_IdentityCorner[i] = axis.TransformPoint(m_Corner[i]);
	}
}
