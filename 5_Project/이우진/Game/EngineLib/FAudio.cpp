#include "pch.h"
#include "framework.h"
#include "SingletonManager.h"
#include "FAudio.h"

/// <summary>
/// ���� �����Դϴ�
/// 
/// </summary>
FMOD_SYSTEM* FAudio::m_sound_system;

#pragma warning(disable:4996)

FAudio::FAudio() : m_Version(0), m_FBool(false) , m_FMBool(false)
{
	m_Result = { };
	m_FVolume = 0;
	m_System = 0;
	

}

FAudio::~FAudio()
{
	FRelease();
}

bool FAudio::SucceededOrWarn(const std::string& message, FMOD_RESULT result)
{
	if (m_Result != FMOD_OK) 
	{
		//std::cerr << message << ": " << result << " " << FMOD_ErrorString(result) << std::endl;
#ifdef _DEBUG
		Debug::LogFormat("%s : result > %s \n", message.c_str(), FMOD_ErrorString(result));
#endif
		return false;
	}
	return true;
}

//Create
bool FAudio::FCreate()
{
	m_Result = FMOD::System_Create(&m_System);
	if (!SucceededOrWarn("FMOD: Failed to create system object", m_Result))
	{
		return true;
	}
#ifdef _DEBUG
	Debug::LogFormat("Success Fmod Create \n");
#endif
	return false;
}
/// <summary>
/// fmod�� �ʱ�ȭ ���ִ� �Լ��Դϴ�.
/// </summary>
/// <returns></returns>
bool FAudio::FInit()
{
	m_FBool = true;
	m_FMBool = true;
	//�ý����� ������ �޽��ϴ�.
	m_Result = m_System->getVersion(&m_Version);
	
	if (m_Version < FMOD_VERSION)
	{
#ifdef _DEBUG
		Debug::LogFormat("FMOD lib version %08x doesn't match header version %08x", m_Version, FMOD_VERSION);
#endif
	}
	m_Result = m_System->init(512, FMOD_INIT_NORMAL, nullptr);
	//Result�� �ùٸ� �� (0) �� �ƴѰ��� ��ȯ���� �� ������ �Լ�
	if (!SucceededOrWarn("FMOD: Failed to initialise system object", m_Result))
	{
		return true;
	}
#ifdef _DEBUG
	Debug::LogFormat("Success Fmod initialise \n");
#endif
	return false;
}
/// <summary>
/// ��θ� ã�� ���� ������ �������ִ� �Լ��Դϴ�.
/// </summary>
/// <param name="_name">�̸��� �������ݴϴ�.�Ʒ� ���ڿ��� �⺻ ��η� �����Ǿ��ֽ��ϴ�. </param>
/// <param name="_loop">�ݺ����θ� ����� bool �����Դϴ�. </param>
/// <param name="_sound">�ش� ���� ������ �ּҸ� �޽��ϴ�.</param>
/// <returns></returns>
bool FAudio::FCreateSound(std::wstring _name, bool _loop, FMOD::Sound** _sound, std::wstring _folder)
{
	//�⺻��θ� ���մϴ�.
	std::wstring _path;
	_path.append(PATH_SOUND);

	if (_folder.size() > 0)
	{
		_path.append(_folder);
		_path.append(_T("/"));
	}

	_path.append(_name);

	HANDLE hFile = nullptr;

	hFile = CreateFile(_path.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	//CREATE_NEW = �� ������ �������� ��쿡�� �����մϴ�.
	CloseHandle(hFile);
	/*
	HANDLE hFile = nullptr;	
	hFile = CreateFile(_T("../../Resource/Sound/"), GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//CREATE_NEW = �� ������ �������� ��쿡�� �����մϴ�.
	CloseHandle(hFile);
	*/
	//w to m�� ���� ��ȯ �Ŀ� �⺻��ο��� ���� ���� �̸��� �����ϱ� ���� �����Դϴ�.
	int strSize = WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, NULL, 0, NULL, NULL) + 1;

	LPSTR _tempChar = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, _tempChar, strSize, 0, 0);
