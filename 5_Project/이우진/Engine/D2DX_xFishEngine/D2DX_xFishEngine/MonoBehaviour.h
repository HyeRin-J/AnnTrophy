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
	void Awake();//���ʽ���� �� �ѹ��� ȣ��Ǵ� �Լ�
	void FixedUpdate();
	void Update();//�� �����Ӹ��� ȣ��
	void LateUpdate();//������ 

public:
	//invoke func
	void Invoke();
	void InvokeReating();
	void CancleInvoke();
};

