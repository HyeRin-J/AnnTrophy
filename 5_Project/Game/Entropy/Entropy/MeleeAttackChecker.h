#pragma once

namespace BrainTree 
{
	//// tartget object �� Source Object��  "����" �����ȿ��ִ��� üũ
	//// ����� src �� Meleemonster , target �� �÷��̾��� �����ϰ� ���� generic ��������
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