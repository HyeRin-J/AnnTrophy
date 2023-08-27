#include "pch.h"
#include "framework.h"
#include "SingletonManager.h"
#include "FAudio.h"

/// <summary>
/// 사운드 엔진입니다
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
/// fmod를 초기화 해주는 함수입니다.
/// </summary>
/// <returns></returns>
bool FAudio::FInit()
{
	m_FBool = true;
	m_FMBool = true;
	//시스템의 버전을 받습니다.
	m_Result = m_System->getVersion(&m_Version);
	
	if (m_Version < FMOD_VERSION)
	{
#ifdef _DEBUG
		Debug::LogFormat("FMOD lib version %08x doesn't match header version %08x", m_Version, FMOD_VERSION);
#endif
	}
	m_Result = m_System->init(512, FMOD_INIT_NORMAL, nullptr);
	//Result가 올바른 값 (0) 이 아닌값을 반환했을 때 나오는 함수
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
/// 경로를 찾고 사운드 파일을 생성해주는 함수입니다.
/// </summary>
/// <param name="_name">이름을 지정해줍니다.아래 문자열이 기본 경로로 설정되어있습니다. </param>
/// <param name="_loop">반복여부를 물어보는 bool 변수입니다. </param>
/// <param name="_sound">해당 사운드 파일의 주소를 받습니다.</param>
/// <returns></returns>
bool FAudio::FCreateSound(std::wstring _name, bool _loop, FMOD::Sound** _sound, std::wstring _folder)
{
	//기본경로를 더합니다.
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
	//CREATE_NEW = 새 파일이 아직없는 경우에만 생성합니다.
	CloseHandle(hFile);
	/*
	HANDLE hFile = nullptr;	
	hFile = CreateFile(_T("../../Resource/Sound/"), GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//CREATE_NEW = 새 파일이 아직없는 경우에만 생성합니다.
	CloseHandle(hFile);
	*/
	//w to m을 위한 변환 후에 기본경로에서 사운드 파일 이름만 추출하기 위한 과정입니다.
	int strSize = WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, NULL, 0, NULL, NULL) + 1;

	LPSTR _tempChar = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, _path.c_str(), -1, _tempChar, strSize, 0, 0);
#ifdef _DEBUG
	Debug::LogFormat("before Creating Fmod Sound : %s\n", _tempChar);
	//추출 끝
