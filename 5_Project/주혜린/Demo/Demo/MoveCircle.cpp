#include "pch.h"
#include "framework.h"
#include "MoveCircle.h"

void MoveCircle::Update()
{
	Vector2 tr;

	if (IsKey(VK_UP))
	{
		tr.y = -1;
	}
	if (IsKey(VK_DOWN))
	{
		tr.y = 1;
	}
	if (IsKey(VK_LEFT))
	{
		tr.x = -1;
	}
	if (IsKey(VK_RIGHT))
	{
		tr.x = 1;
	}

	if (IsKey(VK_F1))
	{
		m_GameObject->m_Transform->SetPosition(0, 0);
	}

	tr *= 5; //speed

	m_GameObject->m_Transform->Translate(tr);
}
