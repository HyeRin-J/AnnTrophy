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
/// 콜라이더 기본생성시
/// 기본옵션을 지정해준다.
/// </summary>
Collider::Collider()
{
	//필요는 없는데 재대로 생성됬는지 콘솔창에서 시험해보기 위한 문자열출력
	Debug::LogFormat("콜라이더 생성");
	//자신은 충돌을 받겠다는 의미.
	this->m_isCollistion = TRUE;
	//처음으로 자신충돌상태 여부는?
	this->m_isTrigger = FALSE;
	//기본 충돌체크 타입을 지정한다.
	this->m_ColliderType = CollistionType::CC;
	//콜라이더의 정보는 정신사나우니 표시하지않는다.
	this->m_CollderInfo = FALSE;
	//콜라이더의 그림은 디버깅용제외하곤 인게임에선 불필요하니 꺼둔다
	this->m_CollderDraw = FALSE;
	this->m_Transform = new Transform();
}

/// <summary>
/// 콜라이더 소멸자 호출시 기능.. 아직은없다
/// </summary>
Collider::~Collider()
{
	Debug::LogFormat("콜라이더 소멸차 호출");
}

/// <summary>
/// 기본 콜라이더의 사이즈를 지정해주는 함수
/// </summary>
/// <param name="_left"></param>도형의 왼쪽
/// <param name="_top"></param>도형의 위쪽
/// <param name="_right"></param>도형의 오른쪽
/// <param name="_bottom"></param>도형의 아래쪽
void Collider::SetColliderSize(float _left, float _top, float _right, float _bottom)
{
	Update();
	//Debug::LogFormat("콜라이더 사이즈 조절");
	m_ColliderSize.left = _left;
	m_ColliderSize.top = _top;
	m_ColliderSize.right = _right;
	m_ColliderSize.bottom = _bottom;
}

/// <summary>
/// 어떠한 콜라이더를 그려줄지 표시할 OnDraw함수이다 
/// 현재는 이 함수는 순수 가상함수라 의미는없다
/// </summary>

/// <summary>
/// 현재의 기능은없다
/// </summary>
void Collider::Release()
{

}
/// <summary>
/// 어떠한 충돌처리를 지정해줄지 결과
/// </summary>
/// <param name="_target">충돌할 대상의 포인터 </param>
/// <returns></returns>
BOOL Collider::Collisition(Collider* _target)
{
	switch (this->m_ColliderType)
	{
	case CollistionType::CC:
		//서로간의 충돌체크를 여부를 확인 한 후 비교를해준다,
		if (this->m_isCollistion == TRUE && _target->m_isCollistion == TRUE)
		{
			//마지막에 비교한 충돌체의 거리값을 비교 후에 넣는다.
			float dis = Vector2::Distance
			(
				this->m_ColliderSize.left,
				this->m_ColliderSize.top,
				_target->m_ColliderSize.left,
				_target->m_ColliderSize.top
			);
			//거리값이랑 원의 지름이랑 비교
			if (dis < 150)
			{
				//일정영역에 도달하면 충돌!
				Debug::LogFormat("충돌 범위 밖 : dis :%f.1\n ", dis);
				//서로가 충돌했다는 플래그를 설정
				this->m_isTrigger = TRUE;
				_target->m_isTrigger = TRUE;
			}
			else
			{
				Debug::LogFormat("충돌 범위 안 : dis :%f.1\n ", dis);

				this->m_isTrigger = FALSE;
				_target->m_isTrigger = FALSE;
			}
		}

		break;
	case CollistionType::AABB:
		//AABB는 여러방법이 있겠지만
		//측면과 측면사이를 비교해서 4방향을 서로 비교하는
		//방법을 생각하고 있었는데 , 사각형 중앙의 점을 비교하여 
		//대각선을 제외 상하좌우만 비교하여 빠진값으로 비교하는 방법이 있길래
		//나도 그걸 해봐겠다.
		//CC와 비슷한데 원과 달리 사각형은 대각선은 비교를 안하는것이 원칙
		
		//서로간의 충돌체크를 여부를 확인 한 후 비교를해준다
		if (this->m_isCollistion == TRUE && _target->m_isCollistion == TRUE)
		{
			
			//4방향으로 비교하는방법이다. 사격형 처음위치를 설정하자..
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
			//점과 점사이를 비교하는 방법

			//D2D1_POINT_2F _pos;
			//_pos.x = _target->m_Transform->postion.x;
			//_pos.y = _target->m_Transform->postion.y;
			////절대값으로 기준
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


