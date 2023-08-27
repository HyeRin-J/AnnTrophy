#pragma once

namespace BrainTree
{
	class TopPlatformChecker : public MessageChecker
	{
		public:
			TopPlatformChecker() {};

			bool check(BTEventMessage::BaseMessage message) override
			{
				if (message.GetState() == BTEventMessage::MessageId::DETECTTOPPLATFORM)
				{
					return true;
				}

				status = Status::Failure;
				return false;
			};

	};
}

