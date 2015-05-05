#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img;
    img.load("../../../../images/carlock1.png");

    float radio = img.width()/32;

    CImg<float> pasaalto = pasaalto_ideal(radio,float(img.width()),float(img.height()));
    CImg<float> img_filt = filtrar(img,pasaalto);

    CImgList<float> lista(img,img_filt);
    lista.display("Original - Filtrada");

    return 0;
}

