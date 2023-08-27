#pragma once
#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Debug.h"

/// <summary>
/// 콜라이더 기본생성시
/// 기본옵션을 지정해준다.
/// </summary>
Collider::Collider()
{
#ifdef _DEBUG
	//필요는 없는데 재대로 생성됬는지 콘솔창에서 시험해보기 위한 문자열출력
	Debug::Log("콜라이더 생성");
#endif
	//자신은 충돌을 받겠다는 의미.
	this->m_IsTrigger = true;
	//처음으로 자신충돌상태 여부는?
	this->m_IsCrash = false;
	//콜라이더의 정보는 정신사나우니 표시하지않는다.
	this->m_CollderInfo = false;
	//콜라이더의 그림은 디버깅용제외하곤 인게임에선 불필요하니 꺼둔다
	this->m_CollderDraw = false;
}

/// <summary>
/// 콜라이더 소멸자 호출시 기능.. 아직은없다
/// </summary>
Collider::~Collider()
{
#ifdef _DEBUG
	Debug::Log("콜라이더 소멸자 호출");
#endif
}

void Collider::DeleteIgnoreTag(std::string tag)
{
	for (auto it = m_IgnoreList.begin(); it != m_IgnoreList.end(); it++)
	{
		if (it->_Equal(tag) == true)
		{
			m_IgnoreList.erase(it);
			break;
		}
	}
}
