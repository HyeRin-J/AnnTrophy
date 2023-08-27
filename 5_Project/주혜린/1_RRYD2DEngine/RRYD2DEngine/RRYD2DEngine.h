#pragma once

using namespace D2D1;
class GameObject;

class RRYD2DEngine : public SingletonManager<RRYD2DEngine>
{
public:
	RRYD2DEngine();
	~RRYD2DEngine();

	/// <summary>
	/// ������ �ʱ�ȭ�մϴ�
	/// </summary>
	/// <param name="hwnd">���� ������ �ڵ�</param>
	/// <returns>���</returns>
	HRESULT Initialize(HWND& hwnd);

	/// <summary>
	/// ���ҽ� �ڿ����� �����մϴ�
	/// </summary>
	/// <returns> ��� </returns>
	HRESULT CreateResource();

	/// <summary>
	/// ������ ����
	/// </summary>
	void BeginRender();

	/// <summary>
	/// �������� ������
	/// </summary>
	void EndRender();

	/// <summary>
	/// ���ΰ� ����ִ� �簢���� �׸���
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="penColor">�׵θ� ����</param>
	/// <param name="strokeWidth">�׵θ� �β�</param>
	/// <param name="style">�׵θ� ��Ÿ�� https://docs.microsoft.com/en-us/windows/win32/api/d2d1/nn-d2d1-id2d1strokestyle </param>
	void DrawHollowRect(int xPos, int yPos, int width, int height, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// ���ΰ� ä���� �簢���� �׸���
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="BrushColor">Rect Color</param>
	void DrawFillRect(int xPos, int yPos, int width, int height, D2D1::ColorF BrushColor);

	/// <summary>
	/// ���ΰ� ����ִ� �ձ� �簢���� �׸���
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="xRadius">�𼭸� x ������</param>
	/// <param name="yRadius">�𼭸� y ������</param>
	/// <param name="penColor">�� ũ��</param>
	/// <param name="strokeWidth">�׵θ� �β�</param>
	/// <param name="style">�׵θ� ��Ÿ��</param>
	void DrawHollowRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// ���ΰ� ä���� �ձ� �簢���� �׸���
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="xRadius">�𼭸� x ������</param>
	/// <param name="yRadius">�𼭸� y ������</param>
	/// <param name="BrushColor">�簢�� ���� ����</param>
	void DrawFillRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, D2D1::ColorF BrushColor);

	/// <summary>
	/// ���ΰ� ����ִ� Ÿ���� �׸���
	/// </summary>
	/// <param name="xPos">Ÿ�� �߽� x Pos</param>
	/// <param name="yPos">Ÿ�� �߽� y Pos</param>
	/// <param name="xRadius">x�� ������</param>
	/// <param name="yRadius">y�� ������</param>
	/// <param name="penColor">�׵θ� ����</param>
	/// <param name="strokeWidth">�׵θ� �β�</param>
	/// <param name="style">�׵θ� ��Ÿ�� https://docs.microsoft.com/en-us/windows/win32/api/d2d1/nn-d2d1-id2d1strokestyle </param>
	void DrawHollowEllipse(int xPos, int yPos, int xRadius, int yRadius, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);


	/// <summary>
	/// ���ΰ� ä���� Ÿ���� �׸���
	/// </summary>
	/// <param name="xPos">Ÿ�� �߽� x Pos</param>
	/// <param name="yPos">Ÿ�� �߽� y Pos</param>
	/// <param name="xRadius">x�� ������</param>
	/// <param name="yRadius">y�� ������</param>
	/// <param name="BrushColor">Ÿ�� ����</param>
	void DrawFillEllipse(int xPos, int yPos, int xRadius, int yRadius, D2D1::ColorF BrushColor);

