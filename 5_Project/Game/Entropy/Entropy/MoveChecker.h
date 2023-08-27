#pragma once

namespace BrainTree
{
	class MoveChecker : public MessageChecker
	{
	public:
		MoveChecker() {};

		bool check(BTEventMessage::BaseMessage message) override
		{
			if (message.GetState() == BTEventMessage::MessageId::MOVE)
			{

				//Debug::Log("MoveChecker on!");

				return true;
			}

			status = Status::Failure;
			return false;
		};

		/*Status updateMessage(BTEventMessage::BaseMessage message) override
		{
			if (check(message))
			{
				return Status::Running;
			}

			return status;
		}*/
	};
}

