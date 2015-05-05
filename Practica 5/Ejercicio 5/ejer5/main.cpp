#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img;
    img.load("../../../../images/carlock1.png");

    CImgList<float> lista(img);

    float radio = img.width()/32;

    //Filtro Ideal
    CImg<float> pasaalto = ideal_mask(img,radio,true);
    CImg<float> img_filt = filtrar(img,pasaalto);

    lista.push_back(img_filt);

    //Filtro Butter
    pasaalto = butterworth_mask(img,radio,1,true);
    img_filt = filtrar(img,pasaalto);

    lista.push_back(img_filt);

    //Filtro Gauss
    pasaalto = gaussian_mask(img,radio,true);
    img_filt = filtrar(img,pasaalto);

    lista.push_back(img_filt);

    //Muestro
    lista.display("Original - Filtro Ideal - Filtro Butter - Filtro Gauss");

    return 0;
}

