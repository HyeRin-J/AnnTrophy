#pragma once

namespace BrainTree
{
	//근접 공격 액션 노드
	class MeleeAttackAction : public Action
	{
	private:
		MeleeMonster* m_SourceObject;
	public:

		MeleeAttackAction(MeleeMonster* _source) :m_SourceObject(_source) {}
		virtual ~MeleeAttackAction() {}

		Status update() override
		{
#ifdef DEBUG
			Debug::Log("Attack :: Run attack Action");
#endif // DEBUG

			m_SourceObject->Attack();
			return Status::Success;
		}

	};

}