#pragma once


namespace BrainTree
{
	class RangeAttackAction : public Action
	{
	private:
		RangedMonster* m_SourceObject;
	public:

		RangeAttackAction(RangedMonster* _source) :m_SourceObject(_source) {}
		virtual ~RangeAttackAction() {}

		Status update() override
		{

			//Debug::Log("Move:: Run Move Action");

		/*	if (dynamic_cast<JumpMeleeMonster*>(m_SourceObject) != nullptr)
			{
				dynamic_cast<JumpMeleeMonster*>(m_SourceObject)->Move();
				return Status::Success;
			}*/

			m_SourceObject->RangeAttack();
			return Status::Success;
		}
	};
}

