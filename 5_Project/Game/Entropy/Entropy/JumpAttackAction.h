#pragma once


namespace BrainTree
{
	class JumpAttackAction : public Action
	{
	private:
		JumpMeleeMonster* m_SourceObject;
	public:

		JumpAttackAction(JumpMeleeMonster* _source) :m_SourceObject(_source) {}

		Status update() override
		{

			//Debug::Log("Move:: Run Move Action");

			m_SourceObject->JumpAttack();
			return Status::Success;
		}
	};
}
