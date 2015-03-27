#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>
#include "CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;


//------------------------------FUNCIONES AUXILIARES--------------------------------------------


//FUNCION LUT - Reliza una transformacion lineal segun el alpha y el offset que recibe
//Caso que tengo todos los grises
const CImg<unsigned char> lut(float a=1,float c=0){

    CImg <unsigned char> lut(1,256,1,1);
    int s;

    for(int i=0;i<256;i++)
    {
        s=a*i+c;

        if(s<0)
        {
            lut(1,i) = 0;
        }
        else
        {
            if(s>255)
            {
                lut(1,i) = 255;
            }
            else
            {
                lut(1,i) = s;
            }
        }
    }

    return lut;
}

//FUNCION LUT - Reliza una transformacion lineal segun el alpha y el offset que recibe
//Caso que tengo un tramo de grises especifico
const CImg<unsigned char> lut(float a,float c,int x1,int y1,int x2,int y2){

    //Calculo pendientes y offset


    CImg <unsigned char> lut(1,256,1,1);
    int s;

    for(int i=0;i<256;i++)
    {
        s=a*i+c;

        if(s<0)
        {
            lut(1,i) = 0;
        }
        else
        {
            if(s>255)
            {
                lut(1,i) = 255;
            }
            else
            {
                lut(1,i) = s;
            }
        }
    }

    return lut;
}

//FUNCION NEGATIVO - Devuelve el negativo de una imagen 
CImg<unsigned char> negativo(CImg<unsigned char> imagen){

  cimg_forXY(imagen,i,j){
          imagen(i,j) = abs(((int)*imagen.data(i,j,0,0) -255));}
  return imagen;
}


//FUNCION BINARIO - Caso que recibe un umbral (En la libreria esta la funcion get_threshold tambien)
CImg<unsigned char> binario(CImg<unsigned char> imagen, int umbral){

    CImg<unsigned char> modificada(imagen.width(),imagen.height(),1,1);

    for (int i=0;i<imagen.width();i++){
        for(int j=0;j<imagen.height();j++){

            if( (int)*imagen.data(i,j,0,0) > umbral )
            {
                modificada(i,j)= 255;
            }
            else
            {
                modificada (i,j)=0;
            }

        }
    }
    return modificada;

}

// FUNCION DETECTAR_MEDIOTONO - Devuelve una imagen 3x3 del mediotono correspondiente a la intensidad recibida 
CImg<unsigned char> detectar_mediotono(int intensidad){
    
    CImg <unsigned char> nivel(3,3,1,1);
    
    //9 niveles de 28 cada uno. El ultimo tiene 31
    if(intensidad >=0 && intensidad<25){
        //nivel 0

        return nivel.fill(0);
    }
    if(intensidad >=25 && intensidad<50){
        //nivel 1

        nivel.fill(0);
        nivel(0,1)= 255;
        return nivel;
    }
    if(intensidad >=50 && intensidad<75){
        //nivel 2

        nivel.fill(0);
        nivel(0,1)= 255;
        nivel(2,2)= 255;
        return nivel;
    }
    if(intensidad >=75 && intensidad<100){
        //nivel 3

        nivel.fill(0);
        nivel(0,0)= 255;
        nivel(0,1)= 255;
        nivel(2,2)= 255;
        return nivel;
    }
    if(intensidad >=100 && intensidad<125){
        //nivel 4

        nivel.fill(0);
        nivel(0,0)= 255;
        nivel(0,1)= 255;
        nivel(2,0)= 255;
        nivel(2,2)= 255;
        return nivel;
    }
    if(intensidad >=125 && intensidad<150){
        //nivel 5

        nivel.fill(0);
        nivel(0,0)= 255;
        nivel(0,1)= 255;
        nivel(0,2)= 255;
        nivel(2,0)= 255;
        nivel(2,2)= 255;
        return nivel;
    }
    if(intensidad >=150 && intensidad<175){
        //nivel 6

        nivel.fill(0);
        nivel(0,0)= 255;
        nivel(0,1)= 255;
        nivel(0,2)= 255;
        nivel(1,2)= 255;
        nivel(2,0)= 255;
        nivel(2,2)= 255;
        return nivel;
    }
    if(intensidad >=175 && intensidad<200){
        //nivel 7

        nivel.fill(255);
        nivel(1,0)= 0;
        nivel(1,1)= 0;
        return nivel;
    }
    if(intensidad >=200 && intensidad<225){
        //nivel 8

        nivel.fill(255);
        nivel(1,1)= 0;
        return nivel;
    }
    if(intensidad >=225){
        //nivel 9

        return nivel.fill(255);
    }

}

//FUNCION MEDIOTONO - Recibe una imagen y la devuelve en binario con los medios tonos correspondientes
CImg<unsigned char> mediotono(CImg<unsigned char> original){

    CImg<unsigned char> modificada(original.width()*3,original.height()*3,1,1), aux(3,3,1,1);
    int var_x,var_y;
    
    original.normalize(0,255);

    for (int x =0;x<original.width();x++){
        for (int y =0;y<original.height();y++){

            aux = detectar_mediotono((int)*original.data(x,y,0,0));
            //cout <<"Fija x: "<<x<<" Columna y: "<<y<<" Intensidad: "<<(int)*original.data(x,y,0,0)<<endl;

            var_x=3*x;
            var_y=3*y;

            modificada(var_x,var_y) = aux(0,0);
            modificada(var_x,var_y+1) = aux(0,1);
            modificada(var_x,var_y+2) = aux(0,2);
            modificada(var_x+1,var_y) = aux(1,0);
            modificada(var_x+1,var_y+1) = aux(1,1);
            modificada(var_x+1,var_y+2) = aux(1,2);
            modificada(var_x+2,var_y) = aux(2,0);
            modificada(var_x+2,var_y+1) = aux(2,1);
            modificada(var_x+2,var_y+2) = aux(2,2);
        }

    }

    modificada.resize(original.width(),original.height(),-100,-100,3);
    return modificada;
}


#endif // FUNCIONES