#ifdef _DEBUG
	Debug::LogFormat("before Creating Fmod Sound : %s\n", _tempChar);
	//���� ��
#endif
	if (_loop)
	{
		//ex) _tempChar = test.wav ���ϸ� �Էµ�
		m_Result = m_System->createSound((_tempChar), FMOD_LOOP_NORMAL, nullptr, _sound);
#ifdef _DEBUG
		Debug::LogFormat("SoundLoop(true)");
#endif
	}
	else
	{
		m_Result = m_System->createSound((_tempChar), FMOD_DEFAULT, nullptr, _sound);
#ifdef _DEBUG
		Debug::LogFormat("SoundLoop(false)");
#endif
	}

	if (*_sound == nullptr)
	{
#ifdef _DEBUG
		Debug::Log("don't Create SoundResource");
#endif
		return false;
	}
	else
	{
#ifdef _DEBUG
		Debug::LogFormat("Success Fmod CreateSound \n");
		Debug::LogFormat("After Fmod CreateSound is Name : %s \n", _tempChar);
		std::wcout << "After Fmod Path " << _path << std::endl;
#endif
	}
	
	if (!SucceededOrWarn("FMOD: Failed to Create object\n", m_Result))
	{
		return true;
	}


	return true;
}

/// <summary>
/// ���带 �߰����ִ� �Լ��Դϴ�.
/// </summary>
/// <param name="_path">�Ķ���ʹ� path������.. ���� �̸��� �־��ָ�˴ϴ�.</param>
/// <param name="_loop">�ݺ����θ� �����ϴ�</param>
/// <returns></returns>
bool FAudio::FAddSound(std::wstring _path, bool _loop, std::wstring _folder)
{
	FMOD::Sound* soundPtr = nullptr;


	std::wstring _Folderpath_;
	_Folderpath_.append(PATH_SOUND);

	if (_folder.size() > 0)
	{
		_Folderpath_.append(_folder);
		_Folderpath_.append(_T("/"));
	}

	_Folderpath_.append(_path);

	if (FCreateSound(_path, _loop, &soundPtr, _folder))
	{
#ifdef _DEBUG
		std::wcout << "input addSoundPath : "<<_path << endl;
#endif

		m_AudioMap.emplace(std::pair<std::wstring, FMOD::Sound*>(_path, soundPtr));
		const auto& sound_ptr = m_AudioMap[_path];
		FMOD::Channel* channel_ptr = m_ChannelMap[soundPtr];
		//FMOD::SOUND*�� ä���� �˱����� �ε����� �����Ѵ�.
		
		//�ش� ä�ΰ�ü�� �ִ��� �˻����ִ� �Լ�
		

		m_Result = m_System->playSound(sound_ptr, nullptr, false, &channel_ptr);
		if (FCheckChannel(&channel_ptr))
		{
#ifdef _DEBUG
			Debug::Log("ä�� �˻� ��\n");
#endif
		}
		m_Result = channel_ptr->stop();
		m_ChannelMap.emplace(std::pair<FMOD::Sound*, FMOD::Channel*>(soundPtr, channel_ptr));
#ifdef _DEBUG
		Debug::LogFormat("FAddSound =>\n channel_ptr : %p \n", channel_ptr);
#endif
	}
	return false;
}

bool FAudio::FAddBackground(std::wstring _path, bool _loop, FMOD::Channel** _channel, std::wstring _folder)
{
	static int index = 0;

	FMOD::Sound* soundPtr = nullptr;

	if (FCreateSound(_path, _loop, &soundPtr, _folder))
	{
#ifdef _DEBUG
		std::wcout << "input addSoundPath : " << _path << endl;
#endif

		m_AudioMap.emplace(std::pair<std::wstring, FMOD::Sound*>(_path, soundPtr));
		const auto& sound_ptr = m_AudioMap[_path];
		FMOD::Channel* channel_ptr = m_ChannelMap[soundPtr];
		//FMOD::SOUND*�� ä���� �˱����� �ε����� �����Ѵ�.

		//�ش� ä�ΰ�ü�� �ִ��� �˻����ִ� �Լ�
		if (FCheckChannel(&channel_ptr))
		{
#ifdef _DEBUG
			Debug::Log("ä�� �˻� ��\n");
#endif
		}

		m_Result = m_System->playSound(sound_ptr, nullptr, false, _channel);
		(*_channel)->setPaused(true);
		m_ChannelMap.emplace(std::pair<FMOD::Sound*, FMOD::Channel*>(soundPtr, *_channel));
#ifdef _DEBUG
		Debug::LogFormat("FAddSound =>\n channel_ptr : %p \n", _channel);
#endif
		index++;
	}
	return false;
}

