#include "funciones.h"

int main()
{    //imagen
    CImg<double> original,final;
    CImg<bool> img,mask;
    original.load("../../../../images/Morfologia/GlobulosRojos.jpg");
    img = original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(145);
    //Elimino las celulas que tocan el borde
    mask=bordes(img,false);
    mask.display("bordes");

    //Pinto la imagen original con los circulos rojos (en realidad hago un balance de color con un aumento grande)
    final = balancecolorRGB(original,0,300).get_mul(mask) + final.get_mul(negativo(mask));
    final.display();

    return 0;
}

