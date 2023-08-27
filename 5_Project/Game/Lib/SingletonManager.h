#pragma once

template<typename T>
class SingletonManager
{
private:
	static T* m_Instance;
public:
	/// <summary>
	/// 현재 참조 객체를 얻어옵니다
	/// </summary>
	/// <returns>현재 만들어진 참조 객체를 반환</returns>
	static T* GetInstance();
};

template<typename T>
T* SingletonManager<T>::m_Instance = nullptr;

template<typename T>
inline T* SingletonManager<T>::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new T();
	}

	return m_Instance;
}