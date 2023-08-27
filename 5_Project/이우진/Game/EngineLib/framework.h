#pragma once

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#include "fmod_common.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include "Debug.h"
#define PATH_SOUND std::wstring(_T("../../Resource/Sound/"))

//Volume
#define  _DEFAULT_VOLUME_MIN   (float)1
#define  _DEFAULT_VOLUME_NOMAL (float)50
#define  _DEFAULT_VOLUME_MAX   (float)100
//Frequency
#define  _DEFAULT_FREQUENCY_   (float)44100.00