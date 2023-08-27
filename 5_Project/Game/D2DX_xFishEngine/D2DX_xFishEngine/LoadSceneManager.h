#pragma once

class LoadSceneManager : public SingletonManager<LoadSceneManager>
{
private:
	std::vector<Scene*> m_Scene;

	int m_ActiveCSceneNum = -1;

public:
	ID2D1Bitmap* m_LoadImage;

	void LoadData(PCWSTR path);

	void CreateScene(std::wstring name, std::wstring tilemapName);

	bool LoadScene(int index);
	bool LoadScene(std::wstring name);

	int GetSceneAt() { return m_ActiveCSceneNum; };
	Scene* GetActiveScene() { return m_Scene[m_ActiveCSceneNum]; };

	//Manager
	void Init();

	int		SceneMax() {return m_Scene.size();}

	//it is need?
	//void Update();
	//void Render();
};

