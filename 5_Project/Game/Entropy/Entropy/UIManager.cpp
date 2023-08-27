#include "GamePCH.h"
#include "SingletonManager.h"
#include "UIManager.h"


/// <summary>
/// 컴포넌트로 이쁘게 각자 그릴수 할려고했는데 
/// 그릴때 순서 보장이 안되는거같은데.. 이렇게 해야하나.. 개빡친당 ㅋㅋ루FIFO
/// </summary>
UIManager::UIManager() : m_IsUIActive(false)
{
	m_OverloadingEffect = ObjectFactory::CreateObject<GameObject>();


	WCHAR imageName[256] = _T("\0");
	m_OverloadingEffectSprite.push_back(m_OverloadingEffect->AddComponent<Sprite>());
	swprintf_s(imageName, _T("overloading_fx_0.png"));
	m_OverloadingEffectSprite[0]->LoadSprite(_T("overloading_fx.txt"), imageName, _T("overloading"));
	m_OverloadingEffectSprite[0]->SetStringTag("UI");

	m_OverloadingEffectSprite.push_back(m_OverloadingEffect->AddComponent<Sprite>());
	swprintf_s(imageName, _T("overloading_fx_1.png"));
	m_OverloadingEffectSprite[1]->LoadSprite(_T("overloading_fx.txt"), imageName, _T("overloading"));
	m_OverloadingEffectSprite[1]->SetStringTag("UI");

	m_OverloadingEffectSprite[0]->StopAnimation();
	m_OverloadingEffectSprite[0]->SetActive(false);
	m_OverloadingEffectSprite[1]->StopAnimation();
	m_OverloadingEffectSprite[1]->SetActive(false);
	//m_Round[1]->m_IsInversePlay = true;

}

UIManager::~UIManager()
{
	ObjectManager::GetInstance()->Destroy(&m_OverloadingEffect);
}



void UIManager::HPBarCreate()
{
	//			전체값의 몇 퍼센트는 얼마?를 구하는 공식
	//				   (전체값 * 퍼센트 / 100(백분율))
	unsigned int Line = Boss_MAX_HP * 0.225 / 100;//전체 백분율 중  해당%만 추출한다.
	//체력바가 까질 1줄

	unsigned int Result = 0;
	std::vector<int> conutBar;

	while (Result < Boss_MAX_HP)
	{
		Result += Line;
		conutBar.push_back(Line);
	}

	m_line = conutBar.size();
	conutBar.clear();

}
void UIManager::DrawBossPannel(int _posX, int _posY, int _Max)
{





	if (SceneObjectManager::GetInstance()->m_Boss != nullptr)
	{
		Boss_CURRENT_HP = SceneObjectManager::GetInstance()->m_Boss->GetComponent<Boss>()->m_Hp;
		Boss_MAX_HP = SceneObjectManager::GetInstance()->m_Boss->GetComponent<Boss>()->m_MaxHp;

		float amount = Boss_CURRENT_HP / (float)Boss_MAX_HP;


		//DrawSprite(D2D1::Point2F(0, 0), D2D1::Point2F(1000, 50), D2D1::SizeF(1.0f, 1.0f), 11);
		DrawSprite(D2D1::Point2F(0, 0), D2D1::Point2F(1120, 100), D2D1::SizeF(1.0f, 1.0f), 11);


		_GraphicEngine->DrawBitmap(
			m_ItemData[14].m_Bitmap,
			D2D1::Point2F(0, 0),
			D2D1::SizeF(m_ItemData[14].m_Bitmap->GetPixelSize().width * amount, m_ItemData[14].m_Bitmap->GetPixelSize().height),
			D2D1::Point2F(1280, 90));


#ifdef _DEBUG
		_GraphicEngine->D2DXDrawText(_posX + 500, _posY + 600, 10, 10, D2D1::ColorF::Red, L"궁서", L"BOSS LINE : %d", (short)m_line);
		_GraphicEngine->D2DXDrawText(_posX + 500, _posY + 650, 10, 10, D2D1::ColorF::Red, L"궁서", L"BOSS HP : %d", (short)Boss_CURRENT_HP);
#endif
	}
}
void UIManager::DrawOverloadingEffectPannel(int _posX, int posY)
{
	m_OverloadingEffect->SetPos(D2D1::Point2(_posX, posY));

}

