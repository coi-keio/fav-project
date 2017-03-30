// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <stdlib.h>

#include "stdafx.h"

#include "../FavLibrary/Fav.h"

using namespace FavLibrary;

int main()
{
	Fav* fav = new Fav();
	fav->read("C:\\Users\\fx28613\\Desktop\\Sources\\fav-project\\FavLibrary\\FavLibrary.Win\\x64\\Release\\FAVSample_v1.fav");

	system("pause");
    return 0;
}

