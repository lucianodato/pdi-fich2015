#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;


unsigned patrones[10][3][3]={
        {{0,0,0}, {0,0,0}, {0,0,0}},
        {{0,1,0}, {0,0,0}, {0,0,0}},
        {{0,1,0}, {0,0,0}, {0,0,1}},
        {{1,1,0}, {0,0,0}, {0,0,1}},
        {{1,1,0}, {0,0,0}, {1,0,1}},
        {{1,1,1}, {0,0,0}, {1,0,1}},
        {{1,1,1}, {0,0,1}, {1,0,1}},
        {{1,1,1}, {0,0,1}, {1,1,1}},
        {{1,1,1}, {1,0,1}, {1,1,1}},
        {{1,1,1}, {1,1,1}, {1,1,1}}
};

CImg<unsigned char> mediosTonos (CImg<unsigned char> img){

    CImg<unsigned char> aux=img,medioTono(img.width()*3,img.height()*3,1,1,0);
    aux.quantize(10,false); //false no mantengo el rango, 10 xq es la cantidad de tonos que tengo disponibles para usar en la impresora
    cimg_forX(aux,i)//recorro imagen original
            cimg_forX(aux,j)
            //por cada pixel de imagen original(ahora aux) relleno 9 pixeles en medioTono
            for (int l=0;l<3;l++)
                for(int m=0;m<3;m++)
                    medioTono((i*3)+l,(j*3)+m)=patrones[aux(i,j)][l][m]*255;

    return medioTono;
}


CImg<unsigned char> degrade (int x, int y, bool horizontal=true){
    CImg<unsigned char> img(256,256,1,1,0);
    if (horizontal)
    cimg_forX(img,i)//recorro imagen original
            cimg_forX(img,j)
                    img(i,j)=j;
    else
    cimg_forX(img,j)//recorro imagen original
            cimg_forX(img,i)
                    img(i,j)=i;


    return img;
}



int main()
{


        CImg<unsigned char> imgOrig,mediosTonos1,mediosTonos2,imgDegrade=degrade(200,200,false);
        imgOrig.load("../../../../images/huang2.jpg");
        CImgDisplay displayImagen,displayDegrade;
        char window_title[50];
        mediosTonos1=mediosTonos(imgDegrade);
        mediosTonos2=mediosTonos(imgOrig);
        displayDegrade.assign(mediosTonos1);
        displayImagen.assign(mediosTonos2);




        while(!displayImagen.is_closed()&& !displayDegrade.is_closed()){
            displayImagen.wait_all(); // esperamos algun evento en el display

            displayDegrade.render(mediosTonos1);
            sprintf(window_title,"Degrade");
            displayDegrade.set_title(window_title);
            displayDegrade.paint();




            displayImagen.render(mediosTonos2);
            sprintf(window_title,"Imagen");
            displayImagen.set_title(window_title);
            displayImagen.paint();
        }



    return 0;
}
