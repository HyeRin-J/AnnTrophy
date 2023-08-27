#pragma once

#ifndef PCH_H
#define PCH_H

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//우진이 pch 가져오기
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <Windows.h>
#include <windef.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <math.h>
#include <wincodec.h>

#include <vector>
#include <list>
#include <map>
#include <deque>
#include <queue>


#include <memory>


#include <tchar.h>
#include <atlstr.h>
#include <functional>
#include "fmod.h"



#include "rapidjson/document.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC

//engine framework load
#include "framework.h"

#include "ResourceDefines.h"

///Game

#include "AppManager.h"
#include "SceneObjectManager.h"
#include "GameManager.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Player.h"
#include "MovePlayer.h"
#include "UIManager.h"
#include "FTime.h"
#include "Switch.h"
#include "Gate.h"
#include "Boss.h"

#include "TankBullet.h"
//event
#include "MessageEnum.h"
#include "BTEventMessage.h"

///BehaviorTree
#include "BehaviorTree.h"

//Monster
//#include "Monster.h"
#include "BaseMonster.h"
#include "MeleeMonster.h"
#include "DashMeleeMonster.h"
#include "JumpMeleeMonster.h"
#include "RangedMonster.h"


#include "Sequence.h"
#include "Selector.h"
#include "MessageIdEnum.h"
#include "EventMessage.h"
#include "Checker.h"
#include "Action.h"
#include "MessageChecker.h"

	//monster checkers
#include "DetectChecker.h"
#include "MeleeAttackChecker.h"
#include "MoveChecker.h"
#include "TopPlatformChecker.h"

	//monster Actions
#include "MoveAction.h"
#include "MeleeAttackAction.h"
#include "DashAction.h"
#include "JumpAction.h"
#include "JumpAttackAction.h"
#include "RangeAttackAction.h"

//UIItem
#include "UIManager.h"
#include "Pannel.h"
#include "ItemData.h"

#define ITEM_TYPE_MAX 5

#endif //PCH_H

