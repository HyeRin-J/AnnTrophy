#pragma once
class Animator : public Component
{
	std::vector<SpriteData> m_AnimationData;

	PCWSTR			m_DataPath;

	ID2D1Bitmap*	m_Image;

	int		m_Index = 0;
	bool	m_IsPlaying = true;

	void	LoadData(PCWSTR dataPath);
public:
	virtual void	Awake();
	virtual void	Update();
	virtual void	OnRender();

	void	SetPath(PCWSTR _path) { m_DataPath = _path; };

	void	StartAnimation() { m_IsPlaying = true; }
	void	StopAnimation() { m_IsPlaying = false; }
};

