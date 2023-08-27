#pragma once

namespace BrainTree 
{
	//// tartget object 가 Source Object에  "공격" 범위안에있는지 체크
	//// 현재는 src 가 Meleemonster , target 이 플레이어라고 가정하고 만듬 generic 하지않음
	class MeleeAttackChecker : public MessageChecker
	{
	public:
		MeleeAttackChecker() {};
	public:
		bool check(BTEventMessage::BaseMessage message) override
		{

			if (message.GetState() == BTEventMessage::MessageId::INREACH)
			{
#ifdef DEBUG
				Debug::Log("Inreach:: Detect In Reach Player!");
#endif // DEBUG

				return true;
			}

			status = Status::Failure;
			return false;
		};
	};
}