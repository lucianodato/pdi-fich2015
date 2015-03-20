#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

int main()
{


    CImg<unsigned char> img;
    CImgList<unsigned char> listaImagenes;
    CImgDisplay displayImagen;

    img.load("../../../../images/huang2.jpg");
    listaImagenes.insert(img);
    for(unsigned i=8; i>1; i--){
        listaImagenes.insert(img.get_quantize(i));
    }
    displayImagen.assign(listaImagenes, "Quantizacion 8bit(256 niveles) to 2 bit(2 niveles )");

    while(!displayImagen.is_closed()){
        displayImagen.wait_all(); // esperamos algun evento en cualquier display
    }

    return 0;
}

