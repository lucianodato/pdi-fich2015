#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,pasabajos,img_filt;
    img.load("../../../../images/carlock1.png");
    pasabajos.assign(img);
    img_filt.assign(img);

    float radio = img.width()/32;

    pasabajos = pasabajos_ideal(radio,float(img.width()),float(img.height()));
    img_filt = filtrar(img,img_filt);

    CImgList<float> lista(img,img_filt);
    lista.display("Original - Filtrada");

    return 0;
}

