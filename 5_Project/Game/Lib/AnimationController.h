#pragma once

class AnimationController : public Component
{
	/// <summary>
	/// 스프라이트 간의 트랜지션
	/// </summary>
	struct Transition
	{
		int fromIndex = -1;
		int toIndex = -1;

		/// <summary>
		/// 조건이 전부 맞아야 transition이 true가 된다
		/// </summary>
		std::map<std::string, bool> condition;

		bool hasExit = false;

		/// <summary>
		/// 전이할 조건을 추가한다
		/// </summary>
		/// <param name="_name">조건 이름</param>
		/// <param name="_state">상태</param>
		void AddCondition(std::string _name, bool _state)
		{
			condition[_name] = _state;
		}
	};

public:
	//Transition 조건 분기
	std::map<std::string, bool> m_Conditions;

	/// <summary>
	/// 애니메이션 클립들
	/// </summary>
	std::vector<Sprite*> m_Sprites;

	/// <summary>
	/// 현재 재생중인 스프라이트 인덱스
	/// </summary>
	int m_CurrIndex = 0;

	/// <summary>
	/// 스프라이트 간의 전이 상태
	/// </summary>
	std::multimap<int, Transition> m_Transitions;

	/// <summary>
	/// 조건을 추가한다
	/// </summary>
	/// <param name="_name">추가할 이름</param>
	void AddCondition(std::string _name)
	{
		m_Conditions[_name] = false;
	}

	/// <summary>
	/// 특정 트랜지션에 조건을 추가한다
	/// </summary>
	/// <param name="_fromIndex">전이 전 인덱스</param>
	/// <param name="_toIndex">전이 후 인덱스</param>
	/// <param name="_name">조건 이름</param>
	/// <param name="_state">조건 상태</param>
	void AddConditionToTransition(int _fromIndex, int _toIndex, std::string _name, bool _state)
	{
		auto iter = m_Transitions.find(_fromIndex);

		while (iter != m_Transitions.end())
		{
			if (iter->second.toIndex == _toIndex)
			{
				iter->second.condition[_name] = _state;
				break;
			}
			iter++;
		}
	}

	/// <summary>
	/// 조건을 설정한다
	/// </summary>
	/// <param name="_name">설정할 조건 이름</param>
	/// <param name="_state">설정할 상태</param>
	void SetCondition(std::string _name, bool _state)
	{
		for (int i = 0; i < m_Conditions.size(); i++)
		{
			if (m_Conditions.find(_name) != m_Conditions.end())
			{
				m_Conditions[_name] = _state;
				break;
			}
		}
	}

	/// <summary>
	/// 트랜지션을 추가한다
	/// </summary>
	/// <param name="_fromIndex">전이 전 스프라이트 인덱스</param>
	/// <param name="_toIndex">전이 후 스프라이트 인덱스</param>
	/// <returns>추가한 트랜지션</returns>
	Transition AddTransition(int _fromIndex, int _toIndex, bool _hasExit = false)
	{
		Transition tr;
		tr.fromIndex = _fromIndex;
		tr.toIndex = _toIndex;
		tr.hasExit = _hasExit;

		auto pair = std::pair<int, Transition>(_fromIndex, tr);

		m_Transitions.insert(pair);
		return pair.second;
	}

	/// <summary>
	/// 트랜지션을 가져온다
	/// </summary>
	/// <param name="_fromIndex">전이 전 인덱스 정보</param>
	/// <param name="_toIndex">전이 후 인덱스 정보</param>
	/// <returns>추가했던 트랜지션</returns>
	Transition GetTransition(int _fromIndex, int _toIndex)
	{
		auto iter = m_Transitions.find(_fromIndex);

		while (iter != m_Transitions.end())
		{
			if (iter->second.toIndex == _toIndex)
			{
				return iter->second;
			}
			iter++;
		}

		return Transition();
	}

