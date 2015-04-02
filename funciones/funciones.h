#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>
#include "CImg.h"
#include <vector>
#include <algorithm>
#include <math.h>

using namespace cimg_library;
using namespace std;

//Variables auxiliares

//Punto
typedef struct punto{
    float x;
    float y;
    float norma() {
        return sqrt(x*x + y*y);
    }
    float normaManhattan() {
        return x+y;
    }
}punto;

//Sort de Vector con puntos
bool myfunction (punto i,punto j) { return (i.normaManhattan()<j.normaManhattan()); }

//Para usar sort con vectores de puntos
bool compara_puntos(const punto &a, const punto &b)
{
    return a.x < b.x;
}

vector<punto> ordenarCoordenadas(vector<punto> puntos){
    // using object as comp
    std::sort (puntos.begin(), puntos.end(),myfunction);
    return puntos;
}

//------------------------------FUNCIONES AUXILIARES--------------------------------------------

//s=a*r+c
//con r: valor de entrada
//a = factor de ganancia
//c = offset

//Caso generico. Recibe un gris inicial y un final. Por tramos
//item 1
CImg<unsigned char> generar_lut(float a,float c,int ini,int fin){
    CImg<unsigned char> lut(1,abs(fin-ini)+1,1,1);
    int s;
    for (int i=ini;i<abs(fin-ini)+1;i++){
        s=int(a*i+c);
        if (s>255) s=255;
        if (s<0) s=0;
        lut(i)=s;
    }
    return lut;
}

///FUNCION NEGATIVO - Devuelve el negativo de una imagen
CImg<unsigned char> negativo(CImg<unsigned char> imagen){
    cimg_forXY(imagen,i,j)
        imagen(i,j) = abs(((int)*imagen.data(i,j,0,0))-255);
    return imagen.normalize(0,255);
}

//Funcion curva Solo cuando se necesitan tramos
CImg <unsigned char> generar_curva(CImg<unsigned char> lut,vector<punto> puntos){
    int x0,x1,y0,y1;
    float a,c;
    a=1;
    c=0;
    CImg<unsigned char> curva(lut.width(),lut.height(),1,1),aux(lut.width(),lut.height(),1,1);

    //Ordeno el vector para que los puntos esten ordenados
    //sort(puntos.begin(),puntos.end(),compara_puntos);

    if (puntos.size() == 2) return generar_lut(1,0,0,255);

    x0 = puntos[0].x;
    y0 = puntos[0].y;

    for (int i=1;i<puntos.size();i++){
        //Cargo los puntos
        x1 = puntos[i].x;
        y1 = puntos[i].y;
        a=(y1-y0)/(x1-x0);

        cout<<"pendiente: ";
        printf("%.12f", a);
        cout<<endl;

        aux = generar_lut(a,c,x0,x1);

        for(int i=x0;i<x1;i++){
            curva(1,i) = aux(1,i);
        }

        x0 = x1;
        y0 = y1;

    }

    return curva;
}


