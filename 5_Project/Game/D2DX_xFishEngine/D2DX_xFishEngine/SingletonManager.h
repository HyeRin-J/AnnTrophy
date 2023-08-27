#pragma once

template<typename T>
class SingletonManager
{
private:
	static T* m_Instance;
public:
	/// <summary>
	/// ���� ���� ��ü�� ���ɴϴ�
	/// </summary>
	/// <returns>���� ������� ���� ��ü�� ��ȯ</returns>
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