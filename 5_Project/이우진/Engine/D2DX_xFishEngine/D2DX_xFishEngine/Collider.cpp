#include "pch.h"
#include "Object.h"
#include "Vector2.h"
#include "D2DGraphics.h"
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
	//�ʿ�� ���µ� ���� ��������� �ܼ�â���� �����غ��� ���� ���ڿ����
	Debug::LogFormat("�ݶ��̴� ����");
	//�ڽ��� �浹�� �ްڴٴ� �ǹ�.
	this->m_isCollistion = TRUE;
	//ó������ �ڽ��浹���� ���δ�?
	this->m_isTrigger = FALSE;
	//�⺻ �浹üũ Ÿ���� �����Ѵ�.
	this->m_ColliderType = CollistionType::CC;
	//�ݶ��̴��� ������ ���Ż糪��� ǥ�������ʴ´�.
	this->m_CollderInfo = FALSE;
	//�ݶ��̴��� �׸��� �����������ϰ� �ΰ��ӿ��� ���ʿ��ϴ� ���д�
	this->m_CollderDraw = FALSE;
	this->m_Transform = new Transform();
}

/// <summary>
/// �ݶ��̴� �Ҹ��� ȣ��� ���.. ����������
/// </summary>
Collider::~Collider()
{
	Debug::LogFormat("�ݶ��̴� �Ҹ��� ȣ��");
}

/// <summary>
/// �⺻ �ݶ��̴��� ����� �������ִ� �Լ�
/// </summary>
/// <param name="_left"></param>������ ����
/// <param name="_top"></param>������ ����
/// <param name="_right"></param>������ ������
/// <param name="_bottom"></param>������ �Ʒ���
void Collider::SetColliderSize(float _left, float _top, float _right, float _bottom)
{
	Update();
	//Debug::LogFormat("�ݶ��̴� ������ ����");
	m_ColliderSize.left = _left;
	m_ColliderSize.top = _top;
	m_ColliderSize.right = _right;
	m_ColliderSize.bottom = _bottom;
}

/// <summary>
/// ��� �ݶ��̴��� �׷����� ǥ���� OnDraw�Լ��̴� 
/// ����� �� �Լ��� ���� �����Լ��� �ǹ̴¾���
/// </summary>

/// <summary>
/// ������ ���������
/// </summary>
void Collider::Release()
{

}
/// <summary>
/// ��� �浹ó���� ���������� ���
/// </summary>
/// <param name="_target">�浹�� ����� ������ </param>
/// <returns></returns>
BOOL Collider::Collisition(Collider* _target)
{
	switch (this->m_ColliderType)
	{
	case CollistionType::CC:
		//���ΰ��� �浹üũ�� ���θ� Ȯ�� �� �� �񱳸����ش�,
		if (this->m_isCollistion == TRUE && _target->m_isCollistion == TRUE)
		{
			//�������� ���� �浹ü�� �Ÿ����� �� �Ŀ� �ִ´�.
			float dis = Vector2::Distance
			(
				this->m_ColliderSize.left,
				this->m_ColliderSize.top,
				_target->m_ColliderSize.left,
				_target->m_ColliderSize.top
			);
			//�Ÿ����̶� ���� �����̶� ��
			if (dis < 150)
			{
				//���������� �����ϸ� �浹!
				Debug::LogFormat("�浹 ���� �� : dis :%f.1\n ", dis);
				//���ΰ� �浹�ߴٴ� �÷��׸� ����
				this->m_isTrigger = TRUE;
				_target->m_isTrigger = TRUE;
			}
			else
			{
				Debug::LogFormat("�浹 ���� �� : dis :%f.1\n ", dis);

				this->m_isTrigger = FALSE;
				_target->m_isTrigger = FALSE;
			}
		}

		break;
	case CollistionType::AABB:
		//AABB�� ��������� �ְ�����
		//����� ������̸� ���ؼ� 4������ ���� ���ϴ�
		//����� �����ϰ� �־��µ� , �簢�� �߾��� ���� ���Ͽ� 
		//�밢���� ���� �����¿츸 ���Ͽ� ���������� ���ϴ� ����� �ֱ淡
		//���� �װ� �غ��ڴ�.
		//CC�� ����ѵ� ���� �޸� �簢���� �밢���� �񱳸� ���ϴ°��� ��Ģ
		
		//���ΰ��� �浹üũ�� ���θ� Ȯ�� �� �� �񱳸����ش�
		if (this->m_isCollistion == TRUE && _target->m_isCollistion == TRUE)
		{
			
			//4�������� ���ϴ¹���̴�. ����� ó����ġ�� ��������..
			if (this->GetColliderSize().left > _target->GetColliderSize().right &&
				this->GetColliderSize().top > _target->GetColliderSize().bottom &&
				this->GetColliderSize().right < _target->GetColliderSize().left &&
				this->GetColliderSize().bottom < _target->GetColliderSize().top
				)
			{
				this->m_isTrigger = TRUE;
				_target->m_isTrigger = TRUE;
			}
			else
			{
				this->m_isTrigger = FALSE;
				_target->m_isTrigger = FALSE;
			}
			//���� �����̸� ���ϴ� ���

			//D2D1_POINT_2F _pos;
			//_pos.x = _target->m_Transform->postion.x;
			//_pos.y = _target->m_Transform->postion.y;
			////���밪���� ����
			//
			//if(
			//	fabsf(_pos.x - m_Transform->postion.x) < (_target->m_Transform->m_Scale.width/2 - _target->m_Transform->m_Scale.width / 2)
			//	&&
			//	fabsf(_pos.y - m_Transform->postion.y) < (_target->m_Transform->m_Scale.height / 2 - _target->m_Transform->m_Scale.height / 2)
			//)
			//{
			//	this->m_isTrigger = TRUE;
			//	_target->m_isTrigger = TRUE;
			//}
			//else
			//{
			//	this->m_isTrigger = FALSE;
			//	_target->m_isTrigger = FALSE;
			//}

		}



		break;
	case CollistionType::OBB:
		break;
	}
	


	return TRUE;
}

void Collider::ToString()
{
}


