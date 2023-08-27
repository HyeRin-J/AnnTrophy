#pragma once
#include <string>

class BaseMessage
{
public:
	std::string m_Name;
	int m_Value = 0;

	inline std::string GetName(){ return m_Name; };
	inline void SetName(std::string newName) { m_Name = newName; };

	inline int GetValue() { return m_Value; };
	inline void SetValue(int newValue) { m_Value = newValue; };
};

