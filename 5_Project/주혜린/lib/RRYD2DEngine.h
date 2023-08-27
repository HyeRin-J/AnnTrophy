#pragma once

using namespace D2D1;
class GameObject;

class RRYD2DEngine : public SingletonManager<RRYD2DEngine>
{
public:
	RRYD2DEngine();
	~RRYD2DEngine();

	/// <summary>
	/// 엔진을 초기화합니다
	/// </summary>
	/// <param name="hwnd">메인 윈도우 핸들</param>
	/// <returns>결과</returns>
	HRESULT Initialize(HWND& hwnd);

	/// <summary>
	/// 리소스 자원들을 생성합니다
	/// </summary>
	/// <returns> 결과 </returns>
	HRESULT CreateResource();

	/// <summary>
	/// 렌더링 시작
	/// </summary>
	void BeginRender();

	/// <summary>
	/// 렌더링이 끝났음
	/// </summary>
	void EndRender();

	/// <summary>
	/// 내부가 비어있는 사각형을 그린다
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="penColor">테두리 색깔</param>
	/// <param name="strokeWidth">테두리 두께</param>
	/// <param name="style">테두리 스타일 https://docs.microsoft.com/en-us/windows/win32/api/d2d1/nn-d2d1-id2d1strokestyle </param>
	void DrawHollowRect(int xPos, int yPos, int width, int height, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// 내부가 채워진 사각형을 그린다
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="BrushColor">Rect Color</param>
	void DrawFillRect(int xPos, int yPos, int width, int height, D2D1::ColorF BrushColor);

	/// <summary>
	/// 내부가 비어있는 둥근 사각형을 그린다
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="xRadius">모서리 x 반지름</param>
	/// <param name="yRadius">모서리 y 반지름</param>
	/// <param name="penColor">펜 크기</param>
	/// <param name="strokeWidth">테두리 두께</param>
	/// <param name="style">테두리 스타일</param>
	void DrawHollowRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// 내부가 채워진 둥근 사각형을 그린다
	/// </summary>
	/// <param name="xPos">x Pos</param>
	/// <param name="yPos">y Pos</param>
	/// <param name="width">Rect Width</param>
	/// <param name="height">Rect Height</param>
	/// <param name="xRadius">모서리 x 반지름</param>
	/// <param name="yRadius">모서리 y 반지름</param>
	/// <param name="BrushColor">사각형 내부 색깔</param>
	void DrawFillRoundRect(int xPos, int yPos, int width, int height, float xRadius, float yRadius, D2D1::ColorF BrushColor);

	/// <summary>
	/// 내부가 비어있는 타원을 그린다
	/// </summary>
	/// <param name="xPos">타원 중심 x Pos</param>
	/// <param name="yPos">타원 중심 y Pos</param>
	/// <param name="xRadius">x축 반지름</param>
	/// <param name="yRadius">y축 반지름</param>
	/// <param name="penColor">테두리 색깔</param>
	/// <param name="strokeWidth">테두리 두께</param>
	/// <param name="style">테두리 스타일 https://docs.microsoft.com/en-us/windows/win32/api/d2d1/nn-d2d1-id2d1strokestyle </param>
	void DrawHollowEllipse(int xPos, int yPos, int xRadius, int yRadius, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);


	/// <summary>
	/// 내부가 채워진 타원을 그린다
	/// </summary>
	/// <param name="xPos">타원 중심 x Pos</param>
	/// <param name="yPos">타원 중심 y Pos</param>
	/// <param name="xRadius">x축 반지름</param>
	/// <param name="yRadius">y축 반지름</param>
	/// <param name="BrushColor">타원 색깔</param>
	void DrawFillEllipse(int xPos, int yPos, int xRadius, int yRadius, D2D1::ColorF BrushColor);

	/// <summary>
	/// 선을 그린다
	/// </summary>
	/// <param name="x1">start xPos</param>
	/// <param name="y1">start yPos</param>
	/// <param name="x2">end xPos</param>
	/// <param name="y2">end yPos</param>
	/// <param name="penColor">선 색깔</param>
	/// <param name="strokeWidth">선 너비</param>
	/// <param name="style">선의 스타일</param>
	void DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF penColor, float strokeWidth = 1.0f, ID2D1StrokeStyle* style = nullptr);

