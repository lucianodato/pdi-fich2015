#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,img_hsi,mag;
    img.load("../../../../images/Deforestacion.png");
    img.display();
    img_hsi = img.get_RGBtoHSI();

    CImgList<float> Lista(fourier(img_hsi.get_channel(2)));
    //La imagen 1 y 2 son la magnitud original. La 3 y la 4 son las imagenes para visualizar
    mag = Lista.at(2);
    mag.display();

    CImg<float> imagen = fourier_inv(Lista.at(0),Lista.at(1));
    imagen = copia_canal(img_hsi,2,imagen,0);
    imagen.get_HSItoRGB().display();

    return 0;
}

