// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>

#include "../../FavLibrary/FavSettings.h"

using namespace FavLibrary;

#pragma comment(lib, "FavLibrary.lib")

#ifdef _DEBUG
#pragma comment(lib, "xerces-c_3D.lib")
#else
#pragma comment(lib, "xerces-c_3.lib")
#endif

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
