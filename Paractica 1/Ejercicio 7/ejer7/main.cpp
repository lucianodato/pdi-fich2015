#include <iostream>
#include "CImg.h"
#include "pasar_medios_tonos.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/huang2.jpg","Image file\n");
    //Imagen color, 8 bits de profundidad por componente.
    //Asigna 0 a todos los pıxeles
    //Visualiza
    CImg<unsigned char> img0(filename);

    //Punto 1 - columna en escala de grises
//    CImg<unsigned char> img0(256,256,1,1); // Define a 256x256 color image
//    cimg_forXY(img0,x,y) { img0(x,y) =x; }

    //pasar imagen a mediotono
    CImg<unsigned char> img1 = pasar_medios_tonos(img0);


    //Display
    CImgDisplay vent0(img0,"original");
    CImgDisplay vent1(img1,"medios tonos");

    while(!vent1.is_closed() || !vent0.is_closed() ){}

    return 0;
}
