#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "D2DGraphics.h"



D2DGrahpics* D2DGrahpics::m_pInstance = nullptr;

D2DGrahpics* D2DGrahpics::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new D2DGrahpics();
	}
	return m_pInstance;
}

ID2D1HwndRenderTarget* D2DGrahpics::GetRenderTarget()
{

	return m_pRenderTarget;

}

D2DGrahpics::D2DGrahpics() :
	m_pTxtFactory(nullptr),
	m_hwnd(nullptr),
	m_pFactory(nullptr),
	m_pRenderTarget(nullptr),
	m_pbText(nullptr),
	m_pTxtCol(nullptr),
	m_pPen(nullptr),//외부색
	m_pBrush(nullptr)//내부 색
{




}

D2DGrahpics::~D2DGrahpics()
{
	SafeRelease(&m_pPen);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pTxtFactory);
	SafeRelease(&m_pbText);
}

HRESULT D2DGrahpics::Initalize(HWND& _hwnd)
{
	m_hwnd = _hwnd;
	HRESULT hr = S_OK;
	
	//찾아본 바로는 쓰레드를 만드는거라는데 .. 
	//정확히 어떤녀석인지는 모르겠다
	//싱글스레드를 사용하겠다는 의미같다
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
	{
		return -1;  // Fail CreateWindowEx.
	}

	RECT rc;
	GetClientRect(m_hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	hr = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, size),
		&m_pRenderTarget);


	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pPen);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pTxtCol);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);
	}

	const WCHAR msc_fontName[] = L"굴림";


	// Create a DirectWrite factory.
	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pTxtFactory),
		reinterpret_cast<IUnknown**>(&m_pTxtFactory)
	);

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pTxtFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_FontSize,
			L"EN-NUS", //locale
			&m_pbText
		);
	}

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&m_pWICFactory));

	return hr;
}

void D2DGrahpics::BeginRender()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

}
void D2DGrahpics::EndRender()
{
	m_pRenderTarget->EndDraw();
}



void D2DGrahpics::D2DXDrawRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board)
{
	if (m_pRenderTarget == NULL)
	{
		//검사
		return;
	}

	if (m_pRenderTarget != NULL)
	{
		m_pPen->SetColor(_border);
		m_pBrush->SetColor(_board);

		D2D1_RECT_F dRectF;

		dRectF = D2D1::RectF(
			_x, _y,
			_x + _width, _y + _height
		);
		//타입으로 결정하자..
		m_pRenderTarget->DrawRectangle(dRectF, m_pPen);
		//m_pRenderTarget->FillRectangle(dRectF, m_pBrush);

	}
}

void D2DGrahpics::D2DXDrawRoundRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board)
{
	if (m_pRenderTarget != NULL)
	{
		m_pPen->SetColor(_border);
		m_pBrush->SetColor(_board);
		;

		D2D1_RECT_F dRectF;

		dRectF = D2D1::RectF(
			_x, _y,
			_x * _width, _y * _height
		);

		D2D1_ROUNDED_RECT dRoundRect =
			dRoundRect = D2D1::RoundedRect(dRectF, 10.0f, 10.0f);//모서리 사이즈는 나중에 정하자


			//타입으로 결정하자..
		m_pRenderTarget->DrawRoundedRectangle(dRoundRect, m_pPen);

		//m_pRenderTarget->FillRectangle(dRectF, m_pBrush);

	}
}

void D2DGrahpics::D2DXDrawCircle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board)
{
	if (m_pRenderTarget != NULL)
	{
		m_pPen->SetColor(_border);
		m_pBrush->SetColor(_board);

		D2D1_ELLIPSE   ellipse;

		const float radius = min(_width / 2, _height, y / 2);

		//ellipse = D2D1::Ellipse(D2D1::Point2F(0, 0), radius, radius);
		ellipse = D2D1::Ellipse(D2D1::Point2F(_x, _y), radius, radius);

		//타입으로 결정하자..
		m_pRenderTarget->DrawEllipse(ellipse, m_pPen);

		//m_pRenderTarget->FillEllipse(ellipse, m_pBrush);

	}
}
//비트맵 이미지 불러오기 
void D2DGrahpics::D2DXDrawTextrue2D(float _x, float _y, float _width, float _height)
{

}

