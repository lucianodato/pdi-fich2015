#include <iostream>
#include "CImg.h"


using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/cameraman.tif","Image file\n");
    //Imagen color, 8 bits de profundidad por componente.
    //Asigna 0 a todos los pıxeles
    //Visualiza
    CImg<unsigned char> img1(filename);
    //Carga de disco
    CImgDisplay vent1(img1,"original");

    //Encontrar los pixeles de a cara del fotografo (version de libreria)
    CImg<unsigned char> img2 = img1.get_crop(94,38,130,80);
    CImgDisplay vent2(img2,"recortada");

//    //Encontrar los pixeles de a cara del fotografo (version vectorial)
//    CImg<unsigned char> img3(img1);
//    img3.fill(0);

//    for (int i = 94; i<130;i++)
//    {
//        for (int j=38;j<80;j++)
//        {
//            img3(i,j) = img1(i,j);
//        }
//    }
//    CImgDisplay vent3(img3,"recortada_2");

   //guardo en disco

    img2.save_bmp("modificada");

    //Calculo el tamaño de la imagen. BMP ES UNA IMAGEN SIN COMPRESION!, GUARDA LOS 3 CANALES.
    int wx=img2.width();
    int wy=img2.height();
    int wtotal = (wx*wy)+ 54;
    int wtotal_BMP = (wx*wy)*3 + 54;

    cout <<"Valor calculado: "<<wtotal<<endl;
    cout<<"Valor en Memoria: "<< img2.size()<<endl;
    cout<<"Valor Calculado BMP (3Canales): "<< wtotal_BMP<<endl;


    while(!vent1.is_closed() || !vent2.is_closed() /*|| !vent3.is_closed()*/){}
    return 0;
}

