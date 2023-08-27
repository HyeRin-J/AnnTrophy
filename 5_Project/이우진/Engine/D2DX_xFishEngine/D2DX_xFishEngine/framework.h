#pragma once

#include "SingletonManager.h"
#include "Vector2.h"


#include "Object.h"
#include "Component.h"
#include "FMatrix3x2.h"
#include "Transform.h"
#include "GameObject.h"
#include "D2DGraphics.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "FAudio.h"
#include "EventExcuteSystem.h"
#include "Input.h"
#include "Debug.h"



#pragma comment(lib, "D2DX_xFishEngine.lib")

#define  GraphicEngine D2DGrahpics::GetInstance()