#include "pch.h"
#include "framework.h"
#include "Vector.h"
#include "Object.h"
#include "Component.h"
#include "Pannel.h"



void Pannel::SetLoadBitmap(std::wstring& _bitmapName)
{
	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("Sprite/"));
	path.append(_bitmapName);

	D2DGraphics::GetInstance()->D2DLoadBitmap
	(
		path.c_str(),
		&m_pBitmap
	);
	m_BitDraw = true;
	
	
}


/// <summary>
/// ��Ʈ���� ������ ������ ����
/// </summary>
/// <param name="_pos">��Ʈ���� ��ġ</param>
/// <param name="_center">�߰���</param>
void Pannel::SetPoint(D2D1_POINT_2F _pos, D2D1_SIZE_F _center )
{
	//this->m_GameObject->SetPos(_pos);

	//m_Center =
	//{
	//	m_pBitmap->GetPixelSize().width + m_GameObject->GetScale().width / 2,
	//	m_pBitmap->GetPixelSize().height + m_GameObject->GetScale().height / 2
	//};
	//this->m_GameObject->SetScale(_center);
	
}





void Pannel::GetCuserPosDraw(float _x, float _y, float _width, float _height)
{
	m_BOX.left = _x;
	m_BOX.top = _y;
	m_BOX.right = _width;
	m_BOX.bottom = _height;
}



void Pannel::OnRender()
{
	if (m_BitDraw)
	{
		_GraphicEngine->DrawBitmap
		(
			m_pBitmap,
			D2D1::Point2F(0.f, 0.f),
			D2D1::SizeF
			(
				m_pBitmap->GetPixelSize().width,//* this->m_GameObject->GetScale().width, 
				m_pBitmap->GetPixelSize().height//* this->m_GameObject->GetScale().height
			),
			//D2D1::Point2F(this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y)
			D2D1::Point2F(m_Pos.x, m_Pos.y)
		);

		if (m_IsCheck == true)
		{
			m_BitColor = D2D1::ColorF::Red;
		}
		else
		{
			m_BitColor = D2D1::ColorF::Green;
		}

		//��Ʈ�� ������ Ȯ�ο�
		D2DGraphics::GetInstance()->D2DXDrawRectrangle
		(
			m_Pos.x,//this->m_GameObject->GetPos().x,
			m_Pos.y,//this->m_GameObject->GetPos().y,
			m_pBitmap->GetPixelSize().width,//* this->m_GameObject->GetScale().width,
			m_pBitmap->GetPixelSize().height,//* this->m_GameObject->GetScale().height,
			m_BitColor, D2D1::ColorF::White
		);
		//Ŀ�� ��ġ Ȯ�ο� �׸���
		D2DGraphics::GetInstance()->D2DXDrawRectrangle
		(
			m_BOX.left,
			m_BOX.top,
			m_BOX.right,
			m_BOX.bottom,
			D2D1::ColorF::Blue, D2D1::ColorF::White
		);
	
	}

}


