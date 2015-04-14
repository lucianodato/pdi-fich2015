#include "funciones.h"

using namespace std;

int tamanio = 20;
int sigma= 1;//3*sigma

int main()
{
    const char* path = "../../../../images/cameraman.tif";
    const char* path2 = "../../../../images/hubble.tif";
    CImg <unsigned char> img,img2,img3,hubble;
    img.load(path);
    hubble.load(path2);

//    //kernel 3x3
//    CImg<float> maskara(3,3,1,1);
//    maskara(0,0)=0;
//    maskara(0,1)=0.125;
//    maskara(0,2)=0;
//    maskara(1,0)=0.125;
//    maskara(1,1)=0.5;
//    maskara(1,2)=0.125;
//    maskara(2,0)=0;
//    maskara(2,1)=0.125;
//    maskara(2,2)=0;


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

    //Consigna 1 y 2
    CImg<float> maskara = mask(tamanio);//Es kernel
    CImg<float> maskara2 = gauss_filter(sigma,0);//Es kernel
    CImg<unsigned char> maskara3;//Es mascara de multiplicacion

    //filtro espacial aplicacion
    //Pasa Bajos
    img2 = img.get_convolve(maskara);
    //Gaussiano
    img3 = img.get_convolve(maskara2);

    //    CImgList<unsigned char> lista (img,img2,img3);
    //    lista.display("Original - Promediado - Gauss");

    //Consigna 3

    //Procesado de Hubble
    //Filtrado
    maskara3 = hubble.get_convolve(maskara);
    //Umbralado para crear la mascara
    maskara3.threshold(100);
    maskara3.normalize(0,1);//Normalizamos para multiplicar
    CImg <unsigned char> img4 = multiplicacion(hubble,maskara3);

    CImgList<unsigned char> lista2 (hubble,maskara3,img4);
    lista2.display("Original - Filtrada");


    return 0;
}

