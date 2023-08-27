#include "GamePCH.h"
#include "ItemData.h"
#include "Item.h"




void Item::Awake()
{
	this->m_GameObject->SetStringName("_RandomItem");
	this->m_GameObject->SetStringTag("_RandomItem");

	m_GameObject->SetPos(D2D1::Point2F(500, 500));
	m_GameObject->SetScale(D2D1::SizeF(500, 500));

	//비트맵 이름을 저장

	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_T("YBack.png"));

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		//L"../../Resource/Image/Sprite/UIBackGround.png"
		&m_pBitmap
	);

}


void Item::FixedUpdate()
{
	if (m_IsActive)
	{
	}
}

void Item::OnRender()
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