void UIManager::DrawOverloadingPannel(int _ImageSize, int _posX, int _posY)
{
	float cnt = SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_OverloadingDelayDuration / 20.f;

	bool isOver = SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_IsOverloading;
	int indexNum = 18;

	if (GameManager::GetInstance()->m_CurrentState == 0)
	{
		indexNum = 18;
	}
	else
	{
		indexNum = 19;
	}

	_GraphicEngine->DrawBitmap(
		m_ItemData[indexNum].m_Bitmap,
		D2D1::Point2F(0, _ImageSize - (cnt < 1 ? _ImageSize * (1 - cnt) : _ImageSize)),
		D2D1::SizeF(_ImageSize, (cnt < 1 ? _ImageSize * (1 - cnt) : _ImageSize)),
		D2D1::Point2F(_posX, _posY + _ImageSize - (cnt < 1 ? _ImageSize * (1 - cnt) : _ImageSize
			)));

	if (isOver == true)
	{
		m_OverloadingEffectSprite[_GameManager->m_CurrentState ^ 0x01]->StopAnimation();
		m_OverloadingEffectSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
		m_OverloadingEffectSprite[_GameManager->m_CurrentState]->StartAnimation();
		m_OverloadingEffectSprite[_GameManager->m_CurrentState]->SetActive(true);
	}
	else
	{
		m_OverloadingEffectSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
		m_OverloadingEffectSprite[_GameManager->m_CurrentState ^ 0x01]->StopAnimation();
		m_OverloadingEffectSprite[_GameManager->m_CurrentState]->StopAnimation();
		m_OverloadingEffectSprite[_GameManager->m_CurrentState]->SetActive(false);
	}
}

void UIManager::DrawSelectPannel()
{
	if (m_IsUpgrading == true)
	{
		WCHAR imageName[256];
		DrawSprite(D2D1::Point2F(0, 0), D2D1::Point2F(0, 0), D2D1::SizeF(1.1f, 1), 0);

		//if(m_ItemData)
		for (int inx = 0; inx < (m_MaxUpgradeCount < 3 ? 3 : 5 - m_MaxUpgradeCount); inx++)
		{
			swprintf_s(imageName, _T("upgrade_card_%d.png"), _random_Arr_[inx]);

			DrawToUIBitmapRandom(imageName, D2D1::Point2F(307 + (inx * 469), 386), D2D1::SizeF(1.0f, 1.0f));
#ifdef _DEBUG
			_GraphicEngine->D2DXDrawText(307 + (inx * 469), 386, 10, 10, D2D1::ColorF::Red, _T("궁서"), _T("%d"), (short)inx);
			_GraphicEngine->D2DXDrawText(327 + (inx * 469), 436, 10, 10, D2D1::ColorF::Blue, _T("궁서"), _T("ItemIndex : %d"), (short)_random_Arr_[inx]);
			_GraphicEngine->D2DXDrawText(327 + (inx * 469), 436, 10, 10, D2D1::ColorF::Blue, _T("궁서"), _T("%s"), m_ItemData[_random_Arr_[inx]].m_Des.c_str());
#endif
		}
	}
}


void UIManager::DrawBulletPannel(int _posX, int _posY)
{
	DrawImage(D2D1::Point2F(_posX, _posY + 17), D2D1::SizeF(1.0f, 1.0f), 6);//빈바

	float width = 416 / m_MaxBullet;
	int index = (double)_GameManager->m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_CurrBulletIndex;


	DrawOverloadingPannel(110, _posX + 4, _posY + 18);

	//불렛 사이즈 가없으면 그리지 않는다.

	if (GameManager::GetInstance()->m_CurrentState == 0)
	{
		DrawImage(D2D1::Point2F(_posX + 100, _posY + 20), D2D1::SizeF((width / 416) * (m_MaxBullet - (index <= 0 ? 0 : index)), 1.0f), 10);//
	}
	else
	{
		DrawImage(D2D1::Point2F(_posX + 100, _posY + 20), D2D1::SizeF((width / 416) * (m_MaxBullet - (index <= 0 ? 0 : index)), 1.0f), 9);//
	}

	DrawImage(D2D1::Point2F(_posX - 30, _posY - 5), D2D1::SizeF(1.0f, 1.0f), 7);//테두리

	for (int i = 0; i < m_MaxBullet - 1; i++)
	{
		_GraphicEngine->D2DXDrawLine
		(
			(_posX + 100) + ((i + 1) * width),
			_posY + 30,
			(_posX + 100) + ((i + 1) * width),
			70,
			D2D1::ColorF::Black,
			0.5f
		);
	}
}

