//#pragma once
//#include "GamePCH.h"
//#include <memory>
//#include "MobEvent.h"
//
//// 베이스
//class MOBEventMessage
//{
//public:
//	using Ptr = std::shared_ptr<MOBEventMessage>;
//
//public:
//	MOBEventMessage(MobEvent id, int senderId, int receiverId)
//		: id_(id)
//		, senderId_(senderId)
//		, receiverId_(receiverId)
//	{
//	}
//
//	virtual ~MOBEventMessage()
//	{
//	}
//
//public:
//	MessageId getId() const { return id_; }
//
//protected:
//	MessageId id_;
//	int senderId_ = 0;
//	int receiverId_ = 0;
//};
//
//// 어택당했음
//class AttackedMessage : public EventMessage
//{
//public:
//	AttackedMessage(int senderId, int receiverId, int terrainId)
//		: terrainId_(terrainId)
//		, MOBEventMessage(MobEvent::ATTACKED, senderId, receiverId)
//	{
//	}
//
//public:
//	int getTerrainId() const { return terrainId_; }
//
//private:
//	int terrainId_ = 0;
//};