#pragma once
/// <summary>
/// �������� �����͸� ���� ����ü
/// </summary>
struct ItemData
{
	int m_Index;//n��° ������
	int m_Upgrade = 0;

	ID2D1Bitmap* m_Bitmap;//��Ʈ���� ������
	std::wstring m_Name;//�̹��� ������ �̸�
	std::wstring m_Des;//�߰� ���� �� ��Ÿ������ ���ڿ�
	
	enum class UPGRADE
	{
		_NONE = 0,
		_DAMAGE,	 //�⺻ ������ ����
		_MAX,		 //źȯ �ִ� ���� ����
		_SPEED,		 //���� ���ǵ� ����
		_LENGTH,	 //���� ��Ÿ� ����
		_OVERLO		 //�����ε� �ӵ�����.
	};
	


};