	/// <summary>
	/// 트랜지션의 조건을 체크한다
	/// </summary>
	void CheckCondition()
	{
		auto range = m_Transitions.equal_range(-1);

		for (auto& tr = range.first; tr != range.second; tr++)
		{
			if (tr->second.hasExit == false && m_Sprites[m_CurrIndex]->m_IsPlayOnce == true && m_Sprites[m_CurrIndex]->m_IsFinish == false)
				return;

			bool check = false;

			if (tr->second.condition.size() == 0)
			{
				check = true;
			}
			else
			{
				for (auto& con : tr->second.condition)
				{
					if (m_Conditions[con.first] != con.second)
					{
						break;
					}
					check = true;
				}
			}

			if (check == true)
			{
				m_Sprites[m_CurrIndex]->SetActive(false);

				m_Sprites[m_CurrIndex]->StopAnimation();

				m_CurrIndex = tr->second.toIndex;

				m_Sprites[m_CurrIndex]->SetActive(true);
				m_Sprites[m_CurrIndex]->StartAnimation();

				//조건 초기화
				
				for (auto& con : tr->second.condition)
				{
					m_Conditions[con.first] = false;
				}
			
				return;
			}
		}

		range = m_Transitions.equal_range(m_CurrIndex);
		for (auto& tr = range.first; tr != range.second; tr++)
		{
			if (tr->second.hasExit == false)
			{
				if (m_Sprites[m_CurrIndex]->m_IsPlayOnce == true && m_Sprites[m_CurrIndex]->m_IsFinish == false)
      					return;
			}

			bool check = false;

			if (tr->second.condition.size() == 0)
			{
				check = true;
			}
			else
			{
				for (auto& con : tr->second.condition)
				{
					if (m_Conditions[con.first] != con.second)
					{
						check = false;
						break;
					}
					check = true;
				}
			}

			if (check == true)
			{
				m_Sprites[m_CurrIndex]->StopAnimation();
				m_Sprites[m_CurrIndex]->SetActive(false);


				m_CurrIndex = tr->second.toIndex;

				m_Sprites[m_CurrIndex]->SetActive(true);
				m_Sprites[m_CurrIndex]->StartAnimation();

				//조건 초기화

				for (auto& con : tr->second.condition)
				{
					m_Conditions[con.first] = false;
				}

				return;
			}
		}
	}

	/// <summary>
	/// 현재 재생중인 스프라이트
	/// </summary>
	/// <returns>현재 재생중인 스프라이트의 포인터</returns>
	Sprite* GetCurrentSprite()
	{
		return m_Sprites[m_CurrIndex];
	}

	/// <summary>
	/// 인덱스 지점의 스프라이트를 반환
	/// </summary>
	/// <param name="_index">가져올 인덱스</param>
	/// <returns>인덱스의 스프라이트</returns>
	Sprite* GetSprite(int _index)
	{
		return m_Sprites[_index];
	}


	/// <summary>
	/// 이름으로 된 조건 값을 받아온다
	/// </summary>
	/// <param name="_name">조건 값</param>
	/// <returns>현재 상태</returns>
	bool GetCondition(std::string _name)
	{
		return m_Conditions[_name];
	}

	/// <summary>
	/// 스프라이트를 추가한다
	/// </summary>
	/// <param name="_dataName">추가할 데이터 이름</param>
	/// <param name="_imageName">추가할 이미지 이름</param>
	/// <param name="_folderName">추가할 데이터, 이미지 폴더 이름</param>
	/// <returns>추가한 스프라이트 인덱스를 반환한다</returns>
	int AddSprite(std::wstring _dataName, std::wstring _imageName, std::wstring _folderName)
	{
		int index = m_Sprites.size();

		m_Sprites.push_back(m_GameObject->AddComponent<Sprite>());
		m_Sprites[index]->LoadSprite(_dataName.c_str(), _imageName.c_str(), _folderName.c_str());
		m_Sprites[index]->StopAnimation();
		m_Sprites[index]->SetActive(false);

		return index;
	}

	virtual void Update();
};

