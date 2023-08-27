#pragma once

class SceneManager : public SingletonManager<SceneManager>
{
private:
	std::vector<Scene*> m_Scene;

	int m_ActiveCSceneNum = -1;
public:
	void LoadData(PCWSTR path);

	void CreateScene(std::wstring name, std::wstring tilemapName);

	bool LoadScene(int index);
	bool LoadScene(std::wstring name);

	int GetSceneAt() { return m_ActiveCSceneNum; };
	Scene* GetActiveScene() { return m_Scene[m_ActiveCSceneNum]; };

	//Manager
	void Init();

	//it is need?
	//void Update();
	//void Render();
};