void UIManager::DrawStatusPannel(int _posX, int _posY)
{

	/*
	(1, _T("공격력 증가"));
	(2, _T("공격 사거리 증가"));
	(3, _T("공격속도 증가"));
	(4, _T("오버로딩 지속시간 증가"));
	(5, _T("탄알 최대개수 증가"));
	*/


	if (m_IsStatus == true)
	{
		DrawImage(D2D1::Point2F(_posX, _posY), D2D1::SizeF(1, 1), 15);

		for (auto& data : m_ItemData)
		{
			int TempPosX = { 0, };
			int TempPosY = 0;
			switch (data.m_Index)
			{
			case 1://공격력
				TempPosX = 311;//완
				TempPosY = 288;
				break;
			case 2://사거리
				TempPosX = 1220;
				TempPosY = 230;
				break;
			case 3://공속
				TempPosX = 174;//완
				TempPosY = 531;
				break;
			case 4://오버로딩
				TempPosX = 1266;
				TempPosY = 497;
				break;
			case 5://탄알 개수증가
				TempPosX = 1055;
				TempPosY = 710;
				break;
			}

			for (int i = 0; i < 5; i++)
			{
				if (data.m_Upgrade <= 3)
				{
					for (int inx = 0; inx < data.m_Upgrade; inx++)
					{
						DrawImage(D2D1::Point2F((_posX + TempPosX) + (inx * 45.0f), (_posY + TempPosY)), D2D1::SizeF(1.0f, 1.0f), 16);
					}
				}
			}
		}
		///
	}
}


void UIManager::CreateItem(int _index, std::wstring _BitmapName, std::wstring _Des)
{
	ID2D1Bitmap* _BitmapFile = nullptr;


	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/UI/"));
	path.append(_BitmapName);

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		&_BitmapFile
	);


	//아이템 데이터를 입력합니다.
	ItemData _ItemData;
	_ItemData.m_Index = _index;
	_ItemData.m_Bitmap = _BitmapFile;
	_ItemData.m_Name = _BitmapName;
	_ItemData.m_Des = _Des.c_str();

	_ItemData.m_Upgrade = 0;
	if (m_ItemType.size() < 5)
	{
		m_ItemType.push_back(_index);
#ifdef _DEBUG
		Debug::LogFormat("itemType: %d\n", (short)m_ItemType.size());
#endif
	}
	m_ItemData.push_back(_ItemData);
	m_FBitmap.emplace(std::pair<std::wstring, ID2D1Bitmap* >(_BitmapName, _BitmapFile));
}




