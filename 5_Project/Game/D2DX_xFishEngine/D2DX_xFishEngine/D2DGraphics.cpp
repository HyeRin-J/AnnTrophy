#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "SingletonManager.h"
#include "D2DGraphics.h"
#include "Debug.h"

ID2D1HwndRenderTarget* D2DGraphics::GetRenderTarget()
{
	return m_pRenderTarget;
}

void D2DGraphics::D2DXCreateFontStyle(const WCHAR* _Font, float _Size)
{
	HRESULT hr = S_OK;
	IDWriteTextFormat* _TextFormat = nullptr;

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pTxtFactory->CreateTextFormat(
			_Font,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			_Size,
			L"EN-NUS", //locale
			&_TextFormat
		);
	}
	m_FontList.emplace(std::pair<const WCHAR*,IDWriteTextFormat*>(_Font, _TextFormat));
}

void D2DGraphics::D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const  WCHAR* _Font, const WCHAR* msg, ...)
{
	m_pTxtCol->SetColor(_TxtColor);

	std::map<const WCHAR*, IDWriteTextFormat*>::iterator k = m_FontList.find(_Font);

	if (m_FontList.find(_Font) == m_FontList.end())
	{
#ifdef _DEBUG
		Debug::LogFormat("문자열이 없습니다.\n");
#endif
		return;
	}
	else
	{
		if ((*k).second == nullptr)
		{
#ifdef _DEBUG
			Debug::LogFormat("텍스트 포맷이 없습니다.\n");
#endif
			return;
		}
		va_list ap;
		va_start(ap, msg);
		int len;
		len = _vscwprintf(msg, ap) + 1;
		WCHAR* buffer = new WCHAR[len];

		vswprintf_s(buffer, len, msg, ap);
		va_end(ap);

		D2D1_RECT_F dRectF = D2D1::RectF(_x, _y, _x * _width, _y * _height);
		//읽을 버퍼 /버퍼의 길이만큼 읽기, 출력할 텍스트 gdi핸들 , 출력위치 , 색상조정
		m_pRenderTarget->DrawTextW(buffer, wcslen(buffer), (*k).second, dRectF, m_pTxtCol);
		delete[] buffer;
	}
}

D2DGraphics::D2DGraphics() :
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

D2DGraphics::~D2DGraphics()
{
	m_FontList.clear();
	SafeRelease(&m_pPen);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pTxtFactory);
	SafeRelease(&m_pbText);
}

HRESULT D2DGraphics::Initalize(HWND& _hwnd)
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
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		D2D1::HwndRenderTargetProperties(m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget);


	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pPen);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pTxtCol);
		m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);
	}

	const WCHAR msc_font_GuRoonda[] = L"굴림";
	const WCHAR msc_font_Maple[] = L"메이플스토리";
	const WCHAR msc_font_JangGrae[] = L"빙그레 싸만코체";
	m_FontSize[0] = 12;
	m_FontSize[1] = 13;
	m_FontSize[2] = 14;

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pTxtFactory),
		reinterpret_cast<IUnknown**>(&m_pTxtFactory)
	);


	//잠시 테스트용으로 이렇게 하겠습니다 ㅎㅎ
	//
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pTxtFactory->CreateTextFormat(
			msc_font_GuRoonda,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_FontSize[0],
			L"EN-NUS", //locale
			&m_FontTextFormat[0]
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pTxtFactory->CreateTextFormat(
			msc_font_Maple,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_FontSize[1],
			L"EN-NUS", //locale
			&m_FontTextFormat[1]
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pTxtFactory->CreateTextFormat(
			msc_font_JangGrae,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_FontSize[2],
			L"EN-NUS", //locale
			&m_FontTextFormat[2]
		);
	}


	/*if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
				D2D1::Point2F(100, 0),
				D2D1::Point2F(100, 200)),
			D2D1::BrushProperties(),
			pGradientStops,
			&m_pBrush
		);
		pGradientStops->Release();
	}*/


	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&m_pWICFactory));

	return hr;
}

void D2DGraphics::BeginRender()
{
	m_pRenderTarget->BeginDraw();
	//m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White, 0.5f));

}
void D2DGraphics::EndRender()
{
	m_pRenderTarget->EndDraw();
}



void D2DGraphics::D2DXDrawRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board, bool isFill)
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
		if (isFill == true)
		{
			m_pRenderTarget->FillRectangle(dRectF, m_pBrush);
		}
		m_pRenderTarget->DrawRectangle(dRectF, m_pPen);

	}
}

void D2DGraphics::D2DXDrawRoundRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board)
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

void D2DGraphics::D2DXDrawCircle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board)
{
	if (m_pRenderTarget != NULL)
	{
		m_pPen->SetColor(_border);
		m_pBrush->SetColor(_board);

		D2D1_ELLIPSE   ellipse;

		const float radius = min(_width, _height);

		//ellipse = D2D1::Ellipse(D2D1::Point2F(0, 0), radius, radius);
		ellipse = D2D1::Ellipse(D2D1::Point2F(_x, _y), radius, radius);

		//타입으로 결정하자..
		m_pRenderTarget->DrawEllipse(ellipse, m_pPen);

		//m_pRenderTarget->FillEllipse(ellipse, m_pBrush);

	}
}

