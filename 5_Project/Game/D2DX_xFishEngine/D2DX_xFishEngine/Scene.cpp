#include "pch.h"
#include "MapData.h"
#include "TileType.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteData.h"
#include "ObjectBuildAlgorithm.h"
#include "SingletonManager.h"
#include "D2DGraphics.h"
#include "framework.h"

Scene::Scene(std::wstring newName, std::wstring tileName)
{
	m_Name = newName;

	m_TileMapPath = PATH_MAP_UNI;
	m_TileMapPath.append(_T("TileMap/"));
	m_TileMapPath.append(tileName);
}

Scene::~Scene()
{
	for (auto bitmap : m_BackGroundBitmap)
	{
		SafeRelease(&bitmap);
	}
}

void Scene::Init()
{
	m_IsLoadFinish = false;
	m_ChangeFinish = false;
	m_ChangeState = false;

	m_BackGroundPath = PATH_MAP_UNI;
	m_BackGroundPath.append(_T("Background/"));
	m_BackGroundPath.append(m_Name);
	m_BackGroundPath.append(_T("_0.png"));

	D2DGraphics::GetInstance()->D2DLoadBitmap(m_BackGroundPath.c_str(), &m_BackGroundBitmap[0]);

	m_BackGroundPath = PATH_MAP_UNI;
	m_BackGroundPath.append(_T("Background/"));
	m_BackGroundPath.append(m_Name);
	m_BackGroundPath.append(_T("_1.png"));

	D2DGraphics::GetInstance()->D2DLoadBitmap(m_BackGroundPath.c_str(), &m_BackGroundBitmap[1]);
	//초기화하고
	D2DGraphics::GetInstance()->D2DLoadBitmap(m_TileMapPath.c_str(), &m_TileBitmap);

	//다음
	Update();
}

void Scene::Update()
{
	//로직
	if (m_IsLoadFinish == true)
	{
		if (m_ChangeState == true)
		{
			m_ChangeBackgroundTime -= _FTime->GetEngineFixedDeltaTimeSec();

			if (m_ChangeBackgroundTime <= 0)
			{
				m_ChangeState = false;
				m_ChangeFinish = true;
				m_ChangeBackgroundTime = 0.6f;
			}
		}
	}
	else
	{
		float time = _FTime->GetEngineFixedDeltaTimeSec();
		m_LoadTime -= time;

		if (m_LoadTime <= 0.f)
		{
			m_IsLoadFinish = true;
			m_LoadTime = 2.0f;
		}
	}
}

void Scene::Render()
{
	if (m_ChangeState == true)
	{
		m_ChangeFinish = false;
		_GraphicEngine->Blend(m_BackGroundBitmap[m_BackgroundIndex ^ 0x01], m_BackGroundBitmap[m_BackgroundIndex], m_ChangeBackgroundTime);
	}
	else
	{
		_GraphicEngine->DrawBitmap(m_BackGroundBitmap[m_BackgroundIndex], 0, 0);
	}

	if(m_IsLoadFinish == false)
	{
		_GraphicEngine->DrawBitmap(LoadSceneManager::GetInstance()->m_LoadImage, 0, 0);
	}
}

void Scene::PostRender()
{
}

void Scene::Release()
{
	//m_Data.Attribute.clear();
	//m_Data.Index.clear();

	SafeRelease(&m_BackGroundBitmap[0]);
	SafeRelease(&m_BackGroundBitmap[1]);

	SafeRelease(&m_TileBitmap);
}

void Scene::ChangeState()
{
	m_ChangeState = true;
}
