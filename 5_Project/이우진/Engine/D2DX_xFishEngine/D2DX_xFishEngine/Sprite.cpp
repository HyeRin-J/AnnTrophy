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
/// �̹����� �ε��Ѵ�
/// �ε��Ҷ� �̹��� ����� �����س���,
/// �׸��� �� �̹��� ������� ���������Ѵ�.
/// </summary>
/// <param name="_path"></param>
/// <param name="_width"></param>
/// <param name="_height"></param>
void Sprite::LoadSprite(PCWSTR _path, float _width, float _height)
{
	//json���� �������� �پ��� ������ �ִµ�
	//�� ������ �ؽ�Ʈ�� ��Ʈ�� ���� �̸��� �����Ͽ� �������� ���ҽ��Ŵ����� �Լ��̴�.
	//���п� �׸��� �ȶ��� ���³��� �������̿���.
	std::wstring path(ResourceManager::GetInstance()->LoadFile(_path));
	
	if (path.size() != 0)
	{
		//�ش� �������� (���ϴ� ũ�⸸ �߸� ��Ʈ�� ����)��Ʈ�� ������ �����Ѵ�.
		//= �ִϸ��̼� �������
		m_SpriteSheets = ResourceManager::GetInstance()->m_SpritesData;
		//(������)��������Ʈ�� ��Ʈ���� �ε���
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
/// ��������Ʈ �̹����� ���ϱ��� ��ǥ.
/// �׸��°� ������Ʈ���� �����Ѵ�.
/// </summary>
/// <param name="_x">������ x��</param>
/// <param name="_y">������ y��</param>
void Sprite::SetPosition(Vector2 _pos)
{
	m_OriginPos.x = _pos.x;
	m_OriginPos.y = _pos.y;
}




void Sprite::Update(float _dtime)
{
	//isPlay�� ���ΰ�� 
	//��������Ʈ�� �ϳ��� �ִ°�쿡�� ����
	if (m_IsPlay == TRUE && m_SpriteSheets.size() > 0)
	{
		//�� �ð� �������� ����Ѵ�.
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
