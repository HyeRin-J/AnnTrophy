#pragma once
class MonoBehaviour : public Behaviour
{
public:
	MonoBehaviour();
	~MonoBehaviour();
public:
	void OnCollistionEnter();


public:
	//update list
	void Awake();//최초실행시 딱 한번만 호출되는 함수
	void FixedUpdate();
	void Update();//매 프레임마다 호출
	void LateUpdate();//고정된 

public:
	//invoke func
	void Invoke();
	void InvokeReating();
	void CancleInvoke();
};

