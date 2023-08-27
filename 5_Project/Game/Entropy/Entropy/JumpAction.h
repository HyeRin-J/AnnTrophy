#pragma once

namespace BrainTree
{
	class JumpAction : public Action
	{
	private:
		JumpMeleeMonster* m_SourceObject;
	public:

		JumpAction(JumpMeleeMonster* _source) :m_SourceObject(_source) {}
		virtual ~JumpAction() {}

		Status update() override
		{
			m_SourceObject->Jump();
		
			return Status::Success;
		}
	};
	
	
}

