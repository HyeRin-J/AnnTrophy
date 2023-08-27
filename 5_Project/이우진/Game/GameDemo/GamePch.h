//현재 pch사용은
//visual studio및 sdk에서만 제공해주는 lib헤더'만' 사용할 것이다 
//사용자 헤더나 lib같은 경우는 framework에서 포함 시킬것.

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#ifdef _DEBUG

#ifdef UNICODE
//유니코드
#pragma  comment(lib, "../EngineLib/D3D.lib")
#pragma  comment(lib, "../EngineLib/Fish_Engine_.lib")
#else
#pragma  comment(lib, "../EngineLib/D3D.lib")
#pragma  comment(lib, "../EngineLib/Fish_Engine_.lib")
#endif

#endif
