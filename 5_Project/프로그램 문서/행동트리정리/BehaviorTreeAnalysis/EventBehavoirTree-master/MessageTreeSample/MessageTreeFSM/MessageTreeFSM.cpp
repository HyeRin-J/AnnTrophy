// MessageTreeFSM.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Page.h"
#include "PageFSM.h"

#include "MonsterPage.h"
#include "MonsterFSM.h"
#include "NextPageAction.h"

int main()
{
	// 1. fsm ����
	auto pageFSM = std::make_shared<PageFSM>();

	// 2. ���� ������ �����
	// Desc: 3 Page, 3 Behavior Tree
	pageFSM->makeSample();

	// 3. ������Ʈ 
	const int INTERVAL = 500;
	for (int i = 0; i < 10; i++)
	{
		pageFSM->onTick(i, INTERVAL);
	}


	//auto monFSM = std::make_shared<MonsterFSM>();

	//monFSM->makeSample();

	//const int INTERVAL = 300;
	//for (int i = 0; i < 10; i++)
	//{
	//	monFSM->onTick(i, INTERVAL);
	//}



    return 0;
}