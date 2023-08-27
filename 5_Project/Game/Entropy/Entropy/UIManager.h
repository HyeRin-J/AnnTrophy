#pragma once
/// <summary>
/// UI 매니저입니다. 주로 플레이어의 인게임용 메뉴를 이용
/// </summary>
/// 

#include "ItemData.h"

class UIManager : public SingletonManager<UIManager> 
{
private:
	int m_CurrentIndex;        
public:
	UIManager();
	~UIManager();
	int m_MaxBullet;

	int m_MaxUpgradeCount = 0;

	unsigned int m_BulletIndex;
	int _random_Arr_[3];		//카드의 랜덤확률을 결정할 배열
	bool m_IsUIActive = false; //UI를 사용할것인가의 여부UI
	bool m_IsLose = false;	   //패배를 알료주는  여부UI
public:
	std::vector<ItemData> m_ItemData;	//아이템들이 가지는 정보
	std::map<std::wstring , ID2D1Bitmap*> m_FBitmap; //UI의 비트맵을 저장할 벡터
	std::vector<int> m_ItemType; //아이템 타입을 저장할 벡터
	bool m_IsUpgrading = false;//플레이어의 업그레이드 여부UI
	bool m_IsStatus = false;   //플레이어의 스테이터스 여부UI
	bool m_IsMaxBullet = false;   //플레이어의 보일총알 여부UI
	bool m_IsUIOverloading = false;   //플레이어의 오버로딩 여부UI
public:
	bool m_IsBossPannel = false;

public:
	//컴포넌트 객체
	Player* m_PlayerStatus;     //플레이어의 정보를 담을 포인터
	Weapon* m_Weapon;           //무기의 대한 정보를 담을 포인터
	//Boss* m_BossStatus;			//보스의 정보를 담은 포인터;
	GameObject* m_OverloadingEffect;
	std::vector<Sprite*>	m_OverloadingEffectSprite;

public:
	//보스용 HP패널
	float  Boss_MAX_HP = 3000;
	float  Boss_CURRENT_HP = Boss_MAX_HP;

	unsigned int Boss_Hp_Box[3];

	int m_line = 0;
	int m_wantLine = 1562;
	void HPBarCreate();
public:
	void Initialize();			//UI초기화
public:
	// 게임 UI관련 함수들이다.


	void CreateRandomCall(int _min, int _max);	//랜덤 난수생성..
	void CreateItem(int _index, std::wstring _BitmapName, std::wstring _Des);//아이템 생성
	void CheckButton(int _ItemType);
	void CheckUIDraw(float _posX, float _posY, float _width, float _height, D2D1::ColorF::Enum _TxtColor, bool _fill);

	//그리기 함수
	void DrawSelectPannel();
	void DrawToUIBitmapRandom(std::wstring _BitmapName, D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale);
	void DrawToUIText(float _posX, float _posY, const WCHAR* _Font, D2D1::ColorF::Enum _TxtColor,const WCHAR* _msg,...);	
	void DrawImage(D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale,int _select);
	void DrawSprite(D2D1_POINT_2F _Pos, D2D1_POINT_2F _printPos, D2D1_SIZE_F _Scale, int _select);
	

	void DrawBossPannel(int _posX, int _posY,int _Max);

public:
	//플레이어의 정보를 나타낼 UI 함수들
	void DrawBulletPannel(int _posX, int _posY);
	void DrawOverloadingPannel(int _ImageSize,int _posX, int _posY);
	void DrawOverloadingEffectPannel(int _posX, int posY);
	void DrawStatusPannel(int _posX, int _posY);
	void DrawHealthPannel(int _Max);
public:
	void Update();
	void OpenUI();
	void CloseUI();
	void DrawLose();
public:
	void SetCurrentIndex(int _v) { m_CurrentIndex = _v; }
	int GetCurrentIndex() { return m_CurrentIndex; }
public:
	void Release();
};

