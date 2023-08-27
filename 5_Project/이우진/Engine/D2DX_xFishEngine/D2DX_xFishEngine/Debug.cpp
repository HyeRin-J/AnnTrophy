#include "pch.h"
#include "Debug.h"
using namespace std;

/// <summary>
/// ����� Ŭ�����Դϴ�
/// �� Ŭ������ �ش簴ü�� ���� ��� ������ ǥ���ϱ� ����
/// ��������� �ַ� ������ ��������� Ȯ���ϴµ� �ָ��Ҷ�
/// ����ϸ� ���ڴ� �;� ��������ϴ�
/// </summary>

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(const char* _msg)
{
	//���ڿ��� ���̸� ������ �޽��ϴ�
	size_t newSize = strlen(_msg);
	//wchar*������ �������� �������ݴϴ�.
	wchar_t* wmsg = new wchar_t[newSize];

	size_t convertChars;

	//��Ƽ����Ʈ�� ���ڿ��� wchar���ڿ��� �ٲ��ִ��Լ�.
	//convertChars = ��ȯ�� ���ڿ� ������ ��������
	//wmsg = ��ȯ�� �����ڵ� ���ڿ� ������ ����
	//newSize = ������ ũ��
	//������ ���� = ��ȯ�� ������ �ִ밳��
	mbstowcs_s(&convertChars, wmsg, newSize, _msg, _TRUNCATE);

	wcout << wmsg << endl;
}

void Debug::LogFormat(const char* _msg, ...)
{
	//��Ư�� �������ڸ� ����Ҷ� �޼����� �޴� �����Դϴ�
	va_list ap;
	va_start(ap, _msg);
	size_t newSize = strlen(_msg);
	wchar_t* wmsg = new wchar_t[newSize];
	size_t convertChars;
	//��Ƽ����Ʈ�� ���ڿ��� wchar���ڿ��� �ٲ��ִ��Լ�.
	mbstowcs_s(&convertChars, wmsg, newSize, _msg, _TRUNCATE);

	int len;
	//vsprint�� ���� ���ڿ��� ���� ��ȯ�մϴ�
	len = _vscwprintf(wmsg, ap) + 2;
	//����ŭ ���۸� ���� �������ݴϴ�
	wchar_t* buffer = new wchar_t[len];
	//len�� ���̸�ŭ ���ڿ�wmsg�� �о�鿩�� buffer�� �����մϴ�.
	vswprintf_s(buffer, len, wmsg, ap);
	va_end(ap);
	//������ ������ ����մϴ�.
	wcout << buffer << endl;

	delete[] buffer;
	buffer = nullptr;
}

void Debug::LogError(const char* _msg)
{

}



