#include "funciones.h"

using namespace std;

int tamanio = 5;

int main()
{
    const char* path = "../../../../images/cameraman.tif";
    CImg <unsigned char> img,img2;
    img.load(path);

//    //kernel 3x3
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

    CImg<float> maskara = mask(tamanio);

    //Paso bajo

    maskara.fill(0);
    maskara(0,2) = maskara(1,2) = maskara(2,0) = maskara(2,1) = maskara(2,3)= maskara(2,4) = maskara(3,2) = maskara(4,2) =   1.0/16.0;
    maskara(2,2) = 1.0/2.0;

    //filtro espacial
    img2 = img.get_convolve(maskara);

    CImgList<unsigned char> lista (img,img2);
    lista.display();


    return 0;
}

