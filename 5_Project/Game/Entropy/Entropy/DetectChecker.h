#pragma once


namespace BrainTree 
{
	// tartget object �� Source Object�� �����ȿ��ִ��� üũ
	// ����� src �� monster , target �� �÷��̾��� �����ϰ� ���� generic ��������
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