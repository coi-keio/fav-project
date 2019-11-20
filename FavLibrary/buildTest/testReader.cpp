#include <iostream>
#include "Fav.h"

using namespace FavLibrary;


int main(int argc, const char * argv[]) {

    Fav fav;
    fav.read("./sample.fav");
    return 0;

}
