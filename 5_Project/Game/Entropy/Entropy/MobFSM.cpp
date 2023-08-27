#include "GamePCH.h"
//#include "MobFSM.h"
//
//MobFSM::MobFSM()
//{
//}
//
//void MobFSM::onTick(int tickIndex, int interval)
//{
//	if (state_ == StateType::None)
//	{
//		// ���� ����
//		state_ = StateType::Running;
//
//		// �ʱ�ȭ
//		init();
//	}
//
//	if (current_ != nullptr)
//	{
//		current_->onUpdate();
//	}
//
//}
//
//void MobFSM::onMessage(EventMessage::Ptr message)
//{
//	if (current_ == nullptr)
//	{
//		//error
//		//UTIL::doLog("FSM:", __FUNCTION__, "Current Reference: Fail");
//	}
//	else
//	{
//		current_->onMessage(message);
//	}
//}
//
//void MobFSM::nextPage()
//{
//	if (current_ == nullptr)
//	{
//		//UTIL::doLog("FSM:", __FUNCTION__, "Page Reference: Fail");
//
//		return;
//	}
//
//	auto it = pages_.find(current_->getPageId());
//	if (it == pages_.end())
//	{
//		return;
//	}
//
//	auto next_it = std::next(it);
//	if (next_it != pages_.end())
//	{
//		// �������� ����
//		change(next_it->first);
//	}
//}
//
//void MobFSM::makeSample()
//{
//	// �׽�Ʈ BT ����
//	int startId = 1;
//	for (int i = 0; i <= 2; i++)
//	{
//		auto page = std::make_shared<Page>(startId + i, this);
//
//		page->makeSample();
//
//		// ����
//		insert(page);
//	}
//}
//
//void MobFSM::init()
//{
//	if (!pages_.empty())
//	{
//		auto first = pages_.begin()->second;
//		current_ = first;
//
//		// �ʱ�ȭ�� START ȣ��
//		current_->onStart();
//	}
//}
//
//void MobFSM::change(int nextId)
//{
//	if (current_ == nullptr)
//	{
//		//UTIL::doLog("FSM:", __FUNCTION__, "Page Reference: Fail");
//		return;
//	}
//
//	auto it = pages_.find(nextId);
//	if (it == pages_.end())
//	{
//		//UTIL::doLog("FSM:", __FUNCTION__, "Find: Fail");
//		return;
//	}
//
//	// �α�
//	//UTIL::doLog("FSM:", "Try Change Page:", current_->getPageId(), "->", nextId);
//
//	// ���� END
//	current_->onEnd();
//
//	// ��cp
//	current_ = it->second;
//
//	// ���� PAGE ����
//	current_->onStart();
//}
//
//void MobFSM::insert(Page::Ptr ptrPage)
//{
//	auto it = pages_.insert(std::make_pair(ptrPage->getPageId(), ptrPage));
//	if (!it.second)
//	{
//		UTIL::doLog("FSM:", "Insert Fail", ptrPage->getPageId());
//	}
//}
