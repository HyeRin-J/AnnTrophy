#pragma once

class ResourceManager : public SingletonManager<ResourceManager>
{

	int m_CurrIndex = -1;
public:
	std::vector<SpriteData> m_SpritesData;

	std::wstring	LoadFile(PCWSTR path);

	void	SearchObject(const rapidjson::GenericValue< rapidjson::UTF16<> >& crJson);
	void	SearchArray(const rapidjson::GenericValue< rapidjson::UTF16<> >& crJson);
};

