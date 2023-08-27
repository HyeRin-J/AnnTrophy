#include "GamePCH.h"
#include "Gate.h"

void Gate::Awake()
{
	m_pSprite = m_GameObject->AddComponent<Sprite>();
	m_pSprite->LoadSprite(_T("gate.txt"), _T("gate.png"), _T("gate"));
	m_pSprite->StopAnimation();
	m_pSprite->m_IsPlayOnce = true;
	m_pSprite->SetActive(false);
}

void Gate::Update()
{
	if (m_IsOpen == true)
	{
		m_pSprite->StartAnimation();

		if (m_InteractionTime <= 1.0f)
		{
			if (m_Collider->m_Target.size() > 0 && m_Collider->m_Target[0]->m_GameObject->GetStringTag()._Equal("Player"))
			{
				if (m_IsClear == false)
				{
					if (SceneObjectManager::GetInstance()->GetActiveScene()->m_Name._Equal(_T("sector 3-4")) == false)
					{
						UIManager::GetInstance()->m_IsUpgrading = true;
					}
					
					m_IsClear = true;
				}
		
				m_InteractionTime += _FTime->GetObjectFixedDeltaTimeSec();
			}
		}
		else
		{
			m_pSprite->StopAnimation();
			SceneObjectManager::GetInstance()->Release();
			SceneObjectManager::GetInstance()->LoadNextScene();
		}
	}
}

void Gate::OnRender()
{
	if (m_IsOpen)
	{
		D2D1_POINT_2F point = m_GameObject->GetPos();
		D2D1_SIZE_F size = D2D1::SizeF(TILE_SIZE * 2.5f, TILE_SIZE / 3);

		_GraphicEngine->D2DXDrawRectrangle(point.x - size.width / 2, point.y - (TILE_SIZE * 3.f) - size.height / 2, size.width, size.height, ColorF::Black, ColorF::WhiteSmoke, true);
		_GraphicEngine->D2DXDrawRectrangle(point.x - size.width / 2, point.y - (TILE_SIZE * 3.f) - size.height / 2, size.width * m_InteractionTime, size.height, ColorF::Black, ColorF::Yellow, true);
	}
}

void Gate::SetOpen()
{
	_FAudio->FPlaySound(OBJECT_GATE_0);
	m_IsOpen = true;
}

void Gate::Init()
{
	m_IsOpen = false;
	m_IsClear = false;
	m_pSprite->m_SheetIndex = 0;
	m_InteractionTime = 0.f;
	m_pSprite->currTime = 0;
	m_pSprite->startTime = 0.f;
	m_pSprite->StopAnimation();
	m_pSprite->SetActive(true);
}
