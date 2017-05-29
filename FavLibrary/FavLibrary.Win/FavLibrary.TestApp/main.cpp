// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <stdlib.h>

#include "stdafx.h"

#include "../FavLibrary/Fav.h"

using namespace FavLibrary;

int main()
{
	Fav fav;
	fav.read("C:\\Users\\fx28613\\Desktop\\Sources\\fav-project\\FavLibrary\\FavLibrary.Win\\x64\\Release\\FAVSample2.fav");

	system("pause");

	fav.write("C:\\Users\\fx28613\\Desktop\\Sources\\fav-project\\FavLibrary\\FavLibrary.Win\\x64\\Release\\FAVSample3.fav", FavLibrary::CompressionMode::base64);

	system("pause");

    return 0;
}

