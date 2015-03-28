#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main()
{

    CImg<unsigned char> img1,img2;
    CImgList<unsigned char> disp;

img1.clear();
img2.clear();
img1.load("../../../../images/coins.tif");//carga imagen en memo
CImg<unsigned char> noiseImg(img1),promedio;
//Hacer Imagen Ruidosa
noiseImg.noise(-5,0);
promedio=reducRuido(img1,50,-5);
disp.insert(img1);disp.insert(noiseImg);disp.insert(promedio);
//disp(img1,noise,suma,promedio);
CImgDisplay displayImagen10(disp,"Original - Noise - Suma");
while (!displayImagen10.is_closed()) {
    displayImagen10.wait();
}



    return 0;
}

