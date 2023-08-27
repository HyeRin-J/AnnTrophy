#pragma once


namespace BrainTree
{
	class DashAction : public Action
	{
	private:
		DashMeleeMonster* m_SourceObject;
	public:

		DashAction(DashMeleeMonster* _source) :m_SourceObject(_source) {}
		virtual ~DashAction() {}

		Status update() override
		{
			m_SourceObject->Dash();
			return Status::Success;
		}
	};
}

