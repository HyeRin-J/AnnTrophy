#include "GamePCH.h"
#include "Switch.h"

void Switch::Awake()
{
	m_pSprite = m_GameObject->AddComponent<Sprite>();
	m_pSprite->LoadSprite(_T("switch_on.txt"), _T("switch_on.png"), _T("switch"));
	m_pSprite->StopAnimation();
	m_pSprite->SetActive(false);
}

void Switch::Update()
{
	static float m_Delay = 0.f;

	if (m_InteractionTime <= 3.0f)
	{
		if (m_Collider != nullptr && m_Collider->m_Target.size() > 0 && m_Collider->m_Target[0]->m_GameObject->GetStringTag()._Equal("Player"))
		{
			if (InputManager::InputKey(VK_W))
			{
				m_Delay += _FTime->GetEngineFixedDeltaTimeSec();

				if (m_PreserveFinish == false && _FAudio->FIsPlaying(OBJECT_SWITCH_1) == false)
				{
					_FAudio->FPlaySound(OBJECT_SWITCH_1);
					//_FAudio->FPlaySound(ANN_INTERACTION_PRESERVE);

					m_PreserveFinish = true;
				}

				if (m_Delay >= 2.0f)
				{
					if (m_PreserveFinish == true)
					{
						_FAudio->FPlaySound(ANN_INTERACTION_START);
						m_Delay = 0;
					}
				}

				m_pSprite->StartAnimation();
				SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_IsInteraction = true;
				m_InteractionTime += _FTime->GetObjectFixedDeltaTimeSec();
			}
			else
			{
				/*SetInput(false);*/
				m_pSprite->StopAnimation();
				SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_IsInteraction = false;
			}
		}
		else
		{
			m_PreserveFinish = false;
		}
	}
	else
	{
		SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_IsInteraction = false;

		m_Delay += _FTime->GetEngineFixedDeltaTimeSec();

		if (m_Delay >= 3.0f)
		{
			_FAudio->FPlaySound(OBJECT_SWITCH_0);
			m_Delay = 0.f;
		}
		if (m_Gate->GetComponent<Gate>()->IsOpen() == false)
		{
			m_Gate->GetComponent<Gate>()->SetOpen();
		}
	}
}

void Switch::OnRender()
{
	D2D1_POINT_2F point = m_GameObject->GetPos();
	D2D1_SIZE_F size = D2D1::SizeF(TILE_SIZE * 2.5f, TILE_SIZE / 3);

	_GraphicEngine->D2DXDrawRectrangle(point.x - size.width / 2, point.y - (TILE_SIZE * 3.f) - size.height / 2, size.width, size.height, ColorF::Black, ColorF::WhiteSmoke, true);
	_GraphicEngine->D2DXDrawRectrangle(point.x - size.width / 2, point.y - (TILE_SIZE * 3.f) - size.height / 2, size.width * (m_InteractionTime / 3), size.height, ColorF::Black, ColorF::Yellow, true);
}

void Switch::Init()
{
	m_InteractionTime = 0.f;
	m_PreserveFinish = false;
	m_pSprite->m_SheetIndex = 0;
	m_pSprite->StopAnimation();
	m_pSprite->SetActive(true);
}

