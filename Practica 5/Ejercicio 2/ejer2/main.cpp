#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,img2,fase0,magnitud1;
    img.load("../../../../images/cameraman.tif");
    img2.load("../../../../images/clown.jpg");


    magnitud1.assign(img);
    fase0.assign(img);

    magnitud1.fill(1);
    fase0.fill(0);

    //Consigna 1

    CImgList<float> transformada = fourier(img);

    CImg<float> solomagnitud = fourier_inv(transformada.at(0),fase0);
    CImg<float> solofase = fourier_inv(magnitud1,transformada.at(1));

    CImgList<float> lista2(img,solomagnitud,solofase);
    lista2.display("Original - Solo Magnitud - Solo fase");

    //Consigna 2

    CImgList<float> transformada2 = fourier(img2);

    CImg<float> mezcla1 = fourier_inv(transformada.at(0),transformada2.at(1));
    CImg<float> mezcla2 = fourier_inv(transformada2.at(0),transformada.at(1));

    CImgList<float> lista(img,img2,mezcla1,mezcla2);
    lista.display("Original 1 - Original 2 - Mezcla 1 - Mezcla 2");


    return 0;
}

