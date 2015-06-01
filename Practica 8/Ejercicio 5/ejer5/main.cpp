#include "funciones.h"

int main()
{    //imagen
    CImg<double> original,final;
    CImg<bool> img,mask;
    original.load("../../../../images/Morfologia/GlobulosRojos.jpg");
    img = original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(145);
    img = NOTimg(img);
    //Elimino las celulas que tocan el borde
    mask=limpieza_bordes(img);

    //Pinto la imagen original con los circulos rojos (en realidad hago un balance de color con un aumento grande)
    final = mul_mb_c(original,mask) + mul_mb_c(original,NOTimg(img));
    (original,img,mask,final).display("Original - Imagen umbralizada - Eliminacion de Bordes - Final");

    return 0;
}

