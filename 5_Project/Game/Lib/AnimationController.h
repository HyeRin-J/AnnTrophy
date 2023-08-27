#pragma once

class AnimationController : public Component
{
	/// <summary>
	/// ��������Ʈ ���� Ʈ������
	/// </summary>
	struct Transition
	{
		int fromIndex = -1;
		int toIndex = -1;

		/// <summary>
		/// ������ ���� �¾ƾ� transition�� true�� �ȴ�
		/// </summary>
		std::map<std::string, bool> condition;

		bool hasExit = false;

		/// <summary>
		/// ������ ������ �߰��Ѵ�
		/// </summary>
		/// <param name="_name">���� �̸�</param>
		/// <param name="_state">����</param>
		void AddCondition(std::string _name, bool _state)
		{
			condition[_name] = _state;
		}
	};

public:
	//Transition ���� �б�
	std::map<std::string, bool> m_Conditions;

	/// <summary>
	/// �ִϸ��̼� Ŭ����
	/// </summary>
	std::vector<Sprite*> m_Sprites;

	/// <summary>
	/// ���� ������� ��������Ʈ �ε���
	/// </summary>
	int m_CurrIndex = 0;

	/// <summary>
	/// ��������Ʈ ���� ���� ����
	/// </summary>
	std::multimap<int, Transition> m_Transitions;

	/// <summary>
	/// ������ �߰��Ѵ�
	/// </summary>
	/// <param name="_name">�߰��� �̸�</param>
	void AddCondition(std::string _name)
	{
		m_Conditions[_name] = false;
	}

	/// <summary>
	/// Ư�� Ʈ�����ǿ� ������ �߰��Ѵ�
	/// </summary>
	/// <param name="_fromIndex">���� �� �ε���</param>
	/// <param name="_toIndex">���� �� �ε���</param>
	/// <param name="_name">���� �̸�</param>
	/// <param name="_state">���� ����</param>
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
	/// ������ �����Ѵ�
	/// </summary>
	/// <param name="_name">������ ���� �̸�</param>
	/// <param name="_state">������ ����</param>
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
	/// Ʈ�������� �߰��Ѵ�
	/// </summary>
	/// <param name="_fromIndex">���� �� ��������Ʈ �ε���</param>
	/// <param name="_toIndex">���� �� ��������Ʈ �ε���</param>
	/// <returns>�߰��� Ʈ������</returns>
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
	/// Ʈ�������� �����´�
	/// </summary>
	/// <param name="_fromIndex">���� �� �ε��� ����</param>
	/// <param name="_toIndex">���� �� �ε��� ����</param>
	/// <returns>�߰��ߴ� Ʈ������</returns>
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
	/// Ʈ�������� ������ üũ�Ѵ�
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

				//���� �ʱ�ȭ
				
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

				//���� �ʱ�ȭ

				for (auto& con : tr->second.condition)
				{
					m_Conditions[con.first] = false;
				}

				return;
			}
		}
	}

	/// <summary>
	/// ���� ������� ��������Ʈ
	/// </summary>
	/// <returns>���� ������� ��������Ʈ�� ������</returns>
	Sprite* GetCurrentSprite()
	{
		return m_Sprites[m_CurrIndex];
	}

	/// <summary>
	/// �ε��� ������ ��������Ʈ�� ��ȯ
	/// </summary>
	/// <param name="_index">������ �ε���</param>
	/// <returns>�ε����� ��������Ʈ</returns>
	Sprite* GetSprite(int _index)
	{
		return m_Sprites[_index];
	}


	/// <summary>
	/// �̸����� �� ���� ���� �޾ƿ´�
	/// </summary>
	/// <param name="_name">���� ��</param>
	/// <returns>���� ����</returns>
	bool GetCondition(std::string _name)
	{
		return m_Conditions[_name];
	}

	/// <summary>
	/// ��������Ʈ�� �߰��Ѵ�
	/// </summary>
	/// <param name="_dataName">�߰��� ������ �̸�</param>
	/// <param name="_imageName">�߰��� �̹��� �̸�</param>
	/// <param name="_folderName">�߰��� ������, �̹��� ���� �̸�</param>
	/// <returns>�߰��� ��������Ʈ �ε����� ��ȯ�Ѵ�</returns>
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

