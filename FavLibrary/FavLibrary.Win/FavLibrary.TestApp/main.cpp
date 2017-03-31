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

	//Fav out = Fav();
	//out.setMetadataId("idAAA");
	//out.setMetadataAuthor("authorBBB");
	//out.setMetadataTitle("titleCCC");
	//out.setMetadataLicense("OKOKOK");
	//out.setMetadataNote("notenotenote");

	//Geometry gmr = Geometry(1, "ABCABC");
	//gmr.setScale(1, 1, 1.5);
	//gmr.setShape(FavLibrary::GeometryShape::cube);

	//out.palette.addGeometry(gmr);

	//Material mtl = Material(1, "MATMAT");
	//mtl.addMaterialName("matinfooo");

	//out.palette.addMaterial(mtl);

	//Voxel vx = Voxel(1, "vvvvxxxxlllll");
	//vx.addMaterialInfo(1, 1.0);
	//vx.setGeometryInfo(GeometryInfo(gmr.getId()));
	//out.addVoxel(vx);


	//fprintf(stdout, "ID\t: %s\n", fav.getMetadataId());
	//fprintf(stdout, "Title\t: %s\n", fav.getMetadataTitle());
	//fprintf(stdout, "Author\t: %s\n", fav.getMetadataAuthor());
	//fprintf(stdout, "License\t: %s\n", fav.getMetadataLicense());
	//fprintf(stdout, "Note\t: %s\n", fav.getMetadataNote());

	system("pause");

	fav.write("C:\\Users\\fx28613\\Desktop\\Sources\\fav-project\\FavLibrary\\FavLibrary.Win\\x64\\Release\\FAVSample3.fav", FavLibrary::CompressionMode::base64);

	system("pause");

    return 0;
}