bool FAudio::FPlaySound(std::wstring _path)
{	
	
	if (FFindChannel(_path, SOUND_PLAY::PLAY))//�ش�ʰ� ä���� �ִ��� �˻�
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ����� ������ ä���� ã�� ��������� �ɼ��� �����ϴ� �Լ��̴�. 
/// </summary>
/// <param name="_inAudio"></param>
/// <param name="_inChannel"></param>
/// <param name="_path"></param>
/// <param name="_Set"></param>
/// <returns></returns>
bool FAudio::FFindChannel(std::wstring& _path, SOUND_PLAY _Set)
{
	if (m_AudioMap.count(_path) <= 0)
	{
#ifdef _DEBUG
		std::wcout << "���� ��� : " << _path << endl;
		std::wcout << _path << " �ʱ�ȭ ����" << std::endl;;
#endif
	}
	const auto& const sound_ptr = m_AudioMap[_path];
	const auto& const channel_ptr = m_ChannelMap[sound_ptr];

	Debug::LogFormat("FFindChannel =>\n (*k).second  : %p \n", channel_ptr);

	//���尡 �������̸� ���� 
	bool is_playing = false;
	m_Result = channel_ptr->isPlaying(&is_playing);
	if (channel_ptr->isPlaying(&is_playing) == false)
	{
#ifdef _DEBUG
		Debug::Log("FFindChannel : ���尡 �̹� ����� \n");
#endif
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FFindChannel : ���尡 �̹� ������� �ƴ� \n");
#endif
	}

	
	float _Frequencying = 0.0f;

	//std::map<FMOD::Sound*, FMOD::Channel*>::iterator k = _inChannel.find(_inAudio[_path]);
	std::map<FMOD::Sound*, FMOD::Channel*>::iterator k = m_ChannelMap.find(sound_ptr);
	
	switch (_Set)
	{
	case FAudio::SOUND_PLAY::PLAY:
		FCheckChannel(&(*k).second);
		m_Result = m_System->playSound((*k).first, nullptr, false, &(*k).second);
		break;
	case FAudio::SOUND_PLAY::STOP:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->stop();
		break;
	case FAudio::SOUND_PLAY::PAUSE:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setPaused(true);
		break;
	case FAudio::SOUND_PLAY::RESUME:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setPaused(false);
		break;
	case FAudio::SOUND_PLAY::VOLUME_SET:
		//������ ���� up || down ��Ű��
		//���ļ��� �����Ǽ� �Ҹ��� ���� ������ ������ �־.
		//���� set���� �������� �������ش�.
		//�Ҹ� ������� 0~1�����̴�
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_NOMAL);//10;
		break;
	case FAudio::SOUND_PLAY::VOLUME_MIN:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_MIN);//1
		break;
	case FAudio::SOUND_PLAY::VOLUME_MAX:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_MAX);//100 (�̷��� ���� Ű��� ����?�Ǿ �Ҹ��� ����.)
		break;
	case FAudio::SOUND_PLAY::FREQUENCY_SET:
		FCheckChannel(&(*k).second);
		//���⼭ �������� ���� �ʱ�ȭ�Ѵ�.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying = _DEFAULT_FREQUENCY_;//(48000.00f)
		m_Result = (*k).second->setFrequency(_Frequencying);
		break; 
	case FAudio::SOUND_PLAY::FREQUENCY_UP:
		FCheckChannel(&(*k).second);
		//���⼭ �������� ���� �����Ѵ�.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying += 1000;
		m_Result = (*k).second->setFrequency(_Frequencying);
		break;
	case FAudio::SOUND_PLAY::FREQUENCY_DOWN:
		FCheckChannel(&(*k).second);
		//���⼭ �������� ���� �����Ѵ�.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying -= 1000;
		m_Result = (*k).second->setFrequency(_Frequencying);
		break;
	}

	if ( FCheckAudio(m_ChannelMap, sound_ptr) )
	{
#ifdef _DEBUG
		Debug::Log("ä�� üũ �̻����\n");
#endif
	}
	Debug::Log("����������� ���� �̻����\n");
	return true;
}
/// <summary>
/// audio ���� ���� ������ �ִ��� �˻��ϴ��Լ�
/// </summary>
/// <param name="_CheckMap"></param>
/// <param name="_Sndptr"></param>
/// <returns></returns>
bool FAudio::FCheckAudio(std::map<FMOD::Sound*, FMOD::Channel*>& _CheckMap, FMOD::Sound* const& _Sndptr)
{
	std::map<FMOD::Sound*, FMOD::Channel*>::iterator k = _CheckMap.find(_Sndptr);

	//�ش� ���尡 ����ִ°��
	if (_CheckMap.find(_Sndptr) == _CheckMap.end())
	{
		Debug::Log("�� ���� ���尡 �������� ���� \n");
		return false;
	}
	else
	{
		if ((*k).second == nullptr)
		{
			Debug::Log("FCheckAudio : ���� ä���� ������������ \n");
			return false;
		}
		Debug::LogFormat("FCheckAudio =>\n (*k).second  : %p \n", (*k).second);
		FCheckChannel(&(*k).second);
		Debug::Log("FCheckAudio : ���尡 ������\n");

		return true;
	}
	if (!SucceededOrWarn("FCheckAudio : ���� Ž���� ���� �߻���\n", m_Result))
	{
		return false;
	}
	if (m_Result != FMOD_OK)
	{
#ifdef _DEBUG
		Debug::Log("FCheckAudio :�ý��� ��� ���� \n");
#endif
	}
	return false;
}
/// <summary>
/// ä���� �ּҰ� �ִ��� �˻��ϴ��Լ�
/// </summary>
/// <param name="_Chennel"></param>
/// <returns></returns>
bool FAudio::FCheckChannel(FMOD::Channel** _Chennel)
{
	if ((*_Chennel) == nullptr)
	{
#ifdef _DEBUG
		Debug::Log("FCheckChannel : �ش� ä�� ��ü�� ����ֽ��ϴ�.\n");
#endif
		return false;
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FCheckChannel : �ش� ä�� ��ü�� �����մϴ�.\n");
#endif
		return true;
	}
	return false;
}
/// <summary>
/// ���� ������ �ִ��� �˻��ϴ��Լ�
/// </summary>
/// <param name="_Sound"></param>
/// <returns></returns>
bool FAudio::FCheckSound(FMOD::Sound** _Sound)
{
	if ((*_Sound) == nullptr)
	{
#ifdef _DEBUG
		Debug::Log("FCheckSound : �ش� ���� ��ü�� ����ֽ��ϴ�.\n");
#endif
		return false;
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FCheckSound : �ش� ���� ��ü�� �����մϴ�.\n");
#endif
		return true;
	}
	return false;
}