void UIManager::DrawToUIBitmapRandom(std::wstring _BitmapName, D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale)
{
	for (int i = 1; i <= 5; i++)
	{
		auto data = m_ItemData[i];

		if (m_IsUIActive)
		{
			if (data.m_Name == _BitmapName)
			{
				if (data.m_Upgrade < 3)
				{
					_GraphicEngine->DrawBitmap
					(
						data.m_Bitmap,
						D2D1::Point2F(0.f, 0.f),
						D2D1::SizeF
						(
							data.m_Bitmap->GetPixelSize().width * _Scale.width,
							data.m_Bitmap->GetPixelSize().height * _Scale.height
						),
						_Pos
					);
					if (InputManager::InputKeyDown(VK_LBUTTON))
					{
						//Debug::LogFormat("마우스 입력인지됨\n");
						D2D1_POINT_2F mousePos = InputManager::GetMousePos(AppManager::GetInstance()->m_hwnd);

						if (InputManager::InputKeyDown(VK_LBUTTON))
						{

							if (data.m_Index != 0 &&
								mousePos.x > _Pos.x &&
								mousePos.x < _Pos.x + data.m_Bitmap->GetPixelSize().width * _Scale.width &&
								mousePos.y  >_Pos.y &&
								mousePos.y < _Pos.y + data.m_Bitmap->GetPixelSize().height * _Scale.height)
							{
								Debug::LogFormat("mousePos.x : %d \n mousePos.y : %d \n", (int)mousePos.x, (int)mousePos.y);
								CheckUIDraw
								(
									_Pos.x, _Pos.y, data.m_Bitmap->GetPixelSize().width * _Scale.width, data.m_Bitmap->GetPixelSize().height * _Scale.height, D2D1::ColorF::Red, false
								);
								CheckButton(data.m_Index);
							}
						}
						else if (InputManager::InputKeyUp(VK_LBUTTON))
						{
							Debug::LogFormat("mousePos.x : %d \n mousePos.y : %d \n", (int)mousePos.x, (int)mousePos.y);
							//Debug::LogFormat("LButtonUp !!\n");
							return;
						}
						else
						{
							CheckUIDraw
							(
								_Pos.x, _Pos.y, data.m_Bitmap->GetPixelSize().width * _Scale.width, data.m_Bitmap->GetPixelSize().height * _Scale.height, D2D1::ColorF::Red, false
							);
							CheckButton(data.m_Index);
						}
					}
					else if (InputManager::InputKeyUp(VK_LBUTTON))
					{
						//Debug::LogFormat("LButtonUp !!\n");
						return;
					}
					else
					{
						CheckUIDraw
						(
							_Pos.x, _Pos.y, data.m_Bitmap->GetPixelSize().width * _Scale.width, data.m_Bitmap->GetPixelSize().height * _Scale.height, D2D1::ColorF::Green, false
						);

					}
					//

				}
			}
		}
	}
}


void UIManager::DrawToUIText(float _posX, float _posY, const WCHAR* _Font, D2D1::ColorF::Enum _TxtColor, const WCHAR* _msg, ...)
{
#ifdef _DEBUG
	_GraphicEngine->D2DXDrawText
	(
		_posX,
		_posY,
		10,
		10,
		_TxtColor,
		_Font,
		_msg
	);
#endif
}


void UIManager::CheckUIDraw(float _posX, float _posY, float _width, float _height, D2D1::ColorF::Enum _TxtColor, bool _fill)
{
#ifdef _DEBUG
	_GraphicEngine->D2DXDrawRectrangle
	(
		_posX,
		_posY,
		_width,
		_height,
		_TxtColor,
		D2D1::ColorF::White,
		_fill
	);
#endif

}
void UIManager::CheckButton(int _ItemType)
{
	for (auto& data : m_ItemData)
	{
		if (data.m_Index == _ItemType)
		{
			const wchar_t* _msg = data.m_Des.c_str();

			int strSize = WideCharToMultiByte(CP_ACP, 0, _msg, -1, NULL, 0, NULL, NULL) + 1;
			LPSTR _tempChar = new char[strSize];
			WideCharToMultiByte(CP_ACP, 0, _msg, -1, _tempChar, strSize, 0, 0);

			if (data.m_Upgrade < 3)
			{
				data.m_Upgrade++;

				if (data.m_Upgrade >= 3)
				{
					m_MaxUpgradeCount++;
				}

#ifdef _DEBUG
				Debug::LogFormat("업그레이드 횟수 : %d (최대 3) \n", (int)data.m_Upgrade);
				Debug::LogFormat("클릭한 데이터 인덱스 : %d, 적응한 능력: %s , \n", (int)data.m_Index, _tempChar);
#endif
				//탄알 최대 개수 증가이다.
				if (data.m_Index == 5)
				{
					//총알 증가량

					if (m_MaxBullet < 10)
					{
						m_MaxBullet += 2;
					}

					SetCurrentIndex(data.m_Index);
					SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->Upgrade(GetCurrentIndex());
				}
			}
			else
			{
#ifdef _DEBUG

				Debug::LogFormat("업그레이드가 최대치입니다 : %d (최대 3) \n", (int)data.m_Upgrade);
				Debug::LogFormat("클릭한 데이터 인덱스 : %d, 적응한 능력: %s , \n", (int)data.m_Index, _tempChar);
#endif
			}
#ifdef _DEBUG
			Debug::LogFormat("현재 가져온 인덱스:: %d \n", (int)GetCurrentIndex());
#endif

		}
	}

	m_IsUpgrading = false;
}


