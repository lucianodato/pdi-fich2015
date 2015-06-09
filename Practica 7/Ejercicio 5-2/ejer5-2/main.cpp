#include "funciones.h"

int main()
{
    CImg<double> original,limpia;
    original.load("../../../../images/corrientes_ruidogris.jpg");

    //Aplico denoise con media armonica
    limpia = denoise(original,3,5,0,2);
    limpia = filtroAP(limpia,mask(3),0.5);
    limpia.normalize(0,255);

    //Deteccion de lineas
    CImg<bool> mascara = detectar_lineas(limpia,90,3);
    mascara.dilate(mask(3));

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

