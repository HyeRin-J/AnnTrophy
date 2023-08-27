#include "pch.h"
#include "Vector2.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "D2DGraphics.h"
#include "SingletonManager.h"
#include "ResourceManager.h"

/// <summary>
/// 이미지를 로드한다
/// 로드할때 이미지 사이즈를 조정해놓고,
/// 그릴때 그 이미지 사이재로 나오도록한다.
/// </summary>
/// <param name="_path"></param>
/// <param name="_width"></param>
/// <param name="_height"></param>
void Sprite::LoadSprite(PCWSTR _path, float _width, float _height)
{
	//json파일 정보안의 다양한 정보가 있는데
	//그 수많은 텍스트중 비트맵 파일 이름만 추출하여 가져오는 리소스매니저의 함수이다.
	//덕분에 그림이 안떠서 보는내내 죽을맛이였다.
	std::wstring path(ResourceManager::GetInstance()->LoadFile(_path));
	
	if (path.size() != 0)
	{
		//해당 데이터의 (원하는 크기만 잘린 비트맵 정보)시트를 벡터의 저장한다.
		//= 애니메이션 정보재생
		m_SpriteSheets = ResourceManager::GetInstance()->m_SpritesData;
		//(나눠진)스프라이트의 비트맵을 로드함
		D2DGrahpics::GetInstance()->D2DLoadBitmap
		(
			D2DGrahpics::GetInstance()->m_pRenderTarget,
			D2DGrahpics::GetInstance()->m_pWICFactory,
			path.c_str(),
			(UINT)_width,
			(UINT)_height,
			&m_BitMap
		);
	}

	


	//m_SpriteSheets.push_back(nullptr);
}
void Sprite::SetPosition(float _x, float _y)
{
	m_OriginPos.x = _x;
	m_OriginPos.y = _y;
}
void Sprite::ToString()
{
}
/// <summary>
/// 스프라이트 이미지를 출하기전 좌표.
/// 그리는건 업데이트에서 진행한다.
/// </summary>
/// <param name="_x">생성될 x축</param>
/// <param name="_y">생성될 y축</param>
void Sprite::SetPosition(Vector2 _pos)
{
	m_OriginPos.x = _pos.x;
	m_OriginPos.y = _pos.y;
}




void Sprite::Update(float _dtime)
{
	//isPlay가 참인경우 
	//스프라이트가 하나라도 있는경우에만 실행
	if (m_IsPlay == TRUE && m_SpriteSheets.size() > 0)
	{
		//매 시간 프레임을 계산한다.
		static DWORD64 startCount = GetTickCount64();
		DWORD64 currCount = GetTickCount64();

		if ((currCount - startCount) / _dtime > m_SpriteSheets[m_SheetIndex].m_delay)
		{
			startCount = currCount;
			++m_SheetIndex %= m_SpriteSheets.size();
		}
		D2D1_SIZE_F size = m_BitMap->GetSize();

		D2DGrahpics::GetInstance()->DrawBitmap
		(
			D2D1::Point2F(m_OriginPos.x, m_OriginPos.y),
			m_SpriteSheets[m_SheetIndex],
			m_BitMap,
			D2D1::SizeF(1, 1),
			1.0f

		);
		
	}
}
