#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    //Punto 1 - columna en escala de grises
    CImg<unsigned char> img1(256,256,1,1); // Define a 256x256 color image
    cimg_forXYC(img1,x,y,v) { img1(x,y,v) =x; }
    CImgDisplay ventana1(img1,"Escala de Grises");
     //Punto 2 - columna en escala de grises
    CImg<unsigned char> img2(100,100,1,1); // Define a 256x256 color image
    //solo hay que normalizar el gradiente
    cimg_forXYC(img2,x,y,v) { img2(x,y,v) =255/100 * x; }
    CImgDisplay ventana2(img2,"Escala de Grises");
    //Punto 2 - columna en escala de grises
    CImg<unsigned char> img3(100,100,1,1); // Define a 256x256 color image
    //solo hay que normalizar el gradiente
    cimg_forXYC(img3,x,y,v){
        if(x%2 == 0){
            img3(x,y,v) = 0;
        }else
        {
            img3(x,y,v) = 255;
        }
    }
    CImgDisplay ventana3(img3,"Escala de Grises");

    int tamanio_img=256,radio=100;
    cout<<"Ingrese el tamaño de la imagen: ";
    cin>>tamanio_img;

    cout<<"Ingrese el tamaño del circulo: ";
    cin>>radio;
    while(radio >=tamanio_img/2)
    {
        cin>>radio;
    }
    CImg<unsigned char> img4(tamanio_img,tamanio_img,1,1); // Define a 256x256 color image
    img4.fill(0);
    const unsigned char white[] = { 255,255,255 };
    int aux = floor(tamanio_img/2);
    img4.draw_circle(aux,aux,radio,white,1);
    CImgDisplay ventana4(img4,"Escala de Grises");


    while(!ventana4.is_closed() || !ventana3.is_closed() || !ventana2.is_closed() || !ventana1.is_closed()){}
    return 0;


}