void D2DGraphics::D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const WCHAR* msg, ...)
{
	m_pTxtCol->SetColor(_TxtColor);

	va_list ap;
	va_start(ap, msg);

	int len;

	len = _vscwprintf(msg, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, msg, ap);
	va_end(ap);

	D2D1_RECT_F dRectF = D2D1::RectF(_x, _y, _x * _width, _y * _height);

	//읽을 버퍼 /버퍼의 길이만큼 읽기, 출력할 텍스트 gdi핸들 , 출력위치 , 색상조정
	m_pRenderTarget->DrawTextW(buffer, wcslen(buffer), m_FontTextFormat[0],
		dRectF, m_pTxtCol);

	delete[] buffer;
}




void D2DGraphics::D2DXDrawLine(float _start1, float _start2, float _end1, float _end2, D2D1::ColorF _lineCol, float _size)
{
	if (m_pRenderTarget != NULL)
	{
		m_pBrush->SetColor(_lineCol);

		m_pRenderTarget->DrawLine(Point2F(_start1, _start2), Point2F(_end1, _end2), m_pBrush, _size);

	}

}

HRESULT D2DGraphics::DX2DGraphicResource(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
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

HRESULT D2DGraphics::LoadBitMapfromFile
(

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

	hr = m_pWICFactory->CreateDecoderFromFilename
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
		hr = m_pWICFactory->CreateFormatConverter(&pConverter);
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

				hr = m_pWICFactory->CreateBitmapScaler(&pScaler);
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
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
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

HRESULT D2DGraphics::D2DLoadBitmap(PCWSTR uri, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;

	//경로?이미지 파일을 검색해서 이 
	//프레임을 ㅇㅣ 디코더 객체에 저장한다고 함 (feat.msdn)
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;


	HRESULT hr = m_pWICFactory->CreateDecoderFromFilename
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
		hr = m_pWICFactory->CreateFormatConverter(&pConverter);

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
			hr = m_pRenderTarget->CreateBitmapFromWicBitmap
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

void D2DGraphics::DrawBitmap(ID2D1Bitmap* _bitMap, float x, float y, float opacity)
{
	if (_bitMap == nullptr) return;

	D2D1_SIZE_F size = _bitMap->GetSize();
	D2D1_PIXEL_FORMAT format =	_bitMap->GetPixelFormat();

	m_pRenderTarget->DrawBitmap(_bitMap,
		D2D1::RectF(x, y, (x + size.width), (y + size.height)),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(x, y, (x + size.width), (y + size.height))
	);
}

void D2DGraphics::DrawBitmap(ID2D1Bitmap* _bitMap, D2D1_POINT_2F pos, D2D1_SIZE_F size, D2D1_POINT_2F outPos)
{
	if (_bitMap == nullptr) return;

	m_pRenderTarget->DrawBitmap(
		_bitMap,
		D2D1::RectF(
			outPos.x,
			outPos.y,
			outPos.x + size.width,
			outPos.y + size.height
		),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + size.width,
			pos.y + size.height));
}

void D2DGraphics::DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* pBitmap, D2D1_SIZE_F scale, float opacity)
{
	D2D1_POINT_2F leftPos = D2D1::Point2F(point.x - (data.m_Pivot.x * (scale.width / data.m_BitmapSize.width)),
		point.y - (data.m_Pivot.y * (scale.height / data.m_BitmapSize.height)));
	//ScaleTransform(scale, centerPos);

	// Draw a bitmap.
	m_pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			leftPos.x,
			leftPos.y,
			leftPos.x + scale.width,
			leftPos.y + scale.height),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
			data.m_BitmapPos.x,
			data.m_BitmapPos.y,
			data.m_BitmapPos.x + data.m_BitmapSize.width,
			data.m_BitmapPos.y + data.m_BitmapSize.height
		));
	//IdentityTransform();
}

void D2DGraphics::DrawSprite(ID2D1Bitmap* _bitMap, D2D1_POINT_2F pos, D2D1_SIZE_F size, D2D1_POINT_2F outPos)
{
	m_pRenderTarget->DrawBitmap(
		_bitMap,
		D2D1::RectF(
			outPos.x,
			outPos.y,
			outPos.x+ size.width,
			outPos.y+size.height
		),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
			pos.x,
			pos.y,
			outPos.x + size.width,
			outPos.y + size.height));
}

void D2DGraphics::Blend(ID2D1Bitmap* _bitmap1, ID2D1Bitmap* _bitmap2, float time)
{
	
	DrawBitmap(_bitmap1, 0, 0, time);
	DrawBitmap(_bitmap2, 0, 0, 0.6f - time);
}