	/// <summary>
	/// 텍스트 출력
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="textColor"></param>
	/// <param name="pch"></param>
	void PrintText(int x, int y, D2D1::ColorF textColor, const WCHAR* pch, ...);

	/// <summary>
	/// 파일로부터 이미지를 불러온다
	/// </summary>
	/// <param name="path">이미지를 불러올 경로</param>
	/// <param name="ppBitmap">Bitmap 이중포인터</param>
	void LoadBitmapFromFile(PCWSTR path, ID2D1Bitmap** ppBitmap);

	/// <summary>
	/// 리소스로부터 이미지를 불러온다
	/// </summary>
	/// <param name="resourceName">이미지 이름</param>
	/// <param name="resourceType">이미지 타입</param>
	/// <param name="ppBitmap">Bitmap 이중포인터</param>
	void LoadResourceBitmap(PCWSTR resourceName, PCWSTR resourceType, ID2D1Bitmap** ppBitmap);

	/// <summary>
	/// 비트맵을 그린다.
	/// </summary>
	/// <param name="x">x Pos</param>
	/// <param name="y">y Pos</param>
	/// <param name="ppBitmap">이미지 이름</param>
	/// <param name="opacity">투명도</param>
	/// <param name="size">사이즈</param>
	void DrawBitmap(D2D1_POINT_2F point, SpriteData data, ID2D1Bitmap* ppBitmap, D2D1_SIZE_F scale = { 1.f, 1.f }, float opacity = 1.0f);


	/// <summary>
	/// 현재 transform을 size만큼 이동한다
	/// </summary>
	/// <param name="size">이동할 사이즈</param>
	/// <returns>사이즈만큼 이동한 변환행렬</returns>
	Matrix3x2F TranslateTransform(D2D1_SIZE_F size);

	/// <summary>
	/// 현재 transform을 center 기준으로 angle만큼 회전합니다.
	/// </summary>
	/// <param name="angle">회전할 각도 (0 ~ 360)</param>
	/// <param name="center">회전할 중심점</param>
	/// <returns>center 기준으로 회전된 변환행렬</returns>
	Matrix3x2F RotateTransform(float angle, D2D1_POINT_2F center);

	/// <summary>
	/// 현재 transform을 center 기준으로 size만큼 늘린다
	/// </summary>
	/// <param name="size"></param>
	/// <param name="center"></param>
	/// <returns></returns>
	Matrix3x2F ScaleTransform(D2D1_SIZE_F size, D2D1_POINT_2F center);

	/// <summary>
	/// 현재 transform을 원상태로 되돌립니다.
	/// </summary>
	/// <returns>되돌린 후의 현재 행렬</returns>
	Matrix3x2F IdentityTransform();
private:
	HWND m_hwnd;				//메인 윈도우 핸들

	ID2D1Factory* m_pD2DFactory;	//D2DFactory

	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	/// <summary>
	/// WIC 팩토리를 만든다.
	/// 파일 경로를 기반으로 해서 디코더를 만든다.
	///디코딩된 프레임을 가져온다.
	///변환기에 넣어서 Direct2D 형식으로 변환한다.
	///Direct2D 비트맵을 생성하고, 이를 렌더링한다.
	///출처: https://vsts2010.tistory.com/592 [Visual Studio 2010 공식 팀 블로그 @vsts2010]
	/// </summary>
	IWICImagingFactory* m_pWICFactory;

	D2D1::ColorF m_BackGroundColor = D2D1::ColorF(D2D1::ColorF::Black);

	Matrix3x2F m_Transform = Matrix3x2F::Identity();
};

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)