#include "pch.h"
#include "SingletonManager.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"

RRYD2DEngine::RRYD2DEngine() :
	m_hwnd(NULL), m_pD2DFactory(NULL), m_pRenderTarget(NULL),
	m_pBrush(NULL), m_pDWriteFactory(NULL), m_pTextFormat(NULL), m_pWICFactory(NULL) { }

RRYD2DEngine::~RRYD2DEngine()
{
	SafeRelease(&m_pD2DFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pWICFactory);
}


HRESULT RRYD2DEngine::Initialize(HWND& hwnd)
{
	m_hwnd = hwnd;

	static const WCHAR msc_fontName[] = L"굴림";
	static const FLOAT msc_fontSize = 12;

	CoInitialize(0);

	// Create D2DFactory
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory)))
	{
		return -1;  // Fail CreateWindowEx.
	}

	if (SUCCEEDED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory))))
	{
		m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat);
	}

	CreateResource();

	return -1;
}

HRESULT RRYD2DEngine::CreateResource()
{
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	D2D1_SIZE_U size = SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	//CreateRender Target, property m_hwnd
	if (SUCCEEDED(m_pD2DFactory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget)))
	{
		// Create Brush, Color White
		IdentityTransform();
		m_pRenderTarget->CreateSolidColorBrush(
			ColorF(ColorF::White),
			&m_pBrush);
	}

	return CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
}


void RRYD2DEngine::BeginRender()
{
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	m_pRenderTarget->Resize(SizeU(rc.right - rc.left, rc.bottom - rc.top));

	if (!(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		// WM_PAINT BeginPaint()

		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear(m_BackGroundColor);
	}
}


void RRYD2DEngine::EndRender()
{
	// WM_PAINT EndPaint()
	IdentityTransform();
	HRESULT hr = m_pRenderTarget->EndDraw();
}

void RRYD2DEngine::DrawHollowRect(int xPos, int yPos, int width, int height, ColorF penColor, float strokeWidth, ID2D1StrokeStyle* style)
{
	m_pBrush->SetColor(penColor);

	/* 점선 만들기 예제
	float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };

	ID2D1StrokeStyle* m_pStrokeStyleCustomOffsetZero;

	m_pD2DFactory->CreateStrokeStyle(
		StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&m_pStrokeStyleCustomOffsetZero
	);
	*/
	RECT rc = { xPos, yPos, xPos + width, yPos + height };

	m_pRenderTarget->DrawRectangle(
		RectF(rc.left, rc.top, rc.right, rc.bottom), m_pBrush, strokeWidth, style
	);
}


void RRYD2DEngine::DrawFillRect(int xPos, int yPos, int width, int height, ColorF BrushColor)
{
	m_pBrush->SetColor(BrushColor);

	RECT rc = { xPos, yPos, xPos + width, yPos + height };

	m_pRenderTarget->FillRectangle(RectF(rc.left, rc.top, rc.right, rc.bottom), m_pBrush);
}


void RRYD2DEngine::DrawHollowRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, ColorF penColor, float strokeWidth, ID2D1StrokeStyle* style)
{
	m_pBrush->SetColor(penColor);

	/* 점선 만들기 예제
	float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };

	ID2D1StrokeStyle* m_pStrokeStyleCustomOffsetZero;

	m_pD2DFactory->CreateStrokeStyle(
		StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&m_pStrokeStyleCustomOffsetZero
	);
	*/
	RECT rc = { xPos, yPos, xPos + width, yPos + height };

	m_pRenderTarget->DrawRoundedRectangle(RoundedRect(RectF(rc.left, rc.top, rc.right, rc.bottom), xRadius, yRadius), m_pBrush, strokeWidth, style);
}

void RRYD2DEngine::DrawFillRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, ColorF BrushColor)
{
	m_pBrush->SetColor(BrushColor);

	RECT rc = { xPos, yPos, xPos + width, yPos + height };

	m_pRenderTarget->FillRoundedRectangle(RoundedRect(RectF(rc.left, rc.top, rc.right, rc.bottom), xRadius, yRadius), m_pBrush);
}

void RRYD2DEngine::DrawHollowEllipse(int xPos, int yPos, int xRadius, int yRadius, ColorF penColor, float strokeWidth, ID2D1StrokeStyle* style)
{
	m_pBrush->SetColor(penColor);

	m_pRenderTarget->DrawEllipse(Ellipse(Point2F(xPos, yPos), xRadius, yRadius), m_pBrush);
}

void RRYD2DEngine::DrawFillEllipse(int xPos, int yPos, int xRadius, int yRadius, ColorF BrushColor)
{
	m_pBrush->SetColor(BrushColor);

	m_pRenderTarget->FillEllipse(Ellipse(Point2F(xPos, yPos), xRadius, yRadius), m_pBrush);
}

void RRYD2DEngine::DrawLine(int x1, int y1, int x2, int y2, ColorF penColor, float strokeWidth, ID2D1StrokeStyle* style)
{
	m_pBrush->SetColor(penColor);

	m_pRenderTarget->DrawLine(Point2F(x1, y1), Point2F(x2, y2), m_pBrush, strokeWidth, style);
}

void RRYD2DEngine::PrintText(int x, int y, ColorF textColor, const WCHAR* pch, ...)
{
	m_pBrush->SetColor(textColor);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	//int nLen = lstrlenA(pch); 
	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		//RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
		RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
}

void RRYD2DEngine::LoadBitmapFromFile(PCWSTR path, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRESULT hr = m_pWICFactory->CreateDecoderFromFilename(
		path,
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
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}
}

void RRYD2DEngine::LoadResourceBitmap(PCWSTR resourceName, PCWSTR resourceType, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = m_pWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = m_pWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
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
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}
}

void RRYD2DEngine::DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* pBitmap, D2D1_SIZE_F scale, float opacity)
{
	// Retrieve the size of the bitmap.

	D2D1_POINT_2F centerPos = D2D1::Point2F(point.x, point.y);
	ScaleTransform(scale, centerPos);

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
	IdentityTransform();
}

Matrix3x2F RRYD2DEngine::TranslateTransform(D2D1_SIZE_F size)
{
	Matrix3x2F translate = Matrix3x2F::Translation(size);
	m_Transform = translate * m_Transform;
	m_pRenderTarget->SetTransform(translate);

	return translate;
}

Matrix3x2F RRYD2DEngine::RotateTransform(float angle, D2D1_POINT_2F center)
{
	Matrix3x2F rotate = Matrix3x2F::Rotation(angle, center);
	m_Transform = rotate * m_Transform;
	m_pRenderTarget->SetTransform(m_Transform);

	return rotate;
}

Matrix3x2F RRYD2DEngine::ScaleTransform(D2D1_SIZE_F size, D2D1_POINT_2F center)
{
	Matrix3x2F scale = Matrix3x2F::Scale(size, center);
	m_Transform = scale * m_Transform;
	m_pRenderTarget->SetTransform(m_Transform);

	return scale;
}

Matrix3x2F RRYD2DEngine::IdentityTransform()
{
	m_Transform = Matrix3x2F::Identity();

	m_pRenderTarget->SetTransform(m_Transform);

	return m_Transform;
}
