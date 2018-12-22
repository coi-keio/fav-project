// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <stdlib.h>

#include "stdafx.h"

#include "../FavLibrary/Fav.h"

using namespace FavLibrary;

int main()
{
	Fav fav;
	//fav.read("..\\..\\..\\..\\Sample_FAVs\\Cone.fav");
	fav.read("..\\..\\..\\..\\Sample_FAVs\\disk_for_reftest.fav");
	//fav.read("../../../../Sample_FAVs/disk.fav");

	system("pause");

	fav.write("../../../../Sample_FAVs/test.fav", FavLibrary::CompressionMode::base64);

	system("pause");

    return 0;
}

