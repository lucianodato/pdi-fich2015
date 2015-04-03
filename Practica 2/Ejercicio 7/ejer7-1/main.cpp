#include "funciones.h"

using namespace cimg_library;
using namespace std;

int c = 1;

int main(int argc, char *argv[])
{
    const char* path = "../../../../images/earth.bmp";
    CImg<unsigned char> img;
    img.load(path);
    CImgDisplay disp(transformacion(img.get_channel(2),generar_lut_logb(c)));
    while(!disp.is_closed()){
        disp.wait();
    }
    return 0 ;

}
