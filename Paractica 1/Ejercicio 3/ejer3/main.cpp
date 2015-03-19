#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    CImg<unsigned char> image("../../../../images/cameraman.tif"), visu(500,400,1,3,0);
    CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
    //declaro color de linea para intensidad
    const unsigned char white[] = { 255,255,255 };
    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y()>=0) {
            const int y = main_disp.mouse_y();
            visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
            // Muestro por consola el valor de intensidad
            cout <<  image.get_channel() <<endl;

        }
    }
    return 0;
}

