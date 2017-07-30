#include <iostream>
#include "Fav.h"


int main(int argc, const char * argv[]) {
    
    FavLibrary::Fav fav_test;
    fav_test.read("../../../Sample\ FAVs/ChessKing_Color_reso1_v1.fav");
    fav_test.write("./testLib.fav", FavLibrary::CompressionMode::base64);
    return 0;

}
