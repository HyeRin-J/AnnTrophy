#pragma once
/// <summary>
/// 아이템의 데이터를 가진 구조체
/// </summary>
struct ItemData
{
	int m_Index;//n번째 아이템
	int m_Upgrade = 0;

	ID2D1Bitmap* m_Bitmap;//비트맵의 포인터
	std::wstring m_Name;//이미지 파일의 이름
	std::wstring m_Des;//추가 설명 및 기타사항의 문자열
	
	enum class UPGRADE
	{
		_NONE = 0,
		_DAMAGE,	 //기본 데미지 증가
		_MAX,		 //탄환 최대 개수 증가
		_SPEED,		 //공격 스피드 증가
		_LENGTH,	 //공격 사거리 증가
		_OVERLO		 //오버로딩 속도증가.
	};
	


};
