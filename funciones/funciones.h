#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>
#include "CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;


//------------------------------FUNCIONES AUXILIARES--------------------------------------------

//s=a*r+c
//con r: valor de entrada
//a = factor de ganancia
//c = offset

//Caso que tengo todos los grises
//item 1
CImg<unsigned char> generar_lut_lin(float a,float c){
        CImg<unsigned char> lut(1,256,1,1);
        int s;
        for (int i=0;i<256;i++){
                s=int(a*i+c);
                if (s>255) s=255;
                if (s<0) s=0;
                lut(i)=s;
        }
        return lut;
}


//lut recta 3 tramos,(solo 3 tramos, hacerla de muchos tramos muy bien gracias)
CImg<unsigned char> generar_lut_mod(int r1,int r2,int s1,int s2){
        CImg<unsigned char> lut(1,256,1,1);
        int s;
        for (int i=0;i<256;i++){
                if (i<=r1) s=(((s1-0)/(r1-0))*(i-0))+0;
                if (i>r1 && i<=r2) s=(((s2-s1)/(r2-r1))*(i-r1))+s1;

                if (i>r2 ) s=(((255-s2)/(255-r2))*(i-r2))+s2;
                if (s>255) s=255;
                if (s<0) s=0;
                lut(i)=s;
        }
        return lut;
}

//logaritmica: imagenes resultantes son mas claras
//Caso que tengo todos los grises
CImg<int> generar_lut_logb(float c){
        CImg<unsigned char> lut(1,256,1,1);
        int s;
        for (int i=0;i<256;i++){
                s=(int)(c*(255*((log(1+i)/log(1+255)))));// normalizo -.- mmmm
                if (s>255) s=255;
                if (s<0) s=0;
                lut(i)=s;
        }
        return lut;
}



//lut exponencial bis: REDUCE el rango de grises, las imagenes resultantes son mas oscuras
//Caso que tengo todos los grises
CImg<unsigned char> generar_lut_expb(float c,float gamma){
        CImg<unsigned char> lut(1,256,1,1);
        int s;
        for (int i=0;i<256;i++){
                s=int(c*(pow(i,gamma)/255));
                if (s>255) s=255;
                if (s<0) s=0;
                lut(i)=s;
        }
        return lut;
}

//aplica la transformacion que se la pase en "lut" a la imagen "img"
CImg<unsigned char> transformacion(CImg<unsigned char> img,CImg<unsigned char> lut){
        cimg_forXY(img,i,j)
                        img(i,j)=lut(img(i,j)); // "map"
        return img;
}


//lut que no andan
//FUNCION LUT - Reliza una transformacion lineal segun el alpha y el offset que recibe



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


//SUMA
CImg<unsigned char> sumaImg(CImg<unsigned char> img1, CImg<unsigned char> img2){
        CImg<unsigned char> resultado(img1.width(),img1.height(),1,1);
        cimg_forXY(img1,i,j) resultado(i,j)=(img1(i,j)+ img2(i,j))/2;
        return resultado;
}
//DIFERENCIA
CImg<unsigned char> DifImg(CImg<unsigned char> img1, CImg<unsigned char> img2){
        CImg<unsigned char> resultado(img1.width(),img1.height(),1,1);
        cimg_forXY(img1,i,j)  resultado(i,j)=(img1(i,j)- img2(i,j)+255)/2;
        return resultado;
}
//MULTIPLICACION
CImg<unsigned char> multiplicacion(CImg<unsigned char> &img, CImg<unsigned char> &masc){
        CImg<unsigned char> resultado(img.width(),img.height(),1,1);
        cimg_forXY(img,i,j) resultado(i,j)=img(i,j) * masc(i,j)/255; //divid0 por 255 para normalizar la mascara
        return resultado;
}
//DIVISION
CImg<unsigned char> division(CImg<unsigned char> &img, CImg<unsigned char> &masc){
    CImg<unsigned char> lut(generar_lut_lin(-1,255));
    CImg<unsigned char> mascara;
    mascara=transformacion(masc,lut);
    return multiplicacion(img,mascara);
}
//REDUCIR RUIDO //pasar una imagen con ruido en "img",  //genera la suma de "n" imagenes con ruido
//noise(desvio, tipo de ruido a gnerar)
//(0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician).
CImg<unsigned char> reducRuido(CImg<unsigned char>img,unsigned int n, int ruido){
        CImg<unsigned char> suma(img.width(),img.height(),1,1,0);
        for(unsigned char i=0;i<n;i++){
                CImg<unsigned char>img2(img);
                suma=sumaImg(suma,img2.get_noise(ruido,0)); //sumo
        }
                return suma;
}




#endif // FUNCIONES

