#pragma once


#ifndef _CSOUND_H_
#define _CSOUND_H_


#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

class FAudio
{
public:
	static FMOD_SYSTEM* m_sound_system;
	static FAudio* m_instance;
private:
	FMOD_SOUND* m_sound;
	FMOD_CHANNEL* m_channel;

	float m_volume;
	FMOD_BOOL m_bool;
public:
	FAudio();
	FAudio(const char* path, bool loop);
	~FAudio();


	//사운드 key와 파일 이름을 저장할 맵
	std::map<int, const char*>  m_AudioMaps;
	//사운드를 저장할 벡터
	std::vector<FMOD_SOUND*> m_SoundList;

	//사운드 인덱스를 결정할 멤버변수
	int m_SoundIndex;


	void AddSound(const char* _path, bool _loop , FMOD_SOUND* _sound)
	{
		
		if (_loop)
		{
			FMOD_System_CreateSound(m_sound_system, _path, FMOD_LOOP_NORMAL, 0, &_sound);
		}
		else
		{
			FMOD_System_CreateSound(m_sound_system, _path, FMOD_DEFAULT, 0, &_sound);
		}
		
		m_SoundList.push_back(_sound);

		m_channel = nullptr;
		m_volume = SOUND_DEFAULT;
	}
	

	static int Init();
	static int Release();

	int set(const char* path, bool loop);
	int play();
	int pause();
	int resume();
	int stop();
	int volumeUp();
	int volumeDown();
	int Update();
public:
	static FAudio* GetInstance();
	static void FreeIntance();

};

#endif
