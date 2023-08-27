#pragma once


#include "SpriteData.h"
using namespace D2D1;


class Sprite;


class D2DGrahpics
{
	//�̱��� ����
public:
	static D2DGrahpics* m_pInstance;
public:
	static D2DGrahpics* GetInstance();

public:
	HWND m_hwnd;//�� ����ڵ�
	ID2D1Factory* m_pFactory;//����Ʈ ���丮
	ID2D1HwndRenderTarget* m_pRenderTarget;//����Ÿ��

	IDWriteFactory* m_pTxtFactory;//�ؽ�Ʈ�� ���丮
	IDWriteTextFormat* m_pbText;//�ؽ�Ʈ�� ������ 

	IWICImagingFactory* m_pWICFactory;//�̹����� ���丮


	//�������� ����

	ID2D1SolidColorBrush* m_pPen;//�ܺλ�
	ID2D1SolidColorBrush* m_pBrush;//���� ��

	ID2D1SolidColorBrush* m_pTxtCol;//�ؽ�Ʈ ��

public:
	ID2D1HwndRenderTarget* GetRenderTarget();
	IDWriteTextFormat* GetTxtFactory() { return m_pbText; }
	void SetTxtFactory(IDWriteTextFormat* _write) { m_pbText = _write; }
	float m_FontSize = 12;


public:
	D2DGrahpics();
	~D2DGrahpics();
public:
	HRESULT Initalize(HWND& _hwnd);
	void BeginRender();
	void EndRender();

public:
	//  �̹����� �׷��� �Լ��� 

	void D2DXDrawTextrue2D(float _x, float _y, float _width, float _height);

	void D2DXDrawRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board);

	void D2DXDrawRoundRectrangle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board);

	void D2DXDrawCircle(float _x, float _y, float _width, float _height, D2D1::ColorF _border, D2D1::ColorF _board);

	void D2DXDrawText(float _x, float _y, float _width, float _height, D2D1::ColorF _TxtColor, const wchar_t* msg, ...);

	
	void D2DXDrawLine(float _start1, float _start2, float _end1, float _end2, D2D1::ColorF _lineCol, float _size, ID2D1StrokeStyle* _style);

	HRESULT DX2DGraphicResource(FLOAT r, FLOAT g, FLOAT b, FLOAT a);

	
	ID2D1Bitmap* m_mBit;

	HRESULT LoadBitMapfromFile
	(
		ID2D1HwndRenderTarget* _pRenderTarget, 
		IWICImagingFactory* _pWICFactory,
		PCWSTR uri, 
		PCWSTR _resourceName,
		PCWSTR _resourceType, 
		UINT _destinationWidth, 
		UINT _destinationHeight, 
		ID2D1Bitmap** _ppBitmap
	);

	HRESULT D2DLoadBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap);

	void DrawBitmap(ID2D1Bitmap* _bitMap, float x, float y);
	void DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* pBitmap, D2D1_SIZE_F scale, float opacity);
	void DrawSprite(Sprite* _Spr);


	// �ٷ� �̹��� ������ �ϳ� �д� ����


	// ��������Ʈ ���
	// ���� ��ġ ���� ������ ������ �����̸� ������ �ִ�.
	



};

