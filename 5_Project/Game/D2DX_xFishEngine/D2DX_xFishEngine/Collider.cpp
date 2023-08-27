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
/// �ݶ��̴� �⺻������
/// �⺻�ɼ��� �������ش�.
/// </summary>
Collider::Collider()
{
#ifdef _DEBUG
	//�ʿ�� ���µ� ���� ��������� �ܼ�â���� �����غ��� ���� ���ڿ����
	Debug::Log("�ݶ��̴� ����");
#endif
	//�ڽ��� �浹�� �ްڴٴ� �ǹ�.
	this->m_IsTrigger = true;
	//ó������ �ڽ��浹���� ���δ�?
	this->m_IsCrash = false;
	//�ݶ��̴��� ������ ���Ż糪��� ǥ�������ʴ´�.
	this->m_CollderInfo = false;
	//�ݶ��̴��� �׸��� �����������ϰ� �ΰ��ӿ��� ���ʿ��ϴ� ���д�
	this->m_CollderDraw = false;
}

/// <summary>
/// �ݶ��̴� �Ҹ��� ȣ��� ���.. ����������
/// </summary>
Collider::~Collider()
{
#ifdef _DEBUG
	Debug::Log("�ݶ��̴� �Ҹ��� ȣ��");
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
