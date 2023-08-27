#pragma once

class ResourceManager : public SingletonManager<ResourceManager>
{

	int m_CurrIndex = -1;
public:
	enum LOADMODE
	{
		SPRITE, MAP,
	};

	std::vector<SpriteData> m_SpritesData;
	MapData					m_MapData;

	std::wstring	LoadFile(PCWSTR path, LOADMODE mode = LOADMODE::SPRITE);

	void	SearchObject(const rapidjson::GenericValue< rapidjson::UTF16<> >& crJson, LOADMODE mode = LOADMODE::SPRITE);
	void	SearchArray(const rapidjson::GenericValue< rapidjson::UTF16<> >& crJson, LOADMODE mode = LOADMODE::SPRITE);
};

