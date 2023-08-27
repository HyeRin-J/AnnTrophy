#include "pch.h"

#include "FAudio.h"


FMOD_SYSTEM* FAudio::m_sound_system;

FAudio* FAudio::m_instance = nullptr;

FAudio::FAudio(const char* path, bool loop):m_bool(false)
{
	if (loop) 
	{
		FMOD_System_CreateSound(m_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else {
		FMOD_System_CreateSound(m_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}
	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;
}

FAudio::FAudio()
	:m_bool(false), m_channel(nullptr), m_volume(0), m_sound(nullptr)
{


}

FAudio::~FAudio()
{
	FMOD_Sound_Release(m_sound);
	m_instance->FreeIntance();
}


int FAudio::Init() 
{
	FMOD_System_Create(&m_sound_system);
	FMOD_System_Init(m_sound_system, 32, FMOD_INIT_NORMAL, NULL);

	return 0;
}

int FAudio::Release() 
{
	FMOD_System_Close(m_sound_system);
	FMOD_System_Release(m_sound_system);

	return 0;
}


int FAudio::set(const char* path, bool loop)
{
	if (loop) 
	{
		FMOD_System_CreateSound(m_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else 
	{
		FMOD_System_CreateSound(m_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}

	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;

	return 0;
}

int FAudio::play() 
{
	FMOD_System_PlaySound(m_sound_system, m_sound, NULL, false, &m_channel);

	return 0;
}

int FAudio::pause() 
{
	FMOD_Channel_SetPaused(m_channel, true);

	return 0;
}

int FAudio::resume() 
{
	FMOD_Channel_SetPaused(m_channel, false);

	return 0;
}

int FAudio::stop() 
{
	FMOD_Channel_Stop(m_channel);

	return 0;
}

int FAudio::volumeUp()
{
	if (m_volume < SOUND_MAX) 
	{
		m_volume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}

int FAudio::volumeDown()
{
	if (m_volume > SOUND_MIN) 
	{
		m_volume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}


int FAudio::Update() 
{
	FMOD_Channel_IsPlaying(m_channel, &m_bool);

	if (m_bool) 
	{
		FMOD_System_Update(m_sound_system);
	}

	return 0;
}

FAudio* FAudio::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FAudio();
	}
	return m_instance;
}
void FAudio::FreeIntance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}