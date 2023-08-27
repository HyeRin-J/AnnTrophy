#pragma once

using namespace D2D1;

class Sprite;

class D2DGraphics : public SingletonManager<D2DGraphics>
{
public:
	HWND					m_hwnd;//�� ����ڵ�
	ID2D1Factory*			m_pFactory;//����Ʈ ���丮
	ID2D1HwndRenderTarget*	m_pRenderTarget;//����Ÿ��
	IWICImagingFactory*		m_pWICFactory;//�̹����� ���丮
	IWICBitmapFlipRotator*	m_pFlipRotator;	//�̹��� �ø���
	//���� ���� ����
	ID2D1SolidColorBrush* m_pPen;//�ܺλ�
	ID2D1SolidColorBrush* m_pBrush;//���� ��
	ID2D1SolidColorBrush* m_pTxtCol;//�ؽ�Ʈ ��


	IDWriteFactory*			m_pTxtFactory;//�ؽ�Ʈ�� ���丮
	IDWriteTextFormat*		m_pbText;//�ؽ�Ʈ�� ������ 
	
	//������ü font Ÿ��

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
	//  �̹����� �׷��� �Լ��� 
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