#endif
	if (_loop)
	{
		//ex) _tempChar = test.wav 파일만 입력됨
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
/// 사운드를 추가해주는 함수입니다.
/// </summary>
/// <param name="_path">파라미터는 path이지만.. 사운드 이름을 넣어주면됩니다.</param>
/// <param name="_loop">반복여부를 묻습니다</param>
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
		//FMOD::SOUND*의 채널을 알기위해 인덱스로 접근한다.
		
		//해당 채널객체가 있는지 검사해주는 함수
		

		m_Result = m_System->playSound(sound_ptr, nullptr, false, &channel_ptr);
		if (FCheckChannel(&channel_ptr))
		{
#ifdef _DEBUG
			Debug::Log("채널 검사 끝\n");
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
		//FMOD::SOUND*의 채널을 알기위해 인덱스로 접근한다.

		//해당 채널객체가 있는지 검사해주는 함수
		if (FCheckChannel(&channel_ptr))
		{
#ifdef _DEBUG
			Debug::Log("채널 검사 끝\n");
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
	
	if (FFindChannel(_path, SOUND_PLAY::PLAY))//해당맵과 채널이 있는지 검사
	{
		return true;
	}
	return false;
}
/// <summary>
/// 현재 등록한 파일의 채널을 찾아 재생여부의 옵션을 결정하는 함수이다. 
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
		std::wcout << "들어온 경로 : " << _path << endl;
		std::wcout << _path << " 초기화 실패" << std::endl;;
#endif
	}
	const auto& const sound_ptr = m_AudioMap[_path];
	const auto& const channel_ptr = m_ChannelMap[sound_ptr];

	Debug::LogFormat("FFindChannel =>\n (*k).second  : %p \n", channel_ptr);

	//사운드가 실행중이면 종료 
	bool is_playing = false;
	m_Result = channel_ptr->isPlaying(&is_playing);
	if (channel_ptr->isPlaying(&is_playing) == false)
	{
#ifdef _DEBUG
		Debug::Log("FFindChannel : 사운드가 이미 재생중 \n");
#endif
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FFindChannel : 사운드가 이미 재생중이 아님 \n");
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
		//볼륨을 따로 up || down 시키면
		//주파수가 변질되서 소리가 많이 깨지는 현상이 있어서.
		//따로 set으로 볼륨량을 조절해준다.
		//소리 사이즈는 0~1사이이다
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_NOMAL);//10;
		break;
	case FAudio::SOUND_PLAY::VOLUME_MIN:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_MIN);//1
		break;
	case FAudio::SOUND_PLAY::VOLUME_MAX:
		FCheckChannel(&(*k).second);
		m_Result = (*k).second->setVolume(_DEFAULT_VOLUME_MAX);//100 (이렇게 까지 키우면 변질?되어서 소리가 깨짐.)
		break;
	case FAudio::SOUND_PLAY::FREQUENCY_SET:
		FCheckChannel(&(*k).second);
		//여기서 프리퀀시 값을 초기화한다.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying = _DEFAULT_FREQUENCY_;//(48000.00f)
		m_Result = (*k).second->setFrequency(_Frequencying);
		break; 
	case FAudio::SOUND_PLAY::FREQUENCY_UP:
		FCheckChannel(&(*k).second);
		//여기서 프리퀀시 값을 조정한다.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying += 1000;
		m_Result = (*k).second->setFrequency(_Frequencying);
		break;
	case FAudio::SOUND_PLAY::FREQUENCY_DOWN:
		FCheckChannel(&(*k).second);
		//여기서 프리퀀시 값을 조정한다.
		m_Result = (*k).second->getFrequency(&_Frequencying);
		_Frequencying -= 1000;
		m_Result = (*k).second->setFrequency(_Frequencying);
		break;
	}

	if ( FCheckAudio(m_ChannelMap, sound_ptr) )
	{
#ifdef _DEBUG
		Debug::Log("채널 체크 이상없음\n");
#endif
	}
	Debug::Log("최종결과까지 사운드 이상없음\n");
	return true;
}
/// <summary>
/// audio 맵의 사운드 파일이 있는지 검사하는함수
/// </summary>
/// <param name="_CheckMap"></param>
/// <param name="_Sndptr"></param>
/// <returns></returns>
bool FAudio::FCheckAudio(std::map<FMOD::Sound*, FMOD::Channel*>& _CheckMap, FMOD::Sound* const& _Sndptr)
{
	std::map<FMOD::Sound*, FMOD::Channel*>::iterator k = _CheckMap.find(_Sndptr);

	//해당 사운드가 비어있는경우
	if (_CheckMap.find(_Sndptr) == _CheckMap.end())
	{
		Debug::Log("맵 안의 사운드가 존재하지 않음 \n");
		return false;
	}
	else
	{
		if ((*k).second == nullptr)
		{
			Debug::Log("FCheckAudio : 사운드 채널이 존재하지않음 \n");
			return false;
		}
		Debug::LogFormat("FCheckAudio =>\n (*k).second  : %p \n", (*k).second);
		FCheckChannel(&(*k).second);
		Debug::Log("FCheckAudio : 사운드가 존재함\n");

		return true;
	}
	if (!SucceededOrWarn("FCheckAudio : 사운드 탐색중 에러 발생함\n", m_Result))
	{
		return false;
	}
	if (m_Result != FMOD_OK)
	{
#ifdef _DEBUG
		Debug::Log("FCheckAudio :시스템 결과 에러 \n");
#endif
	}
	return false;
}
/// <summary>
/// 채널의 주소가 있는지 검사하는함수
/// </summary>
/// <param name="_Chennel"></param>
/// <returns></returns>
bool FAudio::FCheckChannel(FMOD::Channel** _Chennel)
{
	if ((*_Chennel) == nullptr)
	{
#ifdef _DEBUG
		Debug::Log("FCheckChannel : 해당 채널 객체는 비어있습니다.\n");
#endif
		return false;
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FCheckChannel : 해당 채널 객체는 존재합니다.\n");
#endif
		return true;
	}
	return false;
}
/// <summary>
/// 사운드 파일이 있는지 검사하는함수
/// </summary>
/// <param name="_Sound"></param>
/// <returns></returns>
bool FAudio::FCheckSound(FMOD::Sound** _Sound)
{
	if ((*_Sound) == nullptr)
	{
#ifdef _DEBUG
		Debug::Log("FCheckSound : 해당 사운드 객체는 비어있습니다.\n");
#endif
		return false;
	}
	else
	{
#ifdef _DEBUG
		Debug::Log("FCheckSound : 해당 사운드 객체는 존재합니다.\n");
#endif
		return true;
	}
	return false;
}

/// <summary>
/// 현재 사운드 볼륨을 설정합니다.
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
/// 현재 사운드 Frequency를 Defualt값으로 설정합니다.
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FSetFrequency(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::FREQUENCY_SET))//해당맵과 채널이 있는지 검사
	{
		return true;
	}
	return false;
}
/// <summary>
/// 현재 사운드 Frequency를 증가합니다 음속증가
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
/// 현재 사운드 Frequency를 다운합니다 음속감소 = 0이하로 내려갈시 역재생
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
	//사운드가 실행중이면 종료 
	bool is_playing = false;
	channel_ptr->isPlaying(&is_playing);
	return is_playing;
}
/// <summary>
/// 현재 사운드 일시정지
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FPause(std::wstring _path)
{
	if (FFindChannel(_path,SOUND_PLAY::PAUSE))//해당맵과 채널이 있는지 검사
	{
		return true;
	}
	return false;
}
/// <summary>
/// 현재 사운드 멈춤(시작점 초기화)
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
bool FAudio::FStop(std::wstring _path)
{
	if (FFindChannel(_path, SOUND_PLAY::STOP))//해당맵과 채널이 있는지 검사
	{
		return true;
	}
	return false;
}
/// <summary>
/// 현재 사운드 재시작
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
/// FMOD의 무한재생 사운드 파일을 위한 UPDATE 함수입니다.
/// 주로 반복문에 넣어주면됩니다.
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
/// FMod사용을 종료하기 전 초기화를해줍니다.
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
/// 문자열을 변환해주는 함수입니다. w to m
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
/// FAddSound로 등록된 함수들을 모두 실행하는 함수입니다.
/// </summary>
/// <param name="_start">모든함수를 시작/안함을 여부를 결정합니다.</param>
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
		//가지고있는 채널별로 전체를 순환한다./
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