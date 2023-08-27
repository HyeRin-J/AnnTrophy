#pragma once


namespace BrainTree 
{
	// tartget object 가 Source Object에 범위안에있는지 체크
	// 현재는 src 가 monster , target 이 플레이어라고 가정하고 만듬 generic 하지않음
	class DetectChecker : public MessageChecker
	{
	private:
		

	public:
		DetectChecker(){};

	public:
		bool check(BTEventMessage::BaseMessage message) override
		{

			if (message.GetState() == BTEventMessage::MessageId::DETECTPLAYER)
			{
#ifdef DEBUG
				//Debug::Log("DetectChecker:: Detect Player!");
#endif // DEBUG
				return true;
			}

			status = Status::Failure;
			return false;
		};
	};
}