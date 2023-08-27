#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "SingletonManager.h"
#include "MapData.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "ResourceManager.h"

std::wstring ResourceManager::LoadFile(PCWSTR path, LOADMODE mode)
{
	m_SpritesData.clear();
	m_MapData.Index.clear();
	m_MapData.Attribute.clear();

	m_CurrIndex = -1;

	DWORD numOfByteWritten;

	HANDLE hFileRead = CreateFile(path, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFileRead == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File Open Error!\n"));
		return nullptr;
	}
	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFileRead, &fileSize);
	int size = fileSize.QuadPart / sizeof(WCHAR);

	WCHAR* readBuf = new WCHAR[size + 1];
	ZeroMemory(readBuf, (size + 1) * sizeof(WCHAR));

	//헤더 제거
	ReadFile(hFileRead, readBuf, sizeof(WCHAR) * size, &numOfByteWritten, NULL);

	std::wstring str = readBuf;

	rapidjson::GenericDocument< rapidjson::UTF16<> > Json;
	Json.Parse(readBuf);
	assert(Json.IsObject());

	std::wstring imagePath = Json.MemberBegin()->name.GetString();

	SearchObject(Json, mode);

	delete[] readBuf;
	CloseHandle(hFileRead);

	return 	imagePath;
}

void ResourceManager::SearchObject(const rapidjson::GenericValue<rapidjson::UTF16<>>& Json, LOADMODE mode)
{
	for (auto itr = Json.MemberBegin(); itr < Json.MemberEnd(); ++itr)
	{
		std::wstring  name = itr->name.GetString();
		switch (itr->value.GetType())
		{
		case rapidjson::kObjectType:
		{
			SearchObject(itr->value.GetObject(), mode);
			break;	// Object 타입의 노드 검색
		}
		case rapidjson::kArrayType:
		{
			auto it = itr->value.GetArray().Begin();

			if (name == _T("Pos"))
			{
				m_SpritesData[m_CurrIndex].m_BitmapPos.x = it++->GetInt();
				m_SpritesData[m_CurrIndex].m_BitmapPos.y = it->GetInt();
			}
			else if (name == _T("Size"))
			{
				if (mode == LOADMODE::SPRITE)
				{
					m_SpritesData[m_CurrIndex].m_BitmapSize.width = it++->GetInt();
					m_SpritesData[m_CurrIndex].m_BitmapSize.height = it->GetInt();
				}
				else
				{
					m_MapData.MapSize.width = it++->GetInt();
					m_MapData.MapSize.height = it->GetInt();
				}
			}
			else if (name == _T("Pivot"))
			{
				m_SpritesData[m_CurrIndex].m_Pivot.x = it++->GetInt();
				m_SpritesData[m_CurrIndex].m_Pivot.y = it->GetInt();
			}
			else if (name == _T("Boundary"))
			{

				m_SpritesData[m_CurrIndex].m_Boundary.left = it++->GetInt();
				m_SpritesData[m_CurrIndex].m_Boundary.top = it++->GetInt();
				m_SpritesData[m_CurrIndex].m_Boundary.right = it++->GetInt();
				m_SpritesData[m_CurrIndex].m_Boundary.bottom = it->GetInt();
			}
			else if (name == _T("BackGroundIndex"))
			{
				for (int i = 0; i < itr->value.Capacity(); i++, it++)
				{
					if (it->IsArray())
					{
						auto index = it->Begin();
						m_MapData.Index.push_back(D2D1::Point2F(index++->GetInt(), index->GetInt()));
					}			
				}
			}
			else if (name == _T("Attribute"))
			{
				for (int i = 0; i < itr->value.Capacity(); i++)
				{
					m_MapData.Attribute.push_back(it++->GetInt());
				}
			}
			else
			{
				SearchArray(itr->value.GetArray(), mode);
			}
		}
		case rapidjson::kNumberType:
		{
			// 노드 추가
			if (name == _T("Delay"))
			{
				m_SpritesData[m_CurrIndex].m_delay = itr->value.GetFloat();
			}
		}
		break;
		case rapidjson::kStringType:
		{
			if (name == _T("TileMapName"))
			{
				m_MapData.TileName = itr->value.GetString();
			}
		}
		break;
		default: break;
		}
	}
}

void ResourceManager::SearchArray(const rapidjson::GenericValue<rapidjson::UTF16<>>& Json, LOADMODE mode)
{
	for (rapidjson::GenericValue< rapidjson::UTF16<> >::ConstValueIterator itr = Json.Begin(); itr != Json.End(); ++itr)
	{
		switch (itr->GetType())
		{
		case rapidjson::kObjectType:
		{
			SpriteData tempData;
			++m_CurrIndex;
			m_SpritesData.push_back(tempData);
			SearchObject(itr->GetObject(), mode);
			break;	// Object 타입의 노드 검색
		}
		case rapidjson::kArrayType:
		{
			SearchArray(itr->GetArray(), mode);
			break;	// Array 타입의 노드 검색
		}
		default:
			break;
		}
	}
}
