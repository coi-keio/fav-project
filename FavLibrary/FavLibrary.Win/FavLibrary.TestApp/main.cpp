// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <stdlib.h>

#include "stdafx.h"

#include "../FavLibrary/Fav.h"

using namespace FavLibrary;

int main()
{
    printf("1111111111111111111111");
	Fav fav;
	fav.read("C:\\VCProjects\\fav-project\\Sample_FAVs\\disk.fav");

	system("pause");

	fav.write("C:\\VCProjects\\fav-project\\Sample_FAVs\\test.fav", FavLibrary::CompressionMode::base64);

	system("pause");

    return 0;
}

