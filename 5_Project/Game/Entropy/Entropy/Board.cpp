#include "GamePCH.h"
#include "Board.h"

void Board::Awake()
{
	this->m_GameObject->SetStringName("Board");
	this->m_GameObject->SetStringTag("Board");
	this->m_GameObject->SetPos(D2D1::Point2F(300, 350.f));
	this->m_GameObject->m_pTransform->SetScale(1.0f, 1.0f);


	//��Ʈ�� �̸��� ����
	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_T("Board.png"));

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		&m_pBitmap
	);
}



void Board::FixedUpdate()
{
	if (m_IsActive)
	{
		//�������� �����𸣴� �ϴ� ���ܵδ�.
	}
}

void Board::OnRender()
{
	if (m_IsActive)
	{
		D2DGraphics::GetInstance()->DrawBitmap
		(
			m_pBitmap,
			D2D1::Point2F(0.f, 0.f),
			D2D1::SizeF(m_pBitmap->GetPixelSize().width, m_pBitmap->GetPixelSize().height),
			D2D1::Point2F(m_GameObject->GetPos().x, m_GameObject->GetPos().y)
		);
	}
	
}
