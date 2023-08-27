#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "AnimationController.h"

void AnimationController::Update()
{
	CheckCondition();

	//m_Sprites[m_CurrIndex]->SetActive(true);

	/*
	if (m_Sprites[m_CurrIndex]->m_IsPlayOnce == true && m_Sprites[m_CurrIndex]->m_IsFinish == true)
	{
		for (auto& condition : m_Conditions)
		{
			condition.second = false;
		}
	}
	*/
}
