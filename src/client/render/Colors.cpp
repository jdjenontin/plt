#include "Colors.h"

using namespace sf;

namespace render{

Colors::Colors(){
    Color blue(0, 0, 255, 200);
    Color red(255, 0, 0, 200);
    Color green(0, 255, 0, 200);
    Color pink(238, 130, 238, 200);
    Color purple(88, 82, 169, 200);

    colorList = {blue, red, green, pink, purple};
}

Colors::~Colors(){

}

}