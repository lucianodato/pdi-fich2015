#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    CImg<unsigned char> img1,img2;
    CImgList<unsigned char> listaImagenes;
    const unsigned char white[] = { 255,255,255 };
    img1.load("../../../../images/cameraman.tif");
    img2.load("../../../../images/coins.tif");
    listaImagenes.push_back(img1);
    listaImagenes.push_back(img2);
    listaImagenes.push_back(sumaImg(img1,img2,0));
    CImgDisplay displayImagen(listaImagenes,"G2 - Ejer3-1-a - Suma Imagenes");
    listaImagenes.clear();
    listaImagenes.push_back(img1);
    listaImagenes.push_back(img2);
    listaImagenes.push_back(DifImg(img1,img2));
    CImgDisplay displayImagen2(listaImagenes,"G2 - Ejer3-1-b - Diferencia Imagenes");
    listaImagenes.clear();
    listaImagenes.push_back(img1);
    listaImagenes.push_back(img2);
    listaImagenes.push_back(multiplicacion(img1,img2));
    CImgDisplay displayImagen3(listaImagenes,"G2 - Ejer3-1-c - multiplicacion Imagenes");
    listaImagenes.clear();
    listaImagenes.push_back(division(img1,img2));
    CImgDisplay displayImagen4(listaImagenes,"G2 - Ejer3-1-c - division Imagenes");




    while (!displayImagen.is_closed()) {
        displayImagen.wait_all();
    }
    return 0;
}

