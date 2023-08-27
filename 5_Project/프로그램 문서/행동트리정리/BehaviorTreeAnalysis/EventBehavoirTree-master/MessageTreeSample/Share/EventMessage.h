#pragma once
#include "stdafx.h"
#include <memory>
#include "..\Share\MessageIdEnum.h"

// 베이스
class EventMessage
{
public:
	using Ptr = std::shared_ptr<EventMessage>;

public:
	EventMessage(MessageId id, int senderId, int receiverId)
		: id_(id)
		, senderId_(senderId)
		, receiverId_(receiverId)
	{
	}

	virtual ~EventMessage()
	{
	}

public:
	MessageId getId() const { return id_; }

protected:
	MessageId id_;
	int senderId_ = 0;
	int receiverId_ = 0;
};


#pragma region OriginTestMessage



// 지형 진입
class TerrainInMessage : public EventMessage
{
public:
	TerrainInMessage(int senderId, int receiverId, int terrainId)
		: terrainId_(terrainId)
		, EventMessage(MessageId::TERRAIN_IN, senderId, receiverId)
	{
	}

public:
	int getTerrainId() const { return terrainId_; }

private:
	int terrainId_ = 0;
};

// 특정 NPC를 킬 하였음.
class KillNpcMessage : public EventMessage
{
public:
	KillNpcMessage(int senderId, int receiverId, int npcId)
		: npcId_(npcId)
		, EventMessage(MessageId::KILL_NPC, senderId, receiverId)
	{

	}

public:
	int getNpcId() const { return npcId_; }

private:
	int npcId_ = 0;
};

#pragma endregion

#pragma region MonsterTestMessage

// Player 가 사거리안에 들어왔다.
class FindPlayerMessage : public EventMessage
{
public:
	FindPlayerMessage(int senderId, int receiverId) // 위치값을 넘겨줘도 괜찮을듯?
		: EventMessage(MessageId::FIND_PLAYER, senderId, receiverId)
	{

	}
};

class MonsterDeadMessage : public EventMessage
{
public:
	MonsterDeadMessage(int senderId, int receiverId, int monsterId)
		: MonsterId(monsterId)
		, EventMessage(MessageId::DEAD_MYSELF, senderId, receiverId)
	{
	}

public:
	int getMonsterId() const { return MonsterId; }

private:
	int MonsterId = 0;
};




#pragma endregion