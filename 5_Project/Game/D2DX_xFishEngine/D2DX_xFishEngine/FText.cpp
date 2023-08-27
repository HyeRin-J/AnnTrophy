#include "pch.h"
#include "framework.h"
#include "Vector.h"
#include "Object.h"
#include "Component.h"
#include "FText.h"

void FText::SetText(const WCHAR* _msg)
{
	m_wText = _msg;

	m_IsCheck = true;
}

void FText::SetTextDraw(float _posX, float _posY , const WCHAR* _Font,const WCHAR* _msg, D2D1::ColorF::Enum _TxtColor)
{
	m_wText = _msg;

	m_IsCheck = true;
	m_TxTBoxPos.x = _posX;
	m_TxTBoxPos.y = _posY;
	m_wFont = _Font;
	m_TxtColor = _TxtColor;
}

void FText::OnRender()
{
	if (m_IsCheck == true)
	{
		
		_GraphicEngine->D2DXDrawText(
			m_TxTBoxPos.x,//this->m_GameObject->GetPos().x,
			m_TxTBoxPos.y,//this->m_GameObject->GetPos().y,
			10,
			10,
			m_TxtColor,
			m_wFont, m_wText
		);
		//텍스트박스 위치 확인용 그리기
		_GraphicEngine->D2DXDrawRectrangle
		(
			m_TxTBoxPos.x,//this->m_GameObject->GetPos().x,
			m_TxTBoxPos.y,//this->m_GameObject->GetPos().y,
			m_TxTBoxSize.width,
			m_TxTBoxSize.height,
			D2D1::ColorF::White, D2D1::ColorF::White
		);

	}
}
