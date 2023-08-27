#include "pch.h"
#include "SingletonManager.h"

#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"

ObjectBuildAlgorithm* Builder::build()
{
	algorithm->CreateObject();

	return algorithm;
};