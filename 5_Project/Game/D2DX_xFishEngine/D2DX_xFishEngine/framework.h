#pragma once

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include "SingletonManager.h"
#include "Vector.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteData.h"
#include "D2DGraphics.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "AnimationController.h"
#include "FAudio.h"
#include "EventExcuteSystem.h"
#include "ObjectManager.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"
#include "InputManager.h"
#include "Debug.h"
#include "FTime.h"
#include "MapData.h"
#include "TileType.h"
#include "Scene.h"
#include "LoadSceneManager.h"
#include "Pannel.h"
#include "FText.h"



#pragma comment(lib, "D2DX_xFishEngine.lib")

#define PATH_UNI_STR std::wstring(_T("../"))
#define PATH_RESOURCE_STR std::wstring(_T("../../Resource/"))

//만약 다른곳에 경로를 원할때를 대비해서 주석처리.
#define PATH_SOUND std::wstring(_T("../../Resource/Sound/"))

//JSON파일 관련 함수 매개변수가 틀려서 이곳은 변경X
#define PATH_IMAGE_UNI _T("../../Resource/Image/")
#define PATH_MAP_UNI _T("../../Resource/Map/")

#define _FixedUpdate FTime::GetInstance()->FixedUpdate()
#define _FTime FTime::GetInstance()
#define _GameManager GameManager::GetInstance()
#define _FAudio FAudio::GetInstance()


#define  _GraphicEngine D2DGraphics::GetInstance()

//Volume
#define  _DEFAULT_VOLUME_MIN   (float)1
#define  _DEFAULT_VOLUME_NOMAL (float)50
#define  _DEFAULT_VOLUME_MAX   (float)100
//Frequency
#define  _DEFAULT_FREQUENCY_   (float)44100.00

#pragma region INPUT_MAPPING

#define VK_TAB 0x09 //Horizon Tab
#define VK_ESC 0x1B //ESC
#define VK_SPACE 0x20 //Space

//대문자
#define VK_A 0x41 //A
#define VK_B 0x42 //B
#define VK_C 0x43 //C
#define VK_D 0x44 //D
#define VK_E 0x45 //E
#define VK_F 0x46 //F
#define VK_G 0x47 //G
#define VK_H 0x48 //H
#define VK_I 0x49 //I
#define VK_J 0x4a //J
#define VK_K 0x4b //K
#define VK_L 0x4c //L
#define VK_M 0x4d //M
#define VK_N 0x4e //N
#define VK_O 0x4f //O
#define VK_P 0x50 //P
#define VK_Q 0x51 //Q
#define VK_R 0x52 //R
#define VK_S 0x53 //S
#define VK_T 0x54 //T
#define VK_U 0x55 //U
#define VK_V 0x56 //V
#define VK_W 0x57 //W
#define VK_X 0x58 //X
#define VK_Y 0x59 //Y
#define VK_Z 0x5a //Z

//소문자
#define VK_a 0x61 //a
#define VK_b 0x62 //b
#define VK_c 0x63 //c
#define VK_d 0x64 //d
#define VK_e 0x65 //e
#define VK_f 0x67 //f
#define VK_g 0x68 //g
#define VK_h 0x69 //h
#define VK_i 0x6a //i
#define VK_j 0x6b //j
#define VK_k 0x6c //k
#define VK_l 0x6d //l
#define VK_m 0x6e //m
#define VK_n 0x6f //n
#define VK_o 0x70 //o
#define VK_p 0x71 //p
#define VK_q 0x72 //q
#define VK_r 0x73 //r
#define VK_s 0x74 //s
#define VK_t 0x75 //t
#define VK_u 0x76 //u
#define VK_v 0x77 //v
#define VK_w 0x78 //w
#define VK_x 0x79 //x
#define VK_y 0x79 //y
#define VK_z 0x79 //z

//숫자
#define VK_NUM_0 0x30 //0
#define VK_NUM_1 0x31 //1
#define VK_NUM_2 0x32 //2
#define VK_NUM_3 0x33 //3
#define VK_NUM_4 0x34 //4
#define VK_NUM_5 0x35 //5
#define VK_NUM_6 0x36 //6
#define VK_NUM_7 0x37 //7
#define VK_NUM_8 0x38 //8
#define VK_NUM_9 0x39 //9


#pragma endregion
