// ConsoleApplication1.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