	/// <summary>
	/// ���� �׸���
	/// </summary>
	/// <param name="x1">start xPos</param>
	/// <param name="y1">start yPos</param>
	/// <param name="x2">end xPos</param>
	/// <param name="y2">end yPos</param>
	/// <param name="penColor">�� ����</param>
	/// <param name="strokeWidth">�� �ʺ�</param>
	/// <param name="style">���� ��Ÿ��</param>
	void DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// �ؽ�Ʈ ���
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="textColor"></param>
	/// <param name="pch"></param>
	void PrintText(int x, int y, D2D1::ColorF textColor, const WCHAR* pch, ...);

	/// <summary>
	/// ���Ϸκ��� �̹����� �ҷ��´�
	/// </summary>
	/// <param name="path">�̹����� �ҷ��� ���</param>
	/// <param name="ppBitmap">Bitmap ����������</param>
	void LoadBitmapFromFile(PCWSTR path, ID2D1Bitmap** ppBitmap);

	/// <summary>
	/// ���ҽ��κ��� �̹����� �ҷ��´�
	/// </summary>
	/// <param name="resourceName">�̹��� �̸�</param>
	/// <param name="resourceType">�̹��� Ÿ��</param>
	/// <param name="ppBitmap">Bitmap ����������</param>
	void LoadResourceBitmap(PCWSTR resourceName, PCWSTR resourceType, ID2D1Bitmap** ppBitmap);

	/// <summary>
	/// ��Ʈ���� �׸���.
	/// </summary>
	/// <param name="x">x Pos</param>
	/// <param name="y">y Pos</param>
	/// <param name="ppBitmap">�̹��� �̸�</param>
	/// <param name="opacity">����</param>
	/// <param name="size">������</param>
	void DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* ppBitmap, D2D1_SIZE_F scale = { 1.f, 1.f }, float opacity = 1.0f);


	/// <summary>
	/// ���� transform�� size��ŭ �̵��Ѵ�
	/// </summary>
	/// <param name="size">�̵��� ������</param>
	/// <returns>�����ŭ �̵��� ��ȯ���</returns>
	Matrix3x2F TranslateTransform(D2D1_SIZE_F size);

	/// <summary>
	/// ���� transform�� center �������� angle��ŭ ȸ���մϴ�.
	/// </summary>
	/// <param name="angle">ȸ���� ���� (0 ~ 360)</param>
	/// <param name="center">ȸ���� �߽���</param>
	/// <returns>center �������� ȸ���� ��ȯ���</returns>
	Matrix3x2F RotateTransform(float angle, D2D1_POINT_2F center);

	/// <summary>
	/// ���� transform�� center �������� size��ŭ �ø���
	/// </summary>
	/// <param name="size"></param>
	/// <param name="center"></param>
	/// <returns></returns>
	Matrix3x2F ScaleTransform(D2D1_SIZE_F size, D2D1_POINT_2F center);

	/// <summary>
	/// ���� transform�� �����·� �ǵ����ϴ�.
	/// </summary>
	/// <returns>�ǵ��� ���� ���� ���</returns>
	Matrix3x2F IdentityTransform();
private:
	HWND m_hwnd;				//���� ������ �ڵ�

	ID2D1Factory* m_pD2DFactory;	//D2DFactory

	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	/// <summary>
	/// WIC ���丮�� �����.
	/// ���� ��θ� ������� �ؼ� ���ڴ��� �����.
	///���ڵ��� �������� �����´�.
	///��ȯ�⿡ �־ Direct2D �������� ��ȯ�Ѵ�.
	///Direct2D ��Ʈ���� �����ϰ�, �̸� �������Ѵ�.
	///��ó: https://vsts2010.tistory.com/592 [Visual Studio 2010 ���� �� ��α� @vsts2010]
	/// </summary>
	IWICImagingFactory* m_pWICFactory;

	D2D1::ColorF m_BackGroundColor = D2D1::ColorF(D2D1::ColorF::Black);

	Matrix3x2F m_Transform = Matrix3x2F::Identity();
};

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)