/// <summary>
/// ���� ���� ������ �����մϴ�.
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FSetVolume(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::VOLUME_SET))
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ���� Frequency�� Defualt������ �����մϴ�.
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FSetFrequency(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::FREQUENCY_SET))//�ش�ʰ� ä���� �ִ��� �˻�
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ���� Frequency�� �����մϴ� ��������
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FSetFrequencyUP(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::FREQUENCY_UP))
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ���� Frequency�� �ٿ��մϴ� ���Ӱ��� = 0���Ϸ� �������� �����
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FSetFrequencyDown(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::FREQUENCY_DOWN))
	{
		return true;
	}
	return false;
}
bool FAudio::FIsPlaying(std::wstring _path)
{
	const auto& const sound_ptr = m_AudioMap[_path];
	const auto& const channel_ptr = m_ChannelMap[sound_ptr];
#ifdef _DEBUG
	Debug::LogFormat("FFindChannel =>\n (*k).second  : %p \n", channel_ptr);
#endif
	//���尡 �������̸� ���� 
	bool is_playing = false;
	channel_ptr->isPlaying(&is_playing);
	return is_playing;
}
/// <summary>
/// ���� ���� �Ͻ�����
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FPause(std::wstring _path)
{
	if (FFindChannel(_path,SOUND_PLAY::PAUSE))//�ش�ʰ� ä���� �ִ��� �˻�
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ���� ����(������ �ʱ�ȭ)
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FStop(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::STOP))//�ش�ʰ� ä���� �ִ��� �˻�
	{
		return true;
	}
	return false;
}
/// <summary>
/// ���� ���� �����
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FResume(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::RESUME))
	{
		return true;
	}
	
	return false;
}
/// <summary>
/// FMOD�� ������� ���� ������ ���� UPDATE �Լ��Դϴ�.
/// �ַ� �ݺ����� �־��ָ�˴ϴ�.
/// </summary>
/// <returns></returns>
bool FAudio::FUpdate()
{
	for (auto k = m_ChannelMap.begin(); k != m_ChannelMap.end(); k++)
	{
		(*k).second->isPlaying(&m_FMBool);
	}
	m_Result = m_System->update();
	return false;
}

