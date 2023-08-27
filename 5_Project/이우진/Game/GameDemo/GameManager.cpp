#include "GamePch.h"
#include "framework.h"
#include "GameManager.h"
#include "SystemClass.h"

GameManager::GameManager()
{
	m_System = nullptr;
	m_Result = false;
}

GameManager::~GameManager()
{
}

bool GameManager::Initialize()
{

	m_Result  = false;
	m_System = new SystemClass;

	if (!m_System)
	{
		return 0;
	}

	// Initialize and run the system object.
	m_Result = m_System->Initialize();




	return true;
}

bool GameManager::BeginRender()
{
	return true;
}

bool GameManager::Rendering()
{
	if (m_Result == true)
	{
		m_System->Run();
	}

	return true;
}

bool GameManager::EndRender()
{
	return true;
}

bool GameManager::Update()
{
	m_Result = BeginRender();
	m_Result = Rendering();
	m_Result = EndRender();

	return true;
}

void GameManager::Release()
{
	// Shutdown and release the system object.
	m_System->Shutdown();
	delete m_System;
	m_System = nullptr;

	return;
}
