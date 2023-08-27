#pragma once

using namespace D2D1;

class Sprite;

class D2DGraphics : public SingletonManager<D2DGraphics>
{
public:
	HWND					m_hwnd;//주 멤버핸들
	ID2D1Factory*			m_pFactory;//디폴트 팩토리
	ID2D1HwndRenderTarget*	m_pRenderTarget;//렌더타겟
	IWICImagingFactory*		m_pWICFactory;//이미지용 팩토리
	IWICBitmapFlipRotator*	m_pFlipRotator;	//이미지 플립용
	//도형 색깔 지정
	ID2D1SolidColorBrush* m_pPen;//외부색
	ID2D1SolidColorBrush* m_pBrush;//내부 색
	ID2D1SolidColorBrush* m_pTxtCol;//텍스트 색


	IDWriteFactory*			m_pTxtFactory;//텍스트용 팩토리
	IDWriteTextFormat*		m_pbText;//텍스트용 포인터 
	
	//게임전체 font 타입

public:
	ID2D1HwndRenderTarget* GetRenderTarget();


public:
	FLOAT m_FontSize[3];
	IDWriteTextFormat* m_FontTextFormat[3];

	std::map<const WCHAR*, IDWriteTextFormat*> m_FontList;
	void D2DXCreateFontStyle(const WCHAR* _Font , float _Size);
	void D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const  WCHAR* _Font ,const WCHAR* msg, ...);

public:
	D2DGraphics();
	~D2DGraphics();
public:
	HRESULT Initalize(HWND& _hwnd);
	void BeginRender();
	void EndRender();
public:
	//  이미지를 그려줄 함수들 
	void D2DXDrawRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board, bool isFill = false);
	void D2DXDrawRoundRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board);
	void D2DXDrawCircle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board);
	void D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const WCHAR* msg, ...);
	
	void D2DXDrawLine(float _start1, float _start2, float _end1, float _end2, D2D1::ColorF _lineCol, float _size);

	HRESULT DX2DGraphicResource(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
	ID2D1Bitmap* m_mBit;

	HRESULT LoadBitMapfromFile
	(
		PCWSTR uri, 
		PCWSTR _resourceName,
		PCWSTR _resourceType, 
		UINT _destinationWidth, 
		UINT _destinationHeight, 
		ID2D1Bitmap** _ppBitmap
	);

	HRESULT D2DLoadBitmap
	(
		PCWSTR uri,
		ID2D1Bitmap** ppBitmap
	);

public:
	void DrawBitmap(ID2D1Bitmap* _bitMap, float x, float y, float opacity = 1.f);
	void DrawBitmap(ID2D1Bitmap* _bitMap, D2D1_POINT_2F pos, D2D1_SIZE_F size, D2D1_POINT_2F outPos);
	void DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* pBitmap, D2D1_SIZE_F scale, float opacity);
	void DrawSprite(ID2D1Bitmap* _bitMap, D2D1_POINT_2F pos, D2D1_SIZE_F size, D2D1_POINT_2F outPos);
	void Blend(ID2D1Bitmap* _bitmap1, ID2D1Bitmap* _bitmap2, float time);
public:
	HRESULT CreateTxT(WCHAR& _FontName, FLOAT& _Size, IDWriteTextFormat*& _IDWTextFormat, const wchar_t* _fontType);

};