/// <summary>
/// FMod����� �����ϱ� �� �ʱ�ȭ�����ݴϴ�.
/// </summary>
/// <returns></returns>
bool FAudio::FRelease()
{
	m_AudioMap.clear();
	m_ChannelMap.clear();
	m_PathList.clear();
	m_Result =  m_System->close();
	m_Result =  m_System->release();

	return false;
}
/// <summary>
/// ���ڿ��� ��ȯ���ִ� �Լ��Դϴ�. w to m
/// </summary>
/// <param name="_msg"></param>
/// <returns></returns>
LPSTR FAudio::WidetoMulti_FormatTxt(const wchar_t* _msg)
{
	int strSize = WideCharToMultiByte(CP_ACP, 0, _msg, -1, NULL, 0, NULL, NULL) + 1;
	LPSTR _tempChar = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, _msg, -1, _tempChar, strSize, 0, 0);

	return _tempChar;
}

/// <summary>
/// FAddSound�� ��ϵ� �Լ����� ��� �����ϴ� �Լ��Դϴ�.
/// </summary>
/// <param name="_start">����Լ��� ����/������ ���θ� �����մϴ�.</param>
/// <returns></returns>
bool FAudio::FSoundAllPlay(bool _start)
{
	for (auto k = m_AudioMap.begin(); k != m_AudioMap.end(); k++)
	{
		FCheckSound(&(*k).second);

		LPSTR _tempChar = WidetoMulti_FormatTxt((*k).first.c_str());
#ifdef _DEBUG
		Debug::LogFormat("All Play to Resource Sound  : %s .... \n", _tempChar);
#endif
		//�������ִ� ä�κ��� ��ü�� ��ȯ�Ѵ�./
		for (auto inx = m_ChannelMap.begin(); inx != m_ChannelMap.end(); inx++)
		{
			if (m_Result != FMOD_OK)
			{
#ifdef _DEBUG
				Debug::Log("Map in Wrong File  .\n");
				Debug::LogFormat("not found sound :  %d.\n", m_Result);
#endif
				continue;
			}
			m_Result = m_System->playSound((*inx).first, nullptr, false, &(*inx).second);
			if (!_start)
			{
				(*inx).second->stop();
			}
#ifdef _DEBUG
			Debug::LogFormat("starting : sound  %d.\n", m_Result);
#endif
		}
		//FMOD_System_PlaySound(m_sound_system, (*k).second, NULL, false, &m_channel);
	}

	return false;
}