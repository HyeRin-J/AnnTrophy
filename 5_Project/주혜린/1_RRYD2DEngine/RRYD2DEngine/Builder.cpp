#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "BoundShape.h"
#include "BoundRect.h"
#include "BoundCircle.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"

ObjectBuildAlgorithm* Builder::build()
{
	algorithm->CreateObject();

	return algorithm;
};