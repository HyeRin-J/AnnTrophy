#include "pch.h"
#include "MapData.h"
#include "SpriteData.h"
#include "TileType.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "SingletonManager.h"
#include "ResourceManager.h"
#include "LoadSceneManager.h"
#include "framework.h"

void LoadSceneManager::LoadData(PCWSTR path)
{
	std::wstring SceneName = ResourceManager::GetInstance()->LoadFile(path, ResourceManager::LOADMODE::MAP);
	MapData data = ResourceManager::GetInstance()->m_MapData;
	CreateScene(SceneName, data.TileName);
	m_Scene[m_Scene.size() - 1]->m_Data = data;
}

void LoadSceneManager::CreateScene(std::wstring name, std::wstring tilemapName)
{
	m_Scene.push_back(new Scene(name, tilemapName));
}

bool LoadSceneManager::LoadScene(int index)
{
	if (m_ActiveCSceneNum != -1)
	{
		//이전 씬 릴리즈
		m_Scene[m_ActiveCSceneNum]->Release();
	}

	//씬바꾸기
	m_ActiveCSceneNum = index;
	m_Scene[m_ActiveCSceneNum]->Init();

	return true;
}

bool LoadSceneManager::LoadScene(std::wstring name)
{
	for (int i = 0; i < m_Scene.size(); i++)
	{
		if (m_Scene[i]->m_Name == name)
		{
			m_ActiveCSceneNum = i;
			break;
		}

	}

	return LoadScene(m_ActiveCSceneNum);
}

void LoadSceneManager::Init()
{
	// init 에 필요한거
	std::wstring path = PATH_IMAGE_UNI;
	path.append(_T("/Sprite/LoadingScreen.png"));
	
	_GraphicEngine->D2DLoadBitmap(path.c_str(), &m_LoadImage);
}