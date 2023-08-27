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
//		// 상태 변경
//		state_ = StateType::Running;
//
//		// 초기화
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
//		// 다음으로 진행
//		change(next_it->first);
//	}
//}
//
//void MobFSM::makeSample()
//{
//	// 테스트 BT 생성
//	int startId = 1;
//	for (int i = 0; i <= 2; i++)
//	{
//		auto page = std::make_shared<Page>(startId + i, this);
//
//		page->makeSample();
//
//		// 주입
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
//		// 초기화와 START 호출
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
//	// 로그
//	//UTIL::doLog("FSM:", "Try Change Page:", current_->getPageId(), "->", nextId);
//
//	// 현재 END
//	current_->onEnd();
//
//	// 교cp
//	current_ = it->second;
//
//	// 변경 PAGE 시작
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