void UIManager::Initialize()
{
	m_CurrentIndex = -1;
	m_MaxUpgradeCount = 0;

	m_IsUIActive = false;
	m_IsLose = false;
	ZeroMemory(_random_Arr_, sizeof(_random_Arr_));

	m_IsUpgrading = false;
	m_BulletIndex = -1;

	m_PlayerStatus = nullptr;
	m_Weapon = nullptr;
	//m_BossStatus = nullptr;

	//오브젝트의 이름을 부여하고 파일을 로드합니다.

	char ObjectName[256];
	WCHAR imageName[256];
	_random_Arr_[3] = { NULL, };

	m_ItemData.clear();

	//각자 어떤아이템의 어떤능력인지 설정하기 위해 .. 이렇게
	CreateItem(0, _T("reinforce_panel.png"), _T("보드이다"));
	CreateItem(1, _T("upgrade_card_1.png"), _T("공격력 증가"));
	CreateItem(2, _T("upgrade_card_2.png"), _T("공격 사거리 증가"));
	CreateItem(3, _T("upgrade_card_3.png"), _T("공격속도 증가"));
	CreateItem(4, _T("upgrade_card_4.png"), _T("오버로딩 지속시간 증가"));
	CreateItem(5, _T("upgrade_card_5.png"), _T("탄알 최대개수 증가"));



	CreateItem(6, _T("gauge_empty.png"), _T("배경 총알 받이다"));
	CreateItem(7, _T("gauge_border.png"), _T("배경 총알 테두리가  맞다"));

	CreateItem(8, _T("game_over.png"), _T(".놀랍게도 게임오버 창이다"));

	CreateItem(9, _T("bullet_red.png"), _T("순행 에너지다"));
	CreateItem(10, _T("bullet_blue.png"), _T("역행 에너지다"));

	CreateItem(11, _T("boss_hp.png"), _T("보스 체력바 선"));

	CreateItem(12, _T("hp_0.png"), _T("빈 하트객체"));
	CreateItem(13, _T("hp_1.png"), _T("찬 하트객체"));

	CreateItem(14, _T("boss_hp_bar.png"), _T("보스 체력게이지바 "));

	CreateItem(15, _T("stat_pannel.png"), _T("캐릭터 스테이터스 패널"));
	CreateItem(16, _T("stat_able.png"), _T("강화 수치 포인트"));
	CreateItem(17, _T("stat_back.png"), _T("스테이터스 패널 배경"));

	CreateItem(18, _T("overload_able_b.png"), _T("오버로딩 타입 "));
	CreateItem(19, _T("overload_able_r.png"), _T("오버로딩 타입 "));


	HPBarCreate();


	m_MaxBullet = _GameManager->m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->GetMaxBullet();
	//CheckButton(2);
}
/// <summary>
/// 단순히 이미지만 출력하는 함수이다.
/// </summary>
/// <param name="_Pos">위치</param>
/// <param name="_Scale">크기</param>
/// <param name="_select">찾아서 출력할 아이템 인덱스</param>


void UIManager::DrawHealthPannel(int _max)
{

	for (int inx = 0; inx < SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->m_MAX_HP; inx++)
	{
		DrawImage(D2D1::Point2(230 + (inx * 63), 121), D2D1::SizeF(1, 1), 12);//빈 하트
	}
	for (int inx = 0; inx < SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent<Player>()->Status.HP; inx++)
	{
		DrawImage(D2D1::Point2(230 + (inx * 63), 117), D2D1::SizeF(1, 1), 13);//빈 하트
	}
}

