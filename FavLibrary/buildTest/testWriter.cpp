#include <iostream>
#include "Fav.h"

using namespace FavLibrary;


int voxelSource[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0},
    },
    {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    }
};


int main(int argc, const char * argv[]) {

    Fav fav;
    fav.setMetadataId("2019-11-18");
    fav.setMetadataAuthor("Takumi Moriya");
    fav.setMetadataTitle("Sample data");
    fav.setMetadataLicense("MIT");
    fav.setMetadataNote("This file is created by testWriter.cpp");

    Geometry geometry1 = Geometry(1, "geometry1");
    geometry1.setScale(1, 1, 1);
    geometry1.setShape(GeometryShape::cube);
    fav.palette.addGeometry(geometry1);

    Material material1 = Material(1, "material1");
    material1.addMaterialName("soft_mat1");
    fav.palette.addMaterial(material1);

    Voxel voxel1 = Voxel(1, "voxel1");
    printf("%s\n", voxel1.getReferencePath());
    voxel1.addMaterialInfo(material1.getId(), 1.0);
    voxel1.setGeometryInfo(GeometryInfo(geometry1.getId()));
    fav.addVoxel(voxel1);

    Grid grid1 = Grid();
    grid1.setUnit(1, 1, 1);
    grid1.setOrigin(0, 0, 0);
    grid1.setDimension(4, 4, 4);

    Structure structure1 = Structure();
    structure1.setBitPerVoxel(BitPerVoxel::Bit8);
    structure1.setGridPointer(&grid1);
    structure1.initVoxelMap();
    structure1.initColorMap(ColorMode::RGB);

    for (int z = 0; z < grid1.getDimensionZ(); z++) {
        for (int y = 0; y < grid1.getDimensionY(); y++) {
            for (int x = 0; x < grid1.getDimensionX(); x++) {
                if (voxelSource[z][y][x] != 0) {
                    structure1.setVoxel(x, y, z, voxel1.getId());
                    ColorRGB rgb = ColorRGB(1, 1, 1);
                    structure1.setColor(x, y, z, rgb);
                } else {
                    structure1.setVoxel(x, y, z, 0);
                }
            }
        }
    }

    Object object1 = Object(1, "object1");
    object1.grid = grid1;
    object1.structure = structure1;
    fav.addObject(object1);

    // fav.write("sample.fav", CompressionMode::base64);
    fav.write("sample.fav", CompressionMode::none);
    return 0;

}
