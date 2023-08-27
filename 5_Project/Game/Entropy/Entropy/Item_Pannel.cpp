#include "GamePCH.h"
#include "Item_Pannel.h"



void Item_Pannel::Awake()
{
	this->m_GameObject->AddComponent<BoxCollider>();
	this->m_GameObject->SetStringName("Pannel");
	this->m_GameObject->SetStringTag("Pannel");
	this->m_GameObject->SetPos(D2D1::Point2F(100, 300.f));
	this->m_GameObject->m_pTransform->SetScale(1.0f, 1.0f);


	//비트맵 이름을 저장

	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_T("CBack.png"));

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		//L"../../Resource/Image/Sprite/.png"
		&m_pBitmap
	);

}
/// <summary>
/// 프레임이 갱신될 때 마다 처리되는 구문이다.
/// 
/// </summary>
void Item_Pannel::Update()
{
	Debug::LogFormat("itempannel 업데이트중");


	if (m_IsActive)
	{
		
	
		D2D1_POINT_2F mousePos = InputManager::GetMousePos(AppManager::GetInstance()->m_hwnd);
		
		
	}
	
}

void Item_Pannel::OnRender()
{
	if (m_IsActive)
	{
		D2DGraphics::GetInstance()->DrawBitmap
		(
			m_pBitmap,
			D2D1::Point2F(0.f, 0.f),
			D2D1::SizeF(m_pBitmap->GetPixelSize().width, m_pBitmap->GetPixelSize().height),
			D2D1::Point2F(this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y)
		);

		if (m_IsCheck == true)
		{
			m_hColor = D2D1::ColorF::Red;
		}
		else
		{
			m_hColor = D2D1::ColorF::Green;
		}
		D2DGraphics::GetInstance()->D2DXDrawRectrangle
		(
			this->m_GameObject->GetPos().x,
			this->m_GameObject->GetPos().y,
			m_pBitmap->GetPixelSize().width,
			m_pBitmap->GetPixelSize().height,
			m_hColor, D2D1::ColorF::White
		);
	}
	
}