void D2DGrahpics::D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const wchar_t* msg, ...)
{
	m_pTxtCol->SetColor(_TxtColor);

	va_list ap;
	va_start(ap, msg);

	int len;

	len = _vscwprintf(msg, ap) + 1;
	wchar_t* buffer = new wchar_t[len];

	vswprintf_s(buffer, len, msg, ap);
	va_end(ap);

	D2D1_RECT_F dRectF = D2D1::RectF(_x, _y, _x*_width, _y * _height );

	//읽을 버퍼 /버퍼의 길이만큼 읽기, 출력할 텍스트 gdi핸들 , 출력위치 , 색상조정
	m_pRenderTarget->DrawTextW(buffer, wcslen(buffer), m_pbText,
		dRectF, m_pTxtCol);

	delete[] buffer;
}



void D2DGrahpics::D2DXDrawLine(float _start1, float _start2, float _end1, float _end2, D2D1::ColorF _lineCol, float _size, ID2D1StrokeStyle* _style)
{
	if (m_pRenderTarget != NULL)
	{
		m_pBrush->SetColor(_lineCol);

		m_pRenderTarget->DrawLine(Point2F(_start1, _start2), Point2F(_end1, _end2), m_pBrush, _size, _style);

	}

}

HRESULT D2DGrahpics::DX2DGraphicResource(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	HRESULT hr = S_OK;
	const D2D1_COLOR_F  color = D2D1::ColorF(r, g, b);
	ID2D1SolidColorBrush* pBrush;

	if (SUCCEEDED(hr))
	{
		HRESULT hr = S_OK;
		if (m_pRenderTarget == NULL)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			hr = m_pFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(m_hwnd, size),
				&m_pRenderTarget);

			if (SUCCEEDED(hr))
			{
				const D2D1_COLOR_F color = D2D1::ColorF(r, g, b);
				hr = m_pRenderTarget->CreateSolidColorBrush(color, &pBrush);

				m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &m_pPen);
				m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &m_pBrush);
				m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &m_pTxtCol);
			}
		}
		return hr;
	}

	return NULL;
}
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

HRESULT D2DGrahpics::LoadBitMapfromFile(ID2D1HwndRenderTarget* _pRenderTarget, 
	IWICImagingFactory* _pWICFactory, 
	PCWSTR uri,
	PCWSTR _resourceName, 
	PCWSTR _resourceType, 
	UINT _destinationWidth, 
	UINT _destinationHeight, 
	ID2D1Bitmap** _ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = _pWICFactory->CreateDecoderFromFilename
	(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	uri;
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = _pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (_destinationWidth != 0 || _destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (_destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationHeight) / static_cast<FLOAT>(originalHeight);
					_destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (_destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationWidth) / static_cast<FLOAT>(originalWidth);
					_destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = _pWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						_destinationWidth,
						_destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = _pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			_ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

HRESULT D2DGrahpics::D2DLoadBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;

	//경로?이미지 파일을 검색해서 이 
	//프레임을 ㅇㅣ 디코더 객체에 저장한다고 함 (feat.msdn)
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;


	HRESULT hr = pIWICFactory->CreateDecoderFromFilename
	(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);


	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize
		(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);

		if (SUCCEEDED(hr))
		{
			// Create a Direct2D bitmap from the WIC bitmap.
			hr = pRenderTarget->CreateBitmapFromWicBitmap
			(
				pConverter,
				NULL,
				ppBitmap
			);
		}
		SafeRelease(&pDecoder);
		SafeRelease(&pSource);
		SafeRelease(&pStream);
		SafeRelease(&pConverter);
		SafeRelease(&pScaler);
	}
		return hr;
}

void D2DGrahpics::DrawBitmap(ID2D1Bitmap* _bitMap, float x, float y)
{
	D2D1_SIZE_F size = _bitMap->GetSize();

	m_pRenderTarget->DrawBitmap(_bitMap,
		D2D1::RectF(x, y, (x + size.width), (y + size.height)),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(x, y, (x + size.width), (y + size.height))
	);
}

void D2DGrahpics::DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* pBitmap, D2D1_SIZE_F scale, float opacity)
{
	D2D1_POINT_2F centerPos = D2D1::Point2F(point.x, point.y);
	//ScaleTransform(scale, centerPos);

	// Draw a bitmap.
	m_pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			centerPos.x - data.m_Pivot.x,
			centerPos.y - data.m_Pivot.y,
			centerPos.x + (data.m_BitmapSize.width - data.m_Pivot.x),
			centerPos.y + (data.m_BitmapSize.height - data.m_Pivot.y)),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
			data.m_BitmapPos.x,
			data.m_BitmapPos.y,
			data.m_BitmapPos.x + data.m_BitmapSize.width,
			data.m_BitmapPos.y + data.m_BitmapSize.height
		));
	//IdentityTransform();
}

void D2DGrahpics::DrawSprite(Sprite* _Spr)
{

}



