#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,mag;
    img.load("../../../../images/Deforestacion.png");
    img.display();
    CImgList<float> Lista(fourier(img));
    //La imagen 1 y 2 son la magnitud original. La 3 y la 4 son las imagenes para visualizar
    mag = Lista.at(2);
    mag.display();

    CImg<float> imagen = fourier_inv(Lista.at(0),Lista.at(1));
    imagen.display();

    return 0;
}