//logaritmica: imagenes resultantes son mas claras
//Caso que tengo todos los grises
CImg<int> generar_lut_logb(float c){
    CImg<unsigned char> lut(1,256,1,1);
    int s;
    for (int i=0;i<256;i++){
        //Aca mapeamos el rango total resultante para que despues se traduzca en un nivel de gris
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


///FUNCION BINARIO - Caso que recibe un umbral (En la libreria esta la funcion get_threshold tambien)
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

/// FUNCION DETECTAR_MEDIOTONO - Devuelve una imagen 3x3 del mediotono correspondiente a la intensidad recibida
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

///FUNCION MEDIOTONO - Recibe una imagen y la devuelve en binario con los medios tonos correspondientes
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


///SUMA
//corrimiento=0 si quiero sumar sin corrimiento
CImg<unsigned char> sumaImg(CImg<unsigned char> img1, CImg<unsigned char> img2, int corrimiento ){
    CImg<unsigned char> resultado(img1.width(),img1.height(),1,1);
    cimg_forXY(img1,i,j){
        if((i+corrimiento) >= 0 && (j+corrimiento)>=0){
            resultado(i,j)=(img1(i,j)+ img2(i+corrimiento,j+corrimiento))/2;
        }else
        {
            resultado(i,j)=(img1(i,j)+ img2(i,j))/2;
        }
    }
    return resultado;
}
///DIFERENCIA
CImg<unsigned char> DifImg(CImg<unsigned char> img1, CImg<unsigned char> img2){
    CImg<unsigned char> resultado(img1.width(),img1.height(),1,1);
    cimg_forXY(img1,i,j)
    {
        if((img1(i,j)- img2(i,j)/2) < 0)
        {
        resultado(i,j)= 0;
        }
        else
        {
            if((img1(i,j)- img2(i,j)/2) > 255){
                resultado(i,j)= 255;
            }else
            {
               resultado(i,j)= (img1(i,j)- img2(i,j))/2;
            }
        }
    }
    return resultado;
}
///MULTIPLICACION
CImg<unsigned char> multiplicacion(CImg<unsigned char> &img, CImg<unsigned char> &masc){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j) resultado(i,j)=img(i,j) * masc(i,j)/255; //divid0 por 255 para normalizar la mascara
    return resultado;
}
///DIVISION
CImg<unsigned char> division(CImg<unsigned char> &img, CImg<unsigned char> &masc){
    cimg_forXY(masc,i,j) masc(i,j) = 255 * 1/masc(i,j);
    return multiplicacion(img,masc);

}
///REDUCIR RUIDO //pasar una imagen con ruido en "img",  //genera la suma de "n" imagenes con ruido
//pasar lista de imagenes con ruido
CImg<unsigned char> reducRuido(CImgList<unsigned char>img){
    CImg<unsigned char> suma(img[0].width(),img[0].height(),1,1,0);
    for(unsigned char i=0;i<img.size();i++)
        suma=sumaImg(suma,img[i],0); //sumo
    return suma;
}

///umbral invertido
//recibe imagen en escala de gris
CImg<unsigned char> umbral_invertido(CImg<unsigned char> &img, int p){
    return negativo(img.get_threshold(p));
}

///umbral_por_tramos
//recibe imagen en escala de gris
CImg<unsigned char> umbral_por_tramos(CImg<unsigned char> &img, int p1,int p2){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j){
        if (img(i,j)<=p1 || img(i,j)>=p2)
            resultado(i,j)=255;
        else
            resultado(i,j)=0;
    }
    return resultado;
}

///umbral_por_tramos
//recibe imagen en escala de gris
CImg<unsigned char> umbral_por_tramos_gris(CImg<unsigned char> &img, int p1,int p2){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j){
        if (img(i,j)<=p1 || img(i,j)>=p2)
            resultado(i,j)=255;
        else
            resultado(i,j)=img(i,j);
    }
    return resultado;
}

///OR
//Or entre imagen binaria y una mascara binaria
CImg<unsigned char> ORimg(CImg<unsigned char> img, CImg<unsigned char> masc){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1,0);
    cimg_forXY(img,i,j){
        if ((int)*img.data(i,j,0,0)==0 & (int)*masc.data(i,j,0,0)==0)
            resultado(i,j)=0;
        else
            resultado(i,j)=1;
    }
    return resultado;
}

///AND
//And entre imagen binaria y una mascara binaria
CImg<unsigned char> ANDimg(CImg<unsigned char> &img, CImg<unsigned char> &masc){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            resultado(i,j)=(img(i,j)*masc(i,j));
    return resultado;
}

///MAYOR
// las imagenes en escala de griz
CImg<unsigned char> MAYORimg(CImg<unsigned char> &img, CImg<unsigned char> &img2){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            if ( img(i,j)>img2(i,j) )
            resultado(i,j)=1;
    else
    resultado(i,j)=0;

    return resultado;
}
///MENOR
//imagenes en escala de griz
CImg<unsigned char> MENORimg(CImg<unsigned char> &img, CImg<unsigned char> &img2){
    CImg<unsigned char> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            if ( img(i,j)<img2(i,j) )
            resultado(i,j)=1;
    else
    resultado(i,j)=0;

    return resultado;
}

///BINARIO
//Pasar numero a binario
vector<int> binario(int numero) {
    vector<int> bin;
    while(numero>=1){
        bin.push_back(numero%2);//voy guardando el modulo
        numero=numero/2;

    }
    while(bin.size()<8)
        bin.push_back(0);

    return bin;
}

///EMBOSS
//Filtro emboss
CImg<unsigned char> emboss(CImg<unsigned char> img,int corrimiento){
    CImg<unsigned char> img_neg(img.width(),img.height(),1,1);//
    img_neg = negativo(img);
    return sumaImg(img, img_neg,corrimiento);//suma a img su negativo un poquito desplazado
}
#endif // FUNCIONES

