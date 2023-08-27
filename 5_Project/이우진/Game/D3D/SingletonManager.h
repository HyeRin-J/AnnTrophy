#pragma once
template<typename T>
class SingletonManager
{
private:
	static T* m_Instance;
public:
	//�����Լ��� �޸𸮿� �÷����� .  ������ ��ü�� ��ȯ �� �� �ְ� �Լ� ����
	static T* GetInstance();
};


template<typename T>
T* SingletonManager<T>::m_Instance = nullptr;

/*
*  �ζ��� �Լ��� �ڵ���� ���η� �� �Լ���
	�ζ��� �Լ��� Ÿ��üũ�� �ؼ� ���ڸ� ex)int�� �����θ� ������, 
	��ũ�� �Լ��� �׷� �� ���� ������ ġȯ�Ѵ�.
*/
template<typename T>
 T* SingletonManager<T>::GetInstance()
{
	//���ϰ��� ������ ��ü�� ��ȯ�Ѵ�.
	if (m_Instance == nullptr)
	{
		m_Instance = new T();
	}

	return m_Instance;
}
