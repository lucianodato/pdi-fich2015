#include "funciones.h"

int main()
{
    CImg<double> mdil(3,3,1,1,0),img;
    img.load("../../../../images/cameraman.tif");
    mdil.fill(0);
    mdil(0,0) = 1;mdil(2,0)=1;mdil(1,1)=1;mdil(0,2)=1;mdil(2,2)=1; //  Section E
    CImg<double> ima_dilated=img.get_dilate(mdil);
    CImgList<double> (img,ima_dilated).display("org. image and dilated");

    return 0;
}

