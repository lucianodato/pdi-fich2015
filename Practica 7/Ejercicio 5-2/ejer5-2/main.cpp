#include "funciones.h"

#define UMBRAL 90
#define CANT_MAX 3

int main()
{
    CImg<double> original,limpia;
    original.load("../../../../images/corrientes_ruidogris.jpg");

    //Aplico denoise con alfa recortado
    limpia = denoise(original,3,5,0,2);
    limpia = filtroAP(limpia,mask(3),0.5);
    limpia.normalize(0,255);

    //Deteccion de lineas
    CImg<bool> mascara = detectar_lineas(limpia,UMBRAL,CANT_MAX);
    mascara.dilate(mask(9));

    //Pinto la pista de rojo
    CImg<double> pintada(original.width(),original.height(),1,3);
    cimg_forXY(original,i,j){
        if(mascara(i,j)==1){
            pintada(i,j,0,0)=255;
            pintada(i,j,0,1)=0;
            pintada(i,j,0,2)=0;
        }else{
            pintada(i,j,0,0)=limpia(i,j);
            pintada(i,j,0,1)=limpia(i,j);
            pintada(i,j,0,2)=limpia(i,j);
        }
    }

    //Muestro
    (original,limpia,mascara,pintada).display();

    return 0;
}

