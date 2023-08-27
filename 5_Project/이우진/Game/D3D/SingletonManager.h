#pragma once
template<typename T>
class SingletonManager
{
private:
	static T* m_Instance;
public:
	//전역함수로 메모리에 올려놓고 .  참조된 객체를 반환 할 수 있게 함수 선언
	static T* GetInstance();
};


template<typename T>
T* SingletonManager<T>::m_Instance = nullptr;

/*
*  인라인 함수는 코드라인 내부로 들어간 함수로
	인라인 함수는 타입체크를 해서 인자를 ex)int형 정수로만 받지만, 
	매크로 함수는 그런 것 없이 무조건 치환한다.
*/
template<typename T>
 T* SingletonManager<T>::GetInstance()
{
	//리턴값은 참조된 객체를 반환한다.
	if (m_Instance == nullptr)
	{
		m_Instance = new T();
	}

	return m_Instance;
}
