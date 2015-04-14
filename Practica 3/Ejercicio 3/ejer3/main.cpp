#include "funciones.h"

using namespace std;

int tamanio = 20;
int sigma= 1;//3*sigma

int main()
{
    const char* path = "../../../../images/cameraman.tif";
    const char* path2 = "../../../../images/hubble.tif";
    CImg <float> img;
    img.load(path2);

//    //kernel 3x3
    //suma 1
    CImg<float> kernel1(3,3,1,1);
    kernel1(0,0)=0;
    kernel1(0,1)=-1;
    kernel1(0,2)=0;
    kernel1(1,0)=-1;
    kernel1(1,1)=5;
    kernel1(1,2)=-1;
    kernel1(2,0)=0;
    kernel1(2,1)=-1;
    kernel1(2,2)=0;

    //    //kernel 3x3
        //suma0
        CImg<float> kernel2(3,3,1,1);
        kernel2(0,0)=-1;
        kernel2(0,1)=-1;
        kernel2(0,2)=-1;
        kernel2(1,0)=-1;
        kernel2(1,1)=8;
        kernel2(1,2)=-1;
        kernel2(2,0)=-1;
        kernel2(2,1)=-1;
        kernel2(2,2)=-1;


//    //kernel 5x5
//    CImg<float> mask(3,3,1,1);
//    mask(0,0)=0;
//    mask(0,1)=0;
//    mask(0,2)=0;
//    mask(0,3)=0;
//    mask(0,4)=0;
//    mask(0,5)=0;
//    mask(1,1)=0.25;
//    mask(1,1)=0.25;
//    mask(1,2)=0.25;
//    mask(1,3)=0.25;
//    mask(1,4)=0.25;
//    mask(1,5)=0.25;
//    mask(2,1)=0.5;
//    mask(2,2)=0.25;
//    mask(2,3)=0;
//    mask(2,4)=0;
//    mask(2,5)=0;
//    mask(3,0)=0;

//    //kernel 10x10
//    CImg<float> mask(3,3,1,1);
//    mask(0,0)=0;
//    mask(0,1)=0;
//    mask(0,2)=0;
//    mask(1,0)=0.25;
//    mask(1,1)=0.5;
//    mask(1,2)=0.25;
//    mask(2,0)=0;
//    mask(2,1)=0;
//    mask(2,2)=0;


        CImgList<float> lista (img,img.get_convolve(kernel1),img.get_convolve(kernel2));
        lista.display("Original - Promediado - Gauss");



    return 0;
}
