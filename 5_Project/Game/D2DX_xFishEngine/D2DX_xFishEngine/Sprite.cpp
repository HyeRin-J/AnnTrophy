#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteData.h"
#include "MapData.h"
#include "Sprite.h"
#include "SingletonManager.h"
#include "D2DGraphics.h"
#include "ResourceManager.h"
#include "framework.h"


void Sprite::Awake()
{

}

void Sprite::StopAnimation()
{
	m_IsPlaying = false;
	m_IsFinish = false;

	if (m_IsPlayOnce == true)
	{
		if (m_IsInversePlay == true)
			m_SheetIndex = m_SpriteSheets.size() - 1;
		else
			m_SheetIndex = 0;
	}
}

/// <summary>
/// �̹����� �ε��Ѵ�
/// �ε��Ҷ� �̹��� ����� �����س���,
/// �׸��� �� �̹��� ������� ���������Ѵ�.
/// </summary>
void Sprite::LoadSprite(PCWSTR _path, PCWSTR _folder)
{
	//json���� �������� �پ��� ������ �ִµ�
	//�� ������ �ؽ�Ʈ�� ��Ʈ�� ���� �̸��� �����Ͽ� �������� ���ҽ��Ŵ����� �Լ��̴�.
	//���п� �׸��� �ȶ��� ���³��� �������̿���.
	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_folder);
	path.append(_T("/"));

	std::wstring name = ResourceManager::GetInstance()->LoadFile(_path);

	path += name;

	if (name.size() != 0)
	{
		//�ش� �������� (���ϴ� ũ�⸸ �߸� ��Ʈ�� ����)��Ʈ�� ������ �����Ѵ�.
		//= �ִϸ��̼� �������
		m_SpriteSheets = ResourceManager::GetInstance()->m_SpritesData;
		//(������)��������Ʈ�� ��Ʈ���� �ε���

		D2DGraphics::GetInstance()->D2DLoadBitmap
		(
			path.c_str(),
			&m_BitMap
		);

	}
}

void Sprite::LoadSprite(PCWSTR _dataName, PCWSTR _imageName, PCWSTR _folder)
{
	std::wstring dataPath = PATH_IMAGE_UNI;
	dataPath += _T("data/");
	dataPath += _folder;
	dataPath += _T("/");
	dataPath += _dataName;

	std::wstring imagePath = PATH_IMAGE_UNI;
	imagePath += _T("Sprite/");
	imagePath += _folder;
	imagePath += _T("/");
	imagePath += _imageName;

	ResourceManager::GetInstance()->LoadFile(dataPath.c_str());
	m_SpriteSheets = ResourceManager::GetInstance()->m_SpritesData;
	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		imagePath.c_str(),
		&m_BitMap
	);
}


void Sprite::DrawOpenSprite(std::wstring _fileName)
{

	m_GameObject->m_pTransform->Rotate();
	m_GameObject->m_pTransform->Scale();

	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_fileName);

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		&m_BitMap
	);

	D2DGraphics::GetInstance()->DrawBitmap
	(
		m_BitMap,
		D2D1::Point2F(m_GameObject->GetPos().x, m_GameObject->GetPos().y),
		D2D1::SizeF(m_GameObject->GetScale().width, m_GameObject->GetScale().height),
		D2D1::Point2F(m_GameObject->GetPos().x, m_GameObject->GetPos().y)
	);
}


void Sprite::OnRender()
{
	//isPlay�� ���ΰ�� 
	//��������Ʈ�� �ϳ��� �ִ°�쿡�� ����
	m_GameObject->m_pTransform->Rotate();
	m_GameObject->m_pTransform->Scale();

	if (m_SpriteSheets.size() > 0)
	{
		if (m_IsPlaying == true)
		{
			//�� �ð� �������� ����Ѵ�.
			currTime += _FTime->GetEngineFixedDeltaTimeSec();
			if (m_IsInversePlay == true)
			{
				if (currTime - startTime > m_SpriteSheets[m_SheetIndex].m_delay)
				{
					startTime = 0;
					currTime = 0;

					if (--m_SheetIndex < 0)
					{
						if (m_IsPlayOnce == true)
						{
							m_IsFinish = true;
							m_IsPlaying = false;
							m_SheetIndex = 0;
						}
						else
						{
							m_SheetIndex = m_SpriteSheets.size() - 1;
						}
					}
				}
			}
			else
			{
				if (currTime - startTime > m_SpriteSheets[m_SheetIndex].m_delay)
				{
					startTime = 0;
					currTime = 0;

					if (++m_SheetIndex >= m_SpriteSheets.size())
					{
						if (m_IsPlayOnce == false)
						{
							m_SheetIndex = 0;				
						}
						else
						{
							m_IsFinish = true;
							m_IsPlaying = false;
							m_SheetIndex = m_SpriteSheets.size() - 1;
						}
					}
				}
			}
		}

		if (m_SheetIndex >= 0 && m_SheetIndex < m_SpriteSheets.size())
		{
			D2DGraphics::GetInstance()->DrawBitmap
			(
				m_BitMap,
				m_SpriteSheets[m_SheetIndex].m_BitmapPos,
				m_SpriteSheets[m_SheetIndex].m_BitmapSize,
				D2D1::Point2F(m_GameObject->GetPos().x - m_SpriteSheets[m_SheetIndex].m_Pivot.x,
					m_GameObject->GetPos().y - m_SpriteSheets[m_SheetIndex].m_Pivot.y)
			);
		}
	}

	m_GameObject->m_pTransform->SetIdentity();
}
