#pragma once
/// <summary>
/// UI �Ŵ����Դϴ�. �ַ� �÷��̾��� �ΰ��ӿ� �޴��� �̿�
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
	int _random_Arr_[3];		//ī���� ����Ȯ���� ������ �迭
	bool m_IsUIActive = false; //UI�� ����Ұ��ΰ��� ����UI
	bool m_IsLose = false;	   //�й踦 �˷��ִ�  ����UI
public:
	std::vector<ItemData> m_ItemData;	//�����۵��� ������ ����
	std::map<std::wstring , ID2D1Bitmap*> m_FBitmap; //UI�� ��Ʈ���� ������ ����
	std::vector<int> m_ItemType; //������ Ÿ���� ������ ����
	bool m_IsUpgrading = false;//�÷��̾��� ���׷��̵� ����UI
	bool m_IsStatus = false;   //�÷��̾��� �������ͽ� ����UI
	bool m_IsMaxBullet = false;   //�÷��̾��� �����Ѿ� ����UI
	bool m_IsUIOverloading = false;   //�÷��̾��� �����ε� ����UI
public:
	bool m_IsBossPannel = false;

public:
	//������Ʈ ��ü
	Player* m_PlayerStatus;     //�÷��̾��� ������ ���� ������
	Weapon* m_Weapon;           //������ ���� ������ ���� ������
	//Boss* m_BossStatus;			//������ ������ ���� ������;
	GameObject* m_OverloadingEffect;
	std::vector<Sprite*>	m_OverloadingEffectSprite;

public:
	//������ HP�г�
	float  Boss_MAX_HP = 3000;
	float  Boss_CURRENT_HP = Boss_MAX_HP;

	unsigned int Boss_Hp_Box[3];

	int m_line = 0;
	int m_wantLine = 1562;
	void HPBarCreate();
public:
	void Initialize();			//UI�ʱ�ȭ
public:
	// ���� UI���� �Լ����̴�.


	void CreateRandomCall(int _min, int _max);	//���� ��������..
	void CreateItem(int _index, std::wstring _BitmapName, std::wstring _Des);//������ ����
	void CheckButton(int _ItemType);
	void CheckUIDraw(float _posX, float _posY, float _width, float _height, D2D1::ColorF::Enum _TxtColor, bool _fill);

	//�׸��� �Լ�
	void DrawSelectPannel();
	void DrawToUIBitmapRandom(std::wstring _BitmapName, D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale);
	void DrawToUIText(float _posX, float _posY, const WCHAR* _Font, D2D1::ColorF::Enum _TxtColor,const WCHAR* _msg,...);	
	void DrawImage(D2D1_POINT_2F _Pos, D2D1_SIZE_F _Scale,int _select);
	void DrawSprite(D2D1_POINT_2F _Pos, D2D1_POINT_2F _printPos, D2D1_SIZE_F _Scale, int _select);
	

	void DrawBossPannel(int _posX, int _posY,int _Max);

public:
	//�÷��̾��� ������ ��Ÿ�� UI �Լ���
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

