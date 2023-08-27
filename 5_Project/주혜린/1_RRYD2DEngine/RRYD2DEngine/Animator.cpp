#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Animator.h"

void Animator::Awake()
{
	LoadData(m_DataPath);
}

void Animator::Update()
{

}

void Animator::OnRender()
{
	if (m_IsPlaying && m_AnimationData.size() > 0)
	{
		static DWORD64 startCount = GetTickCount64();
		DWORD64 currCount = GetTickCount64();

		if ((currCount - startCount) / 100 > m_AnimationData[m_Index].delay)
		{
			startCount = currCount;
			++m_Index %= m_AnimationData.size();
		}

		RRYD2DEngine::GetInstance()->DrawBitmap(m_GameObject->m_Transform->m_Position, m_AnimationData[m_Index], m_Image, m_GameObject->m_Transform->m_Scale);
		RRYD2DEngine::GetInstance()->PrintText(m_GameObject->m_Transform->m_Position.x + 50, m_GameObject->m_Transform->m_Position.y - 50, ColorF::Red, 
			_T("Bitmap 위치 : %.0f, %.0f"), m_AnimationData[m_Index].m_BitmapPos.x, m_AnimationData[m_Index].m_BitmapPos.y);
		RRYD2DEngine::GetInstance()->PrintText(m_GameObject->m_Transform->m_Position.x + 50, m_GameObject->m_Transform->m_Position.y - 30, ColorF::Red, 
			_T("Bitmap 사이즈 : %.0f, %.0f"), m_AnimationData[m_Index].m_BitmapSize.width, m_AnimationData[m_Index].m_BitmapSize.height);
		RRYD2DEngine::GetInstance()->PrintText(m_GameObject->m_Transform->m_Position.x + 50, m_GameObject->m_Transform->m_Position.y - 10, ColorF::Red, 
			_T("Pivot 위치 : %.0f, %.0f"), m_AnimationData[m_Index].m_Pivot.x, m_AnimationData[m_Index].m_Pivot.y);
		RRYD2DEngine::GetInstance()->PrintText(m_GameObject->m_Transform->m_Position.x + 50, m_GameObject->m_Transform->m_Position.y + 10, ColorF::Red, 
			_T("딜레이 : %.2f"), m_AnimationData[m_Index].delay);
	}
}

void Animator::LoadData(PCWSTR dataPath)
{
	std::wstring path(ResourceManager::GetInstance()->LoadFile(dataPath));

	if (path.size() != 0)
	{
		m_AnimationData = ResourceManager::GetInstance()->m_SpritesData;
		RRYD2DEngine::GetInstance()->LoadBitmapFromFile(path.c_str(), &m_Image);
	}
}
