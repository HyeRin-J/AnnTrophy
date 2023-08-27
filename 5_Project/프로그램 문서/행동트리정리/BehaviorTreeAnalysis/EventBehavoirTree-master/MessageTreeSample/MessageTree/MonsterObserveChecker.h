#pragma once
#include "..\Share\MessageChecker.h"

namespace BrainTree {

	// GOAL: Ư�� ���� ������ ��� �Դ��� üũ 
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

			// �α�
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