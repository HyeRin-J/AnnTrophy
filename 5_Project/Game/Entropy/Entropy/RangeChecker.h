#pragma once


namespace BrainTree
{
	class RangeChecker : public MessageChecker
	{
	public:
		RangeChecker() {};

		bool check(BTEventMessage::BaseMessage message) override
		{
			if (message.GetState() == BTEventMessage::MessageId::INRANGED)
			{

				return true;
			}

			status = Status::Failure;
			return false;
		};

	};

}
