#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;
int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../../../../images/huang2.jpg","Image file\n");
    //Imagen color, 8 bits de profundidad por componente.
    //Asigna 0 a todos los pıxeles
    //Visualiza
    CImg<unsigned char> img0(filename);
    //Carga de disco
    CImgDisplay vent0(img0,"original");

    CImg<unsigned char> img1 = img0.quantize(8);
    CImgDisplay vent1(img1,"Cuantizada Lvl 8",0);

    CImg<unsigned char> img2 = img0.quantize(4);
    CImgDisplay vent2(img2,"Cuantizada Lvl 4",0);

    CImg<unsigned char> img3 = img0.quantize(2);
    CImgDisplay vent3(img3,"Cuantizada Lvl 2",0);

    CImg<unsigned char> img4 = img0.quantize(1);
    CImgDisplay vent4(img4,"Cuantizada Lvl 4",0);

    while(!vent4.is_closed() || !vent3.is_closed() || !vent2.is_closed() || !vent1.is_closed() || !vent0.is_closed() ){}

    return 0;
}

