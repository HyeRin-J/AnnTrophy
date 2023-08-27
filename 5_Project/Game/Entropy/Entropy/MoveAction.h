#pragma once


namespace BrainTree
{
	//Monster Move action node
	class MoveAction : public Action
	{
	private:
		BaseMonster* m_SourceObject;
	public:

		MoveAction(BaseMonster* _source):m_SourceObject(_source) {}
		virtual ~MoveAction() {}

		Status update() override
		{			

			//Debug::Log("Move:: Run Move Action");

		/*	if (dynamic_cast<JumpMeleeMonster*>(m_SourceObject) != nullptr)
			{
				dynamic_cast<JumpMeleeMonster*>(m_SourceObject)->Move();
				return Status::Success;
			}*/

			m_SourceObject->Move();
			return Status::Success;
		}
	};

	//Monster Tracking action node
	class TrackingAction : public Action
	{
	private:
		BaseMonster* m_SourceObject;
	public:
		TrackingAction(BaseMonster* _source) :m_SourceObject(_source) {}
		virtual ~TrackingAction() {}

		Status update() override
		{
#ifdef DEBUG
			Debug::Log("Tracking:: Tracking Player!");
#endif // DEBUG

			m_SourceObject->Tracking();
			return Status::Success;
		}
	};
}

