#pragma once

class GameObject;
class FTime;


class GameManager
{
	static GameManager* m_instance;
	const WCHAR* m_szClassName = L"물고기엔진";
	const WCHAR* m_szTitle = L"엔진실행중";
	FLOAT m_InFontSize;//현재 게임의 전체 인게임 폰트
	HWND m_hwnd;//현재 윈도우핸들

public:
	float m_p1_x, m_p1_y;
	float m_target_x, m_target_y;

	FAudio* m_SoundTrack;



	EventExcuteSystem* m_pEventExcuteSystem;


public:
	GameObject* m_pTestGameObj1;
	GameObject* m_pTestGameObj2;
	

	//JSON파일을 저장할 벡터
	std::vector<CString> m_ResourceTxtNames;
	//싱글턴 전역포인터를 선언!
	static GameManager* GetInstance();
	FTime* enTime;

	void GetInput();
	
public:
	void Initialize(HINSTANCE& _hinst);
	void On_Upadate();
	void Off_Upadate();
	//도움말 혹은 디버깅 메뉴를 출력해주는 함수이다
	void HelpText();

	void GameProccess();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

