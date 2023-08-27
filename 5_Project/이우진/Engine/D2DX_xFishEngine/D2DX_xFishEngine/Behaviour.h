#pragma once
class Behaviour : Component
{
public:
	Behaviour();
	virtual ~Behaviour();
protected:
	bool m_isEnable;
public:
	bool GetEnable() { return m_isEnable; }
	void SetEnable(bool _v) { m_isEnable = _v; }

};

