#include "funciones.h"

int main()
{
    //kernels
    CImg<bool> img,se1(3,3);
    se1.fill(1);   //  Structuring element 1

    //imagen
    CImg<double> original;
    original.load("../../../../images/Morfologia/GlobulosRojos.jpg");
    img = original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(127);//.get_dilate(se0).get_erode(se1).get_erode(se1).get_erode(se1);//.get_dilate(se1);


    //Elimino las celulas que tocan el borde
    img=limpieza_bordes(img,se1);
    (original,img).display();

    return 0;
}