void UIManager::Update()
{
	m_IsUIOverloading = SceneObjectManager::GetInstance()->m_pPlayerObject->GetComponent < Player>()->m_Gun->GetComponent<Weapon>()->m_IsOverloading;

	if (m_IsUpgrading == false && InputManager::InputKeyDown(VK_TAB))
	{
		m_IsStatus = !m_IsStatus;

		if (m_IsStatus == true)
		{
			DrawStatusPannel(100, 500);
		}

		_FAudio->FPlaySound(UPGRADE_START);

		m_IsUIActive = !m_IsUIActive;

	}


	if (InputManager::InputKeyDown(VK_U))
	{
	//	m_IsBossPannel = !m_IsBossPannel;

		m_IsUpgrading = true;
	}

	if (/*InputManager::InputKeyDown(VK_TAB)*/ m_IsUpgrading == true)
	{
		if (m_IsUIActive == false)
		{
			CreateRandomCall(m_MaxUpgradeCount < 3 ? 3 : 5 - m_MaxUpgradeCount, 5);
			_FAudio->FPlaySound(UPGRADE_START);

			m_IsUIActive = true;
		}
	}

	if (m_IsStatus == false && m_IsUpgrading == false)
	{
		m_IsUIActive = false;
	}


	if (m_IsUIActive)
	{
		OpenUI();
	}
	else
	{
		CloseUI();
	}
}


void UIManager::OpenUI()
{
	_FTime->SetEngineDeltaTimeScale(0.f);
	_FTime->SetObjectDeltaTimeScale(0.f);
	//엔진타이머를 1로 시작함으로 게임을 진행시킨다.

}
void UIManager::CloseUI()
{
	_FTime->ResetEngineDeltatTimeScale();
	_FTime->ResetObjectDeltatTimeScale();
}

void UIManager::DrawLose()
{
	if (m_IsLose == true)
	{
		DrawImage(D2D1::Point2F(1000, 1000), D2D1::SizeF(1, 1), 8);
	}
}

void UIManager::Release()
{
	m_IsUIActive = false;
	m_ItemData.clear();
	m_FBitmap.clear();
}


//DrawBitmap과 달리 그리는 방식을 조금 틀리게함;
void UIManager::DrawImage(D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale, int _select)
{
	// 기본값은 8로 설정 8 = 패배 이미지.
	for (auto& data : m_ItemData)
	{
		if (data.m_Index == _select)
		{
			_GraphicEngine->DrawBitmap
			(
				data.m_Bitmap,
				D2D1::Point2F(0.f, 0.f),
				D2D1::SizeF
				(
					data.m_Bitmap->GetPixelSize().width * _Scale.width,
					data.m_Bitmap->GetPixelSize().height * _Scale.height
				),
				_Pos
			);
		}
	}
}
void UIManager::DrawSprite(D2D1_POINT_2F _Pos, D2D1_POINT_2F _printPos, D2D1_SIZE_F _Scale, int _select)
{
	// 기본값은 8로 설정 8 = 패배 이미지.
	for (auto& data : m_ItemData)
	{
		if (data.m_Index == _select)
		{
			_GraphicEngine->DrawBitmap
			(
				data.m_Bitmap,
				D2D1::Point2F(_Pos.x, _Pos.y),
				D2D1::SizeF
				(
					data.m_Bitmap->GetPixelSize().width + _Scale.width,
					data.m_Bitmap->GetPixelSize().height + _Scale.height
				),
				_printPos
			);
		}
	}
}


void UIManager::CreateRandomCall(int _min, int _max)
{
	srand((unsigned int)time(nullptr));

	unsigned int _random_cnt_ = 0;
	//중복없는 랜덤 난수를 생성하는 구문입니다.
	for (int inx_a = 0; inx_a < _min; inx_a++)
	{
		do
		{
			unsigned int _random_cnt_ = rand() % _max + 1;
			_random_Arr_[inx_a] = _random_cnt_;
		} while (m_ItemData[_random_Arr_[inx_a]].m_Upgrade >= 3);

		for (int inx_b = 0; inx_b < inx_a; inx_b++)
		{
			if (_random_Arr_[inx_a] == _random_Arr_[inx_b])
			{
				//같을경우 다시연산
				inx_a--;
				break;
			}
		}

	}
}
