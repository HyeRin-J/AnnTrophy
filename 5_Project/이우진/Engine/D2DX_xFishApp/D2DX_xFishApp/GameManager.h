#pragma once

class GameObject;
class FTime;


class GameManager
{
	static GameManager* m_instance;
	const WCHAR* m_szClassName = L"����⿣��";
	const WCHAR* m_szTitle = L"����������";
	FLOAT m_InFontSize;//���� ������ ��ü �ΰ��� ��Ʈ
	HWND m_hwnd;//���� �������ڵ�

public:
	float m_p1_x, m_p1_y;
	float m_target_x, m_target_y;

	FAudio* m_SoundTrack;



	EventExcuteSystem* m_pEventExcuteSystem;


public:
	GameObject* m_pTestGameObj1;
	GameObject* m_pTestGameObj2;
	

	//JSON������ ������ ����
	std::vector<CString> m_ResourceTxtNames;
	//�̱��� ���������͸� ����!
	static GameManager* GetInstance();
	FTime* enTime;

	void GetInput();
	
public:
	void Initialize(HINSTANCE& _hinst);
	void On_Upadate();
	void Off_Upadate();
	//���� Ȥ�� ����� �޴��� ������ִ� �Լ��̴�
	void HelpText();

	void GameProccess();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

