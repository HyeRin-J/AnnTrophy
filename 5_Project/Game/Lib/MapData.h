#pragma once
#include "pch.h"

struct MapData
{
	std::wstring TileName;
	std::wstring BackGroundName;
	D2D1_SIZE_F MapSize;
	std::vector<D2D1_POINT_2F> Index;
	std::vector<int> Attribute;
};

