#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;
int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/rmn.jpg","Image file\n");
    //Imagen color, 8 bits de profundidad por componente.
    //Asigna 0 a todos los pıxeles
    //Visualiza
    CImg<unsigned char> img1(filename);
    //Carga de disco
    CImgDisplay vent1(img1,"original");

    int tam_x = floor(img1.width()/2);
    int tam_y= floor(img1.height()/2);
    CImg<unsigned char> img2 = img1.get_resize(tam_x,tam_y,1);

    CImgDisplay vent2(img2,"original/2",0);
    vent2.resize(img1.width(),img1.height());


    tam_x = floor(img1.width()/4);
    tam_y= floor(img1.height()/4);
    CImg<unsigned char> img3 = img1.get_resize(tam_x,tam_y,1);

    CImgDisplay vent3(img3,"original/4",0);
    vent3.resize(img1.width(),img1.height());

    tam_x = floor(img1.width()/8);
    tam_y= floor(img1.height()/8);
    CImg<unsigned char> img4 = img1.get_resize(tam_x,tam_y,1);

    CImgDisplay vent4(img4,"original/8",0);
    vent4.resize(img1.width(),img1.height());

    while(!vent4.is_closed() || !vent3.is_closed() || !vent2.is_closed() || !vent1.is_closed()){}



    return 0;
}

