#pragma once
class CustomClass
{
private:

public:
	CustomClass() { Awake(); }
	~CustomClass() { OnDestroy(); }

	static bool HandleYourMesssageListener(BaseMessage* msg);
	void Awake();
	void OnDestroy();
};

