#pragma once
#include "..\Share\MessageChecker.h"

namespace BrainTree {

	// GOAL: 특정 영역 안으로 들어 왔는지 체크 
	class MonsterObserveChecker : public MessageChecker
	{
	public:
		MonsterObserveChecker(int monsterId)
			: monsterId_(monsterId)
		{
		}
		virtual ~MonsterObserveChecker() {}

	private:
		bool check(EventMessage::Ptr message) override
		{
			bool result = false;

			do
			{
				if (message->getId() != MessageId::FIND_PLAYER)
				{
					break;
				}

				result = true;

			} while (false);

			// 로그
			doLog(result);

			return result;
		}

		void doLog(bool result)
		{
			printf("Message, Monster Observe Checker(%d) State:%s\n", monsterId_, result ? "Success" : "Run");
		}

	protected:
		int monsterId_ = 0;
	};
}