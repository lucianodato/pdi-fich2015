#include "funciones.h"

int main()
{
    //kernels
    CImg<bool> img,se1(3,3),se0(5,5,1,1,0);
    se0(0,0)=se0(1,1)=se0(2,2)=se0(3,3)=se0(4,4)=se0(5,5)=1;
    se0(1,2)=se0(2,3)=se0(3,2)=se0(2,1)=se0(4,3)=se0(3,4)=1;
    se1.fill(0,0,1,0,1,0,1,0,0);   //  Structuring element 1

    //imagen
    CImg<double> original;
    original.load("../../../../images/Morfologia/GlobulosRojos.jpg");
    img = original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(127);//.get_dilate(se0).get_erode(se1).get_erode(se1).get_erode(se1);//.get_dilate(se1);
    (original,img).display();

    return 0;
}

