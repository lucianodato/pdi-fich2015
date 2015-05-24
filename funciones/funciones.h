#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>
#include "CImg.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <complex>
#include <PDI_functions.h>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <time.h>       /* time */
#include <set>

using namespace cimg_library;
using namespace std;

#define EPS 0.00001

/// STRUCTS Y VARIABLES AUXILIARES

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

//Colores auxiliares

const unsigned char red[] = { 255,0,0 },
                    green[] = { 0,255,0 },
                    blue[] = { 0,0,255 },
                    white[] = { 255,255,255 },
                    black[] = { 0,0,0 },
                    yellow[] = { 255,255,0 };

struct Pixel {
    int x;
    int y;
    CImg<double>* img;

    Pixel() : x(0), y(0), img(NULL) {};
    Pixel(const Pixel& p) : x(p.x), y(p.y), img(p.img) {};
    Pixel(int x, int y, CImg<double>* img) : x(x), y(y), img(img) {};

    bool operator<( const Pixel& p ) const {
        return this->value() < p.value();
    }
    double value() const {
        return img->operator()(x,y);
    }
    bool AdentroImagen( ) {
        return x>=0 && y>=0 && x<img->width() && y<img->height();
    }
};

//------------------------------FUNCIONES AUXILIARES--------------------------------------------

///****************************************
///FUNCION NEGATIVO - Devuelve el negativo de una imagen
///****************************************
template<typename T>
CImg<T> negativo(CImg<T> imagen){
    cimg_forXY(imagen,i,j)
            imagen(i,j) = abs(((int)*imagen.data(i,j,0,0))-255);
    return imagen.normalize(0,255);
}

///--------FUNCIONES LUT----------

//s=a*r+c
//con r: valor de entrada
//a = factor de ganancia
//c = offset

//Caso generico. Recibe un gris inicial y un final. Por tramos
//item 1
template<typename T>
CImg<T> generar_lut(T a,T c,T ini,T fin){
    CImg<T> lut(1,abs(fin-ini)+1,1,1);
    T s;
    for (int i=ini;i<abs(fin-ini)+1;i++){
        s=T(a*i+c);
    ///--------------------------    if (s>255) s=255;
        if (s<0) s=0;
        lut(i)=s;
    }
    return lut;
}

//Funcion curva Solo cuando se necesitan tramos
template<typename T>
CImg <T> generar_curva(CImg<T> lut,vector<punto> puntos){
    T x0,x1,y0,y1;
    T a,c;
    a=1;
    c=0;
    CImg<T> curva(lut.width(),lut.height(),1,1),aux(lut.width(),lut.height(),1,1);

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

///LUT LOGARITMICA
// Si positiva es 1 Aclara la imagen
// Si positiva es 0 Oscurece la imagen
template<typename T>
CImg<T> generar_lut_logb(T c){
    CImg<T> lut(1,256,1,1);
    T s;
    for (int i=0;i<256;i++){
        //Aca mapeamos el rango total resultante para que despues se traduzca en un nivel de gris
        s=floor(c*(255*((log(1+i)/log(1+255)))));
        lut(i)=s;
    }
    return lut;

}



///LUT EXPONECIAL
// gamma es positivo
// 0 < gamma < 1 Aclara la imagenimgnueva
// gamma > 1 Oscurece la imagen
template<typename T>
CImg<T> generar_lut_expb(T c,T gamma){
    CImg<T> lut(1,256,1,1);
    T s;
    for (int i=0;i<256;i++){
        //s=floor(c*(pow(i,gamma))/255);
        s=c*(pow(i,gamma));
        lut(i)=s;
    }
    lut.normalize(0,255);
    return lut;
}

//aplica la transformacion que se la pase en "lut" a la imagen "img"
template<typename T>
CImg<T> transformacion(CImg<T> img,CImg<T> lut){
    cimg_forXY(img,i,j)
            img(i,j)=lut(img(i,j)); // "map"
    return img;
}

///****************************************
/// FUNCION DETECTAR_MEDIOTONO - Devuelve una imagen 3x3 del mediotono correspondiente a la intensidad recibida
///****************************************
template<typename T>
CImg<T> detectar_mediotono(T intensidad){
    
    CImg <T> nivel(3,3,1,1);
    
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
///****************************************
///FUNCION MEDIOTONO - Recibe una imagen y la devuelve en binario con los medios tonos correspondientes
///****************************************
template<typename T>
CImg<T> mediotono(CImg<T> original){

    CImg<T> modificada(original.width()*3,original.height()*3,1,1), aux(3,3,1,1);
    T var_x,var_y;
    
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

///****************************************
///FUNCION BINARIO - Caso que recibe un umbral (En la libreria esta la funcion get_threshold tambien)
///****************************************
template<typename T>
CImg<T> binario(CImg<T> imagen, T umbral){

    CImg<T> modificada(imagen.width(),imagen.height(),1,1);

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
///****************************************
///SUMA
///****************************************
//corrimiento=0 si quiero sumar sin corrimiento
template<typename T>
CImg<T> sumaImg(CImg<T> img1, CImg<T> img2, T corrimiento=0 ){
    CImg<T> resultado(img1.width(),img1.height(),1,1);
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
///****************************************
///DIFERENCIA
///****************************************
template<typename T>
CImg<T> DifImg(CImg<T> img1, CImg<T> img2){
    CImg<T> resultado(img1.width(),img1.height(),1,1);
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
///****************************************
///MULTIPLICACION
///****************************************
template<typename T>
CImg<T> multiplicacion(CImg<T> img, CImg<T> masc){
    CImg<T> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j) resultado(i,j)=img(i,j) * masc(i,j);
    return resultado;
}
///****************************************
///DIVISION
///****************************************
template<typename T>
CImg<T> division(CImg<T> &img, CImg<T> &masc){
    cimg_forXY(masc,i,j) masc(i,j) = 255 * 1/masc(i,j);
    return multiplicacion(img,masc);

}
///****************************************
///REDUCIR RUIDO //pasar una imagen con ruido en "img",  //genera la suma de "n" imagenes con ruido
///****************************************
//pasar lista de imagenes con ruido
template<typename T>
CImg<T> reducRuido(CImgList<T>img){
    CImg<T> suma(img[0].width(),img[0].height(),1,1,0);
    for(int i=0;i<img.size();i++)
        suma=sumaImg(suma,img[i],0); //sumo
    return suma;
}
///****************************************
///UMBRAL INVERTIDO
///****************************************
//recibe imagen en escala de gris
template<typename T>
CImg<T> umbral_invertido(CImg<T> &img, T p){
    return negativo(img.get_threshold(p));
}
///****************************************
///UMBRAL POR TRAMOS
///****************************************
//recibe imagen en escala de gris
template<typename T>
CImg<T> umbral_por_tramos(CImg<T> &img, T p1,T p2){
    CImg<T> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j){
        if (img(i,j)<=p1 || img(i,j)>=p2)
            resultado(i,j)=255;
        else
            resultado(i,j)=0;
    }
    return resultado;
}
///****************************************
///OR
///****************************************
//Or entre imagen binaria y una mascara binaria
template<typename T>
CImg<T> ORimg(CImg<T> img, CImg<T> masc){
    CImg<T> resultado(img.width(),img.height(),1,1,0);
    cimg_forXY(img,i,j){
        if ((int)*img.data(i,j,0,0)==0 & (int)*masc.data(i,j,0,0)==0)
            resultado(i,j)=0;
        else
            resultado(i,j)=1;
    }
    return resultado;
}
///****************************************
///AND
///****************************************
//And entre imagen binaria y una mascara binaria
template<typename T>
CImg<T> ANDimg(CImg<T> &img, CImg<T> &masc){
    CImg<T> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            resultado(i,j)=(img(i,j)*masc(i,j));
    return resultado;
}
///****************************************
///MAYOR
///****************************************
// las imagenes en escala de griz
template<typename T>
CImg<T> MAYORimg(CImg<T> &img, CImg<T> &img2){
    CImg<T> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            if ( img(i,j)>img2(i,j) )
            resultado(i,j)=1;
    else
    resultado(i,j)=0;

    return resultado;
}
///****************************************
///MENOR
///****************************************
//imagenes en escala de griz
template<typename T>
CImg<T> MENORimg(CImg<T> &img, CImg<T> &img2){
    CImg<T> resultado(img.width(),img.height(),1,1);
    cimg_forXY(img,i,j)
            if ( img(i,j)<img2(i,j) )
            resultado(i,j)=1;
    else
    resultado(i,j)=0;

    return resultado;
}
///****************************************
///BINARIO
///****************************************
//Pasar numero a binario
template<typename T>
vector<T> binario(T numero) {
    vector<T> bin;
    while(numero>=1){
        bin.push_back(numero%2);//voy guardando el modulo
        numero=numero/2;

    }
    while(bin.size()<8)
        bin.push_back(0);

    return bin;
}
///****************************************
///EMBOSS
///****************************************
//Filtro emboss
template<typename T>
CImg<T> emboss(CImg<T> img,int corrimiento){
    CImg<T> img_neg(img.width(),img.height(),1,1);//
    img_neg = negativo(img);
    return sumaImg(img, img_neg,corrimiento);//suma a img su negativo un poquito desplazado
}
///****************************************
///BLISTER
///****************************************
//Detector de faltantes de pastillas en bliter,
//Recive:la imagen blister (es deseable que este umbralizada o con buen contraste)
//Retorna: vector con coordenadas en las que faltan pastillas
template<typename T>
vector<punto> blister(CImg<T> img)
{   vector<punto> vectorcoord;
    punto puntos;
    for (int j=53;j<142;j=j+48)
        for (int i=53;i<img.width();i=i+50)
            if(img.get_crop(i-18,j-18,i+18,j+18).mean()<0.2){
                puntos.x=i;puntos.y=j;
                vectorcoord.push_back(puntos);
            }
    return vectorcoord;
}
///****************************************
///BIT LIST
///****************************************
template<typename T>
CImgList<T> bitlist(CImg<T> original)
{
    CImg<T> img_b0,img_b1,img_b2,img_b3,img_b4,img_b5,img_b6,img_b7;
    img_b0=img_b1=img_b2=img_b3=img_b4=img_b5=img_b6=img_b7=original;

    vector<T> bit;
    cimg_forXY(original,i,j){
        bit= binario(original(i,j));
        img_b0(i,j) = bit[0]*pow(2.0,0.0);
        img_b1(i,j) = bit[1]*pow(2.0,1.0);
        img_b2(i,j) = bit[2]*pow(2.0,2.0);
        img_b3(i,j) = bit[3]*pow(2.0,3.0);
        img_b4(i,j) = bit[4]*pow(2.0,4.0);
        img_b5(i,j) = bit[5]*pow(2.0,5.0);
        img_b6(i,j) = bit[6]*pow(2.0,6.0);
        img_b7(i,j) = bit[7]*pow(2.0,7.0);
    }

    CImgList<T> lista;
    lista.push_back(img_b0);
    lista.push_back(img_b1);
    lista.push_back(img_b2);
    lista.push_back(img_b3);
    lista.push_back(img_b4);
    lista.push_back(img_b5);
    lista.push_back(img_b6);
    lista.push_back(img_b7);

    return lista;
}

///-------------FILTRADO ESPACIAL-------------------------

///****************************************
///KERNEL PROMEDIO
///****************************************
//Funcion que devuelve el kernel promediado en func. del tamaño
//template<typename T>
CImg<double> mask(double tamanio){

    CImg<double> mascara (tamanio,tamanio,1,1,1);

    //Retorno el kernel.Tamaño
    return mascara/(tamanio*tamanio);

}
///****************************************
///GENERADOR DE KERNEL GAUSSIANO
///****************************************
/**
 * \file         gauss_filter.h
 * \author       Alain Lehmann <lehmann at vision.ee.ethz.ch>
 * \version      $Id: gauss_filter.h 337 2009-09-22 16:01:15Z lehmanal $
 * \date         2009-09-22 created
 */

/** compute Gaussian derivatives filter weights
 * \param sigma = bandwidth of the Gaussian
 * \param deriv = computing the 'deriv'-th derivatives of a Gaussian
 * the width of the filter is automatically determined from sigma.
 * g  = \frac{1}{\sqrt{2\pi}\sigma}   \exp(-0.5 \frac{x^2}{\sigma^2} )
 * g' = \frac{x}{\sqrt{2\pi}\sigma^3} \exp(-0.5 \frac{x^2}{\sigma^2} )
 * /   = -\frac{x}{\sigma^2} g
 * g''= (\frac{x^2}{\sigma^2} - 1) \frac{1}{\sigma^2} g
 */
template<typename T>
CImg<T> gauss_filter (T sigma=1, T deriv=0) {
    T width = 3*sigma;               // may be less width?
    T sigma2 = sigma*sigma;
    CImg<T> filter;
    filter.assign(floor(2*width)+1);

    int i=0;
    for (T x=-width; x<=width; x+=1.0f) {
        T g = exp(-0.5*x*x/sigma2) / sqrt(2*M_PI) / sigma;
        if (deriv==1) g *= -x/sigma2;
        if (deriv==2) g *= (x*x/sigma2 - 1)/sigma2;
        filter[i] = g ;
        //printf ("i=%f -> %f\n", x, filter[i]);
        i++;
    }
    return filter;
}
///****************************************
///ROBERTS
///****************************************
///idea de gradiente en dos direcciones
template<typename T>
CImg<T> roberts(CImg<T> img){
    CImg<T> Gx(3, 3), Gy(3,3);
    Gx(0,0)=0; Gx(0,1)=0; Gx(0,2)=0;
    Gx(1,0)=0; Gx(1,1)=-1; Gx(1,2)=0;
    Gx(2,0)=0; Gx(2,1)=0; Gx(2,2)=1;

    Gy(0,0)=0; Gy(1,0)=0; Gy(2,0)=0;
    Gy(0,1)=0; Gy(1,1)=0; Gy(2,1)=-1;
    Gy(0,2)=0; Gy(1,2)=1; Gy(2,2)=0;

    return (img.get_convolve(Gx)+img.get_convolve(Gy)).abs().normalize(0,255);
}
///****************************************
///SOBEL
///****************************************
///idea de gradiente en dos direcciones
template<typename T>
CImg<T> Sobel(CImg<T> img,int tipo = 0){

    //Sobel con valor de entrada 0 con tendencia vertical y horizontal
    //Cuando el valor de entrada es 1 tiene tendencia diagonal
    CImg<T> Gx(3, 3),Gy(3, 3);

    if(tipo ==0){
        Gx(0,0)=-1; Gx(0,1)=-2; Gx(0,2)=-1;
        Gx(1,0)=0; Gx(1,1)=0; Gx(1,2)=0;
        Gx(2,0)=1; Gx(2,1)=2; Gx(2,2)=1;

        Gy(0,0)=-1; Gy(1,0)=0; Gy(2,0)=1;
        Gy(0,1)=-2; Gy(1,1)=0; Gy(2,1)=2;
        Gy(0,2)=-1; Gy(1,2)=0; Gy(2,2)=1;

    }

    else{

        Gx(0,0)=0; Gx(0,1)=1; Gx(0,2)=2;
        Gx(1,0)=-1; Gx(1,1)=0; Gx(1,2)=1;
        Gx(2,0)=-2; Gx(2,1)=-1; Gx(2,2)=0;

        Gy(0,0)=-2; Gy(1,0)=-1; Gy(2,0)=0;
        Gy(0,1)=-1; Gy(1,1)=0; Gy(2,1)=1;
        Gy(0,2)=0; Gy(1,2)=1; Gy(2,2)=2;
    }


    return (img.get_convolve(Gx)+img.get_convolve(Gy)).abs().normalize(0,255);
}
///****************************************
///PREWITT
///****************************************
///idea de gradiente en dos direcciones
template<typename T>
CImg<T> prewitt(CImg<T> img,int tipo=0){
    //Prewitt con valor de entrada 0 con tendencia vertical y horizontal
    //Prewitt el valor de entrada es 1 tiene tendencia diagonal
    CImg<T> Gx(3, 3),Gy(3, 3);

    if(tipo ==0){
        Gx(0,0)=-1; Gx(0,1)=-1; Gx(0,2)=-1;
        Gx(1,0)=0; Gx(1,1)=0; Gx(1,2)=0;
        Gx(2,0)=1; Gx(2,1)=1; Gx(2,2)=1;

        Gy(0,0)=-1; Gy(1,0)=0; Gy(2,0)=1;
        Gy(0,1)=-1; Gy(1,1)=0; Gy(2,1)=1;
        Gy(0,2)=-1; Gy(1,2)=0; Gy(2,2)=1;

    }

    else{

        Gx(0,0)=0; Gx(0,1)=1; Gx(0,2)=1;
        Gx(1,0)=-1; Gx(1,1)=0; Gx(1,2)=1;
        Gx(2,0)=-1; Gx(2,1)=-1; Gx(2,2)=0;

        Gy(0,0)=-1; Gy(1,0)=-1; Gy(2,0)=0;
        Gy(0,1)=-1; Gy(1,1)=0; Gy(2,1)=1;
        Gy(0,2)=0; Gy(1,2)=1; Gy(2,2)=1;
    }


    return (img.get_convolve(Gx)+img.get_convolve(Gy)).abs().normalize(0,255);
}

///****************************************
///LAPLACIANO
///****************************************
///idea de gradiente en dos direcciones
template<typename T>
CImg<T> laplaciano(CImg<T> img,int tipo =0){
    //LAPLACIANO con valor de entrada 0 valido para aproximación con N4 --> G = 4z5-(z2+z4+z6+z8)
    //LAPLACIANO el valor de entrada 1, valido para aproximación con N8 --> G = 8z5-(z1+z2+z3+z4+z6+z7+z8+z9)
    CImg<T> G(5,5);

    if(tipo ==0){
        G(0,0)=0; G(0,1)=-1; G(0,2)=0;
        G(1,0)=-1; G(1,1)=4; G(1,2)=-1;
        G(2,0)=0; G(2,1)=-1; G(2,2)=0;

    }

    else{

        G(0,0)=-1; G(0,1)=-1; G(0,2)=-1;
        G(1,0)=-1; G(1,1)=8; G(1,2)=-1;
        G(2,0)=-1; G(2,1)=-1; G(2,2)=-1;
    }


    return img.get_convolve(G).abs().normalize(0,255);
}

///****************************************
///LoG (Laplaciano del gaussiano)
///****************************************
///idea de gradiente en dos direcciones
template<typename T>
CImg<T> LoG(CImg<T> img){
    CImg<T> G(5,5);

        G(0,0)=0; G(0,1)=0; G(0,2)=-1;G(0,3)=0; G(0,4)=0;
        G(1,0)=0; G(1,1)=-1; G(1,2)=-2;G(1,3)=-1; G(1,4)=0;
        G(2,0)=-1; G(2,1)=-2; G(2,2)=16;G(2,3)=-2; G(2,4)=-1;
        G(3,0)=0; G(3,1)=-1; G(3,2)=-2;G(3,3)=-1; G(3,4)=0;
        G(4,0)=0; G(4,1)=0; G(4,2)=-1;G(4,3)=0; G(4,4)=0;

    return img.get_convolve(G).abs().normalize(0,255);
}

///****************************************
///FILTRO DE ALTA POTENCIA 1 CANAL
///****************************************
//Recibe la imagen el kernel pasa bajo y la amplificacion
template<typename T>
CImg<T> filtroAP(CImg<T> img,CImg<T> kernel,T amp){
    //auxiliares
    CImg<T> pb,dif,sum;

    //Aplico filtro
    pb=img.get_convolve(kernel);

    //Se lo resto a lo original para generar el pasa alto
    dif=DifImg(img,pb);

    //Lo sumo a la original para generar alta potencia
    sum=sumaImg((1-amp)*img,dif);

    return sum;
}

///****************************************
///FILTRO DE ALTA POTENCIA 3 CANALES
///****************************************
//Recibe la imagen el kernel pasa bajo y la amplificacion
template<typename T>
CImg<T> filtroAP3(CImg<T> img,CImg<T> kernel, T amp){

    CImg<T> c1,c2,c3;

    //Aplico alta potencia a cada canal por separado
    c1 = filtroAP(img.get_channel(0),kernel,amp);
    c2 = filtroAP(img.get_channel(1),kernel,amp);
    c3 = filtroAP(img.get_channel(2),kernel,amp);

    //Devuelvo la suma de canales
    return c1+c2+c3;
}

///PROMEDIO HISTOGRAMA
template<typename T>
CImg<T> promedio_histograma(CImgList<T> lista){

    CImg <T> img,promedio(256,1);
    promedio = lista(0);

    for (int p=1;p<lista.size();p++){
        img = lista(p);
         for (int i=0;i<promedio.width();i++){
            promedio(i)+=img(i);
            promedio(i)*=0.5;
        }
    }

    return promedio;

}
///****************************************
///HISTOGRAMA
///****************************************
/// Construye un histograma y lo devuelve en una imagen
template <class T>
CImg<T> draw_histogram(CImg<T> &img){
    CImg<T> histograma;
    histograma.assign(img.width(), img.height(), 1, img.spectrum());
    histograma.fill(0);
    if(img.spectrum()==1){ // es de 1 solo canal
        T white[]={255};
        histograma.draw_graph(img.get_histogram(256, 0, 255), white, 1 , 3, 0);
    }else{
        T red[]={255,0,0};
        T green[]={0,255,0};
        T blue[]={0,0,255};
        CImg<T> r, g, b;
        r=img.get_channel(0);
        g=img.get_channel(1);
        b=img.get_channel(2);
        histograma.draw_graph(r.get_histogram(256, 0, 255), red, 1 , 1, 0);
        histograma.draw_graph(g.get_histogram(256, 0, 255), green, 1 , 1, 0);
        histograma.draw_graph(b.get_histogram(256, 0, 255), blue, 1 , 1, 0);
    }
    return histograma;
}

///****************************************
///ECUALIZACION LOCAL DE HISTOGRAMA
///****************************************
// ecualizacion /de histograma local para unsigned char descartando los bordes
template<typename T>
void LocalHistoEq(CImg<T> &img, T windowSize){
    //CImg<T> histo=img.get_histogram(256, 0, 255);
    CImg<T> ret(img.width()-windowSize*2-1, img.height()-windowSize*2-1);
    T i, j, m, l, ii, jj, mm, ll;
    ii=img.width()-windowSize-1; //img original menos el borde
    jj=img.height()-windowSize-1;
    T pixelValue;//valor actual de pixel
    T newPixelValue;	//nuevo valor de pixel
    // recorre los pixeles de la imagen original
    for(i=windowSize; i<ii; i++){
        for(j=windowSize; j<jj; j++){
            // calcula el nuevo valor del pixel segun la ecualizacion de histograma local
            pixelValue=img(i,j);
            mm=i+windowSize;
            ll=j+windowSize;
            // recorre la ventana
            newPixelValue=0;
            //ahora recorro solamente la porcion determinada por la ventana
            for(m=i-windowSize; m<mm; m++){
                for(l=j-windowSize; l<ll; l++){
                    if(img(m,l)<=pixelValue) //si el valor de imagen es menor al valor actual de pixel, sumar hasta que sea mayor
                        newPixelValue++;     //newPixelValue es el valor cumulado
                }
            }
            // el valor que le corresponde al nuevo pixel segun la probabilidad acumulada
            newPixelValue*=255.0/float((windowSize*2+1)*(windowSize*2+1)); // normaliza la imagen y saca probabilidad acumulada
            ret(i-windowSize,j-windowSize)=newPixelValue;
        }
    }
    img=ret;
}



///****************************************
/// CARGAR PALETA
///****************************************
//uso esta funcion como funcion auxiliar dentro de "Aplicar Paleta"
//cargo paleta de color desde archivo del disco
//paleta= se guardan los valores leidos desde archivo
//nombre= ruta completa al archivo en disco de la paleta
int cargar_paleta(vector< vector< float> > &paleta, string nombre) {
    vector< float > plinea;
    string cad, rS, gS, bS;
    float r, g, b;
    int pos, nval;

    ifstream arch(nombre.c_str());
    if (arch.fail()) {
        cerr << "ERROR al abrir el archivo " << nombre << endl;
        return 1;
    } else {
        paleta.clear();
        // lee cuantos valores por fila
        getline(arch,cad);
        nval=0;
        pos=cad.find_first_of(".");
        while (pos>0) {
            cad.erase(0,pos+1);
            pos=cad.find_first_of(".");
            nval++;
        }
        arch.close();
        arch.open(nombre.c_str());
        plinea.resize(nval);
        while (getline(arch,cad)) {
            pos=cad.find_first_not_of(" ");
            cad.erase(0,pos);
            pos=cad.find_first_of(" ");
            rS=cad.substr(0,pos);
            r=atof(rS.c_str());
            plinea[0]=r;
            cad.erase(0,pos);
            pos=cad.find_first_not_of(" ");
            cad.erase(0,pos);
            pos=cad.find_first_of(" ");
            gS=cad.substr(0,pos);
            g=atof(gS.c_str());
            plinea[1]=g;
            cad.erase(0,pos);
            pos=cad.find_first_not_of(" ");
            cad.erase(0,pos);
            pos=cad.find_first_of(" ");
            bS=cad.substr(0,pos);
            b=atof(bS.c_str());
            plinea[2]=b;
            paleta.push_back(plinea);
        }
        arch.close();
        return 0;
    }
}

///****************************************
///APLICAR PALETA
///****************************************
// parametros:
//Imagen a la que se la aplica la paleta,
//Rruta completa de la ubicacion de archivo de paleta
CImg<float> AplicarPaleta(CImg<float> img, string nomPaleta){
    CImg<float> ret(img.width(), img.height(), 1, 3);

    vector< vector<float> > paleta;
    cargar_paleta(paleta, nomPaleta);

    img.normalize(0, 255);
    for(unsigned i=0; i<img.width(); i++){
        for(unsigned j=0; j<img.height(); j++){
            ret(i,j,0,0)=paleta[unsigned(img(i,j))][0];
            ret(i,j,0,1)=paleta[unsigned(img(i,j))][1];
            ret(i,j,0,2)=paleta[unsigned(img(i,j))][2];
        }
    }

    return ret;
}

///****************************************
///COMPLEMENTO COLOR
///****************************************
///la idea es girar el H 180 grados en todos sus puntos(como decia Rena)
///  de la circunfencia del plato de color
/// y e invertir la intensidad
template <class T>
CImg<T> complemento_color(CImg<T> img){
    img.RGBtoHSI();
    cimg_forXY(img,i,j){
        img(i,j,0,0)+=180;
        if(img(i,j,0,0) > 360)
            img(i,j,0,0)=(img(i,j,0,0)-360);
        img(i,j,0,2)=1-img(i,j,0,2);//Hace el negativo de la intensidad
	}
    img.HSItoRGB();
    return img;
}

template <class T>
void ComposeRGB(CImg<T> &img, CImg<T> &r, CImg<T> &g, CImg<T> &b){
    int ww=r.width(), hh=r.height(), i, j;
    img.assign(ww, hh, 1, 3);
    for(i=0; i<ww; i++){
        for(j=0; j<hh; j++){
            img(i,j,0,0)=r(i,j);
            img(i,j,0,1)=g(i,j);
            img(i,j,0,2)=b(i,j);
        }
    }
}

template <class T>
CImg<T>  ComposeHSI(CImg<T> h, CImg<T> s, CImg<T> I){
    CImg<T> img;
    int ww=h.width(), hh=h.height(), i, j;
    img.assign(ww, hh, 1, 3);
    img.RGBtoHSI();
    for(i=0; i<ww; i++){
        for(j=0; j<hh; j++){
            img(i,j,0,0)=h(i,j);
            img(i,j,0,1)=s(i,j);
            img(i,j,0,2)=I(i,j);
        }
    }
    img.HSItoRGB();
}


///****************************************
/// Color Slicing RGB
///****************************************
template <class T>
CImg<T> ColorMaskRGB(CImg<T> img, unsigned char x, unsigned char y, float radio){
	unsigned ww=img.width();
	unsigned hh=img.height();   
	T r0, g0, b0;
	r0=img(x, y, 0, 0);
	g0=img(x, y, 0, 1);
	b0=img(x, y, 0, 2);
	float dist;
	for(unsigned i=0; i<ww; i++){
		for(unsigned j=0; j<hh; j++){
			dist=sqrt(powf(r0-img(i,j,0,0),2)+powf(g0-img(i,j,0,1),2)+powf(b0-img(i,j,0,2),2));
			if(dist>radio){
				img(i,j,0,0)=0;
				img(i,j,0,1)=0;
				img(i,j,0,2)=0;
			}
		}
	}
    return img;
}
///****************************************
/// Color Slicing HSI
///****************************************
template <class T>
CImg<T> ColorMaskHSI(CImg<T> img, unsigned mx, unsigned my, float radio){
    img.RGBtoHSI();
    T h=img(mx, my, 0, 0);//h
    T s=img(mx, my, 0, 1);//s
    T i=img(mx, my, 0, 2);//I
	unsigned ww=img.width();
	unsigned hh=img.height();
	float dist;
	for(unsigned i=0; i<ww; i++){
		for(unsigned j=0; j<hh; j++){
			dist=sqrt(powf(h-img(i,j,0,0),2)+powf(s-img(i,j,0,1),2));
			if(dist>radio){
                img(i,j,0,0)=0;//h
                img(i,j,0,1)=0;//s
                img(i,j,0,2)=0;//I
			}
		}
	}
    return img.HSItoRGB();
}


///****************************************
///COPIA CANAL A CANAL
///****************************************
//Sirve para no tener que escribir los ciclos en el main
template<typename T>
CImg<T> copia_canal(CImg<T> img_orig,int canal,CImg<T> img_a_copiar,int canal_a_copiar){
    cimg_forXYZ(img_orig,i,j,k)
            img_orig(i,j,k,canal) = img_a_copiar(i,j,k,canal_a_copiar);
    return img_orig;
}


///----------------FILTRADO FRECUENCIAL------------------------

///****************************************
///TRANSFORMADA DE FOURIER
///****************************************
//devuelve la magnitud la fase la magnitud con escala logaritmica con shift y la fase con escala logaritmica con shift
template<typename T>
CImgList<T> fourier(CImg<T> img){

    CImgList<T>TDF_img=img.get_FFT();
    CImg<T>TDF_real=TDF_img[0];
    CImg<T>TDF_imaginaria=TDF_img[1];

    complex<T>I(0.0,1.0);

    CImg<T>magnitud(img.width(),img.height(),1,1);
    CImg<T>fase(img.width(),img.height(),1,1);

    CImg<T>magnitud_log(img.width(),img.height(),1,1);
    CImg<T>fase_log(img.width(),img.height(),1,1);

    for (int i=0;i<img.width();i++){
        for (int j=0;j<img.height();j++){
            magnitud(i,j)=sqrt(pow(TDF_real(i,j),2)+pow(TDF_imaginaria(i,j),2));
            complex<T>complejo=TDF_real(i,j)+I*TDF_imaginaria(i,j);
            fase(i,j)=arg(complejo);

            //Calculo la magnitud y fase para mostrar en el display()
            magnitud_log(i,j) = log(magnitud(i,j) + 1);
            fase_log(i,j) = log(fase(i,j) + 1);

        }
    }


    magnitud_log = magnitud_log.get_shift(img.width()/2,img.height()/2,0,0,2);
    fase_log = fase_log.get_shift(img.width()/2,img.height()/2,0,0,2);


    CImgList<T> lista(magnitud,fase,magnitud_log,fase_log);

    return lista;
}

///****************************************
///TRANSFORMADA DE FOURIER INVERSA
///****************************************
//devuelve la magnitud la fase la magnitud con escala logaritmica con shift y la fase con escala logaritmica con shift
template<typename T>
CImg<T> fourier_inv(CImg<T> magnitud,CImg<T> fase){

    CImg<T> realfft(magnitud.width(),magnitud.height(),1,1);
    CImg<T> imaginariafft(fase.width(),fase.height(),1,1);

    complex<T>I(0.0,1.0);
    for (int i=0;i<magnitud.width();i++){
        for (int j=0;j<magnitud.height();j++){
            realfft(i,j)=real(magnitud(i,j)*exp(I*fase(i,j)));
            imaginariafft(i,j)=imag(magnitud(i,j)*exp(I*fase(i,j)));

        }
    }

    CImgList<T> orig(magnitud,fase);
    orig[0] = realfft;
    orig[1] = imaginariafft;
    return orig.get_FFT(true)[0];
}

///****************************************
///FILTRADO EN FRECUENCIA - APLICAR FILTRO
///****************************************
//Filtra en frecuencia a partir de una imagen y un filtro
template<typename T>
CImg<T> filtrar(CImg<T> img,CImg<T> filt){
    CImgList<T> img_tr = fourier(img);

    //Acomodo la mascara--> SHIFT de respuesta en frecuencia del filtro antes de multiplicar con la FFT de la img
    filt.shift(filt.width()/2,filt.height()/2,0,0,2);

    return fourier_inv(img_tr.at(0).mul(filt),img_tr.at(1));
}

///****************************************
///FILTRO IDEAL
///****************************************
template <class T>
CImg<T> ideal_mask(CImg<T> &img,T d, bool highpass=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);
    d=d*d;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            if((powf(i-w_2,2)+powf(j-h_2,2))<=d){
                mask(i, j)=!highpass;
            }else{
                mask(i, j)=highpass;
            }

        }
    }
    return mask;
}

///****************************************
///FILTROS BUTTER
///****************************************
template <class T>
CImg<T> butterworth_mask(CImg<T> &img, T d,unsigned o, bool highpass=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);
    float dist;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            dist=sqrt(powf(i-w_2,2)+powf(j-h_2,2));
            mask(i,j)=1/(1+powf(highpass?d/dist:dist/d,2*o));

        }
    }
    return mask;
}

///****************************************
///FILTROS GAUSSIANOS
///****************************************
template <class T>
CImg<T> gaussian_mask(CImg<T> &img, T d, bool highpass=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);
    float dist;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            dist=sqrt(powf(i-w_2,2)+powf(j-h_2,2));
            mask(i,j)=exp(-powf(dist,2)/(2*powf(d,2)));
            if(highpass) mask(i,j)=1-mask(i,j);
        }
    }
    return mask;
}

///****************************************
///FILTROS PASABANDA IDEAL
///****************************************
template <class T>
CImg<T> ideal_band(CImg<T> &img,T d,T W,bool pass=false){
    //Preproceso d para que la frecuencia sea la centrada en W/2
    d=d-W/2;

    if(pass){
        return multiplicacion(ideal_mask(img,d+W),ideal_mask(img,d,true));//pasabanda
    }
    else{
        return sumaImg(ideal_mask(img,d),ideal_mask(img,d+W,true));//rechazabanda
    }
}

///****************************************
///FILTROS PASABANDA BUTTER
///****************************************
template <class T>
CImg<T> butter_band(CImg<T> &img,T d,T W,unsigned o,bool pass=false){
    //corro de para que este en un borde y no en el centro de la frecuencia del filtro
    d=d-W/2;

    if(pass){
        return multiplicacion(butterworth_mask(img,d+W,o),butterworth_mask(img,d,o,true));//pasabanda
    }
    else{
        return sumaImg(butterworth_mask(img,d,o),butterworth_mask(img,d+W,o,true));//rechazabanda
    }
}

///****************************************
///FILTROS PASABANDA GAUSSIANOS
///****************************************
template <class T>
CImg<T> gaussian_band(CImg<T> &img,T d,T W,bool pass=false){
    //corro de para que este en un borde y no en el centro de la frecuencia del filtro
    d=d-W/2;

    if(pass){
        return multiplicacion(gaussian_mask(img,d+W),gaussian_mask(img,d,true));//pasabanda
    }
    else{
        return sumaImg(gaussian_mask(img,d),gaussian_mask(img,d+W,true));//rechazabanda
    }
}

///****************************************
///FILTROS NOTCH IDEAL
///****************************************
template <class T>
CImg<T> ideal_notch(CImg<T> &img,T d,T u0,T v0,bool notch=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            if(sqrt(powf(i-w_2-u0,2)+powf(j-h_2-v0,2))<=d || sqrt(powf(i-w_2+u0,2)+powf(j-h_2+v0,2))<=d){
                mask(i, j)=!notch;
            }else{
                mask(i, j)=notch;
            }

        }
    }
    return mask;
}

///****************************************
///FILTROS NOTCH BUTTER
///****************************************
template <class T>
CImg<T> butter_notch(CImg<T> &img,T d,unsigned o,T u0,T v0,bool notch=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);
    float dist1,dist2;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            dist1=sqrt(powf(i-w_2-u0,2)+powf(j-h_2-v0,2));
            dist2=sqrt(powf(i-w_2+u0,2)+powf(j-h_2+v0,2));
            mask(i,j)=1/(1+powf(notch?(powf(d,2)/(dist1*dist2)):((dist1*dist2)/powf(d,2)),o));

        }
    }
    return mask;
}

///****************************************
///FILTROS NOTCH GAUSSIANOS
///****************************************
template <class T>
CImg<T> gaussian_notch(CImg<T> &img,T d,T u0,T v0,bool notch=false){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);
    float dist1,dist2;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            dist1=sqrt(powf(i-w_2-u0,2)+powf(j-h_2-v0,2));
            dist2=sqrt(powf(i-w_2+u0,2)+powf(j-h_2+v0,2));
            mask(i,j)=exp(-(dist1*dist2)/(2*powf(d,2)));
            if(notch) mask(i,j)=1-mask(i,j);
        }
    }
    return mask;
}


///****************************************
///FILTROS LAPLACIANOS
///****************************************
template <class T>
CImg<T> laplacian_mask(CImg<T> &img){
    int i, j, w=img.width(), h=img.height(), w_2=w/2, h_2=h/2;
    CImg<T> mask(w, h, 1, 1);

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            mask(i,j)=-(powf(i-w_2,2)+powf(j-h_2,2));
        }
    }
    return mask;
}


///****************************************
/// FILTRO HOMOMORFICO
//@ Genera un filtro homomorfico
///****************************************
template <class T>
CImgList<T> filtroHomomorfico(unsigned int w, unsigned int h, unsigned int frec_corte, T gamma_l, T gamma_h, T c) {
    CImgList<T> img(2, w, h, 1, 1, 0);

    unsigned int centro_x = w/2;
    unsigned int centro_y = h/2;
    unsigned int fcp = pow(frec_corte,2);

    cimg_forXY(img[0],x,y) {
        double distancia = ( (x - centro_x)*(x - centro_x) + (y - centro_y)*(y - centro_y));
        double argumento = -c * distancia/fcp;

        img[0](x,y) = (gamma_h - gamma_l) * (1 - exp (argumento)) + gamma_l;
    }
    img[0].display(); //display para ver H
    return img;
}



//Toma una imagen color retorna si imagen en gris
CImg<double> colorToBW(CImg<double> img) {
    if (img.spectrum() == 1) return img;
    else return img.get_RGBtoHSI().get_channel(2);
}

//DEFINICION DE FILTRO HOMOMORFICO
//float gammaH=0.98,
//	gammaL=0.9;
//float D0=0.7;
//float c=1;

//_frec_corte = 150;
// gamma_l = 0.9;
//gamma_h = 1.1
// c = 1.0
///****************************************
/// WRAPPER FILTRO HOMOMORFICO
//est wrapper aplica los pasos nesesarios en el filtrado homomorfico , ademas de la definicion del filtro
//que se define en la funcion anterior
///****************************************
CImg<double> filtradoHomomorficoCompleto(CImg<double> img, unsigned int frec_corte, float gamma_l, float gamma_h, float c) {
    int w=img.width(), h=img.height();
    CImgList<double> filtro_homomorfico = filtroHomomorfico(w, h,frec_corte,gamma_l,gamma_h,c);
    //filtro_homomorfico[0].display();
    //Calculamos el logaritmo de la imagen
    CImg<double> log_img(w, h, 1, 1, 0);

    cimg_forXY(img,x,y) {
        if (img(x,y) < 1.0) //Si el logaritmo es menor a 1, explota por lo tanto controlo eso y asigno cero si se da el caso
            log_img(x,y) = 0.0;
        else
            log_img(x,y) = log(img(x,y));
    }
    //Filtramos (devuelve el resultado antitransformado)
    CImg<float> resultado_filtrado = filtrar(log_img,filtro_homomorfico.at(0));
    //Exponenciamos
    CImg<double> resultado_exp = resultado_filtrado.get_normalize(0,1).get_exp().get_normalize(0,255);
    //equlize
    CImg<double> resultado_filtrado_equ = resultado_exp.get_equalize(256);
    return resultado_filtrado_equ;

}

///****************************************
///FILTRO DE ENFASIS DE ALTA POTENCIA (FREC.)
///****************************************
//Recibe los parametros a = (A-1) y b. 
// Si b = 1 el resultado es un filtro de alta potencia.
// si b> 1 con b>a, entonces obtengo como resultado el filtro de enfasis en alta potencia. 
CImg<double> filtroAP_frecuencia(CImg<double> img,double alpha,double b) {

    //img, frecuencia de corte (D0) y bandera = true [Highpass filter]
    //En este caso uso el gaussiano pero puede ser tambien ideal, butter o laplaciano
    double frec_corte = img.width()/4; //nyquest / 2---> (w/2)/2

    CImg<double>  filtro_PA= gaussian_mask(img,frec_corte,true);

    CImg<double> Resultado,filtro_frec;

    //Calculo el filtro AP o EAF en funcion de los parametros alpha y b
    filtro_frec = alpha + b*filtro_PA;

    //Filtro y obtengo el resultado
    Resultado = filtrar(img,filtro_frec);

    return Resultado;

}


///****************************************
///FILTRO DE FILTRADO DE RUIDO (DENOISE)
///****************************************

//media geometrica
template <class T>
T media_geometrica(CImg<T> window){
    T val=1.0;
    cimg_forXY(window,x,y){
        val*=window(x,y);
    }
    val=pow(val,T(1)/(window.width()*window.height()));
    return val;
}

//media contraarmonica
template <class T>
T media_carmonica(CImg<T> window,int Q){
    T val1=0.0;
    T val2=0.0;
    cimg_forXY(window,x,y){
        val1+=pow(window(x,y),Q+1);
        val2+=pow(window(x,y),Q);
    }

    return val1*1.0/(val2*1.0);
}

//mediana
template <class T>
T mediana(CImg<T> window){

    vector<T> v;
    cimg_forXY(window,x,y)
        v.push_back(window(x,y));
    sort(v.begin(),v.end());//ordeno
    if(v.size()%2!=0) // si el numero de elementos  de la ventana es impar
        return v.at((v.size()+1)/2);
    else //si el numero de elementos de la ventana es par...
        //es nesesario este caso o la ventana sera siempre de cantidad impar???
        return v.at(v.size()/2);
}

//auxiliar para moda
template <class T>
T most_appeared(vector<T> v){
    int contador = 1;
    int max = 0;
    int valor;
    for (int i = 1; i = v.size()-1;i++){
        if(v[i] == v[i-1]){
            contador+=1;//Si el numero actual es igual al anterior aumento el contador
        }
        else
        {
            contador = 1;//Si el numero actual es otro reseteo el contador
        }

        if(contador > max){
            max = contador;
            valor = v[i];
        }
    }

    return valor;
}

//moda
template <class T>
T moda(CImg<T> window){

    vector<T> v;
    cimg_forXY(window,x,y)
        v.push_back(window(x,y));
    sort(v.begin(),v.end());//ordeno
    //Cuento cual es el valor que mas aparece
    return most_appeared(v);

}

//maximo
template <class T>
T maximo(CImg<T> window){
    return window.max();
}

//minimo
template <class T>
T minimo(CImg<T> window){
    return window.min();
}

//punto medio
template <class T>
T punto_medio(CImg<T> window){
    return 	(window.min()+window.max())/2;
}

//media alfarecortado
template <class T>
T media_alfarecortado(CImg<T> window,int d){
    vector<T> v;
    cimg_forXY(window,x,y){
        v.push_back(window(x,y));
    }
    sort(v.begin(),v.end());
    for (int i=0;i<d/2;i++){
        v.erase(v.begin());
        v.pop_back();
    }

    T val=0.0;
    for(int i=0;i<v.size();i++){
        val+=v[i];
    }

    return val/(T)v.size();

}

//ecualizacion local
template <class T>
T equalize_local(CImg<T> window){
    int N=window.width(),M=window.height();
    window.equalize(256);
    return window(N/2,M/2);

}

double distancia(double v1,double v2){
    return abs(v1-v2);
}

double filtro_distancias(CImg<double> window){
    double Rij=0,Rijviejo=99999;//,pivot=0;
    cimg_forXY(window,x,y){
        Rij=0;
        cimg_forXY(window,z,w){
            Rij+=abs(window(x,y,0,0)-window(z,w,0,0))+abs(window(x,y,0,1)-window(z,w,0,1))+abs(window(x,y,0,2)-window(z,w,0,2));
        }
        if  (Rij<Rijviejo)
            Rijviejo=Rij;

    }
    return Rijviejo;
}


//int tipofiltro : 1 MEDIA GEOMETRICA , 2 MEDIA CONTRAARMONICA
//                 3 MEDIANA, 4 PUNTO MEDIO ,5 PUNTO MEDIO RECORTADO,6 MAX, 7 MIN
//el parametro Q para MEDIA CONTRAARMONICA:


///media armonica= para ruido sal (malo para pimienta), bueno para gaussiano
///1.media geometrica= bueno ruido gaussiano
///2.media contra armonica
    //Q=-1 media armonica
    //Q=0 media aritmetica
    //Q>0 = elimina pimienta
    //Q<0 =elimina sal
///3.mediana= ruido impulsivo (sin desenfoque)
///moda = ruido impulsivo (malo para otro tipo de ruido)
///4.punto medio = ruido gaussiano o uniforme
///5.media alfa recortado= Comportamiento situado entre la media aritmética y la mediana,dependiendo del valor de d
///6.max = ruido sal
///7.minimo = ruido pimienta
///9.moda = ruido impulsivo

template <class T>
CImg<T> denoise(CImg<T> img,int sizew,int tipofiltro,int Q=0,int d=0){

    int N=img.height(),
        M=img.width();
    int medio=sizew/2;//posicion del medio de la ventana

    CImg<T> imgout(M,N),window(sizew,sizew);


    for (int x=medio;x<M-medio;x++){
        for(int y=medio;y<N-medio;y++){
            //asigno datos a mi ventana
            window=img.get_crop(x-medio,y-medio,x+medio,y+medio);
            switch(tipofiltro){
            case 1:
                imgout(x,y)=media_geometrica(window);
                break;
            case 2:
                imgout(x,y)=media_carmonica(window,Q);
                break;
            case 3:
                imgout(x,y)=mediana(window);
                break;
            case 4:
                imgout(x,y)=punto_medio(window);
                break;
            case 5:
                imgout(x,y)=media_alfarecortado(window,d);
                break;
            case 6:
                imgout(x,y)=maximo(window);
                break;
            case 7:
                imgout(x,y)=minimo(window);
                break;
            case 8:
                imgout(x,y)=equalize_local(window);
                break;
            case 9:
                imgout(x,y)=moda(window);
                break;
            case 10:
                imgout(x,y)=filtro_distancias(window);
                break;
            }

        }
    }

    imgout.crop(medio,medio,M-medio-1,N-medio-1);
    imgout.resize(M,N);
    return imgout;
}

//Wrapper para 3 canales RGB
template <class T>
CImg<T> denoiseRGB(CImg<T> img,int sizew,int tipofiltro,int Q=0,int d=0){
    CImg<double> imgR=denoise(img.get_channel(0),sizew,tipofiltro,Q,d);
    CImg<double> imgB=denoise(img.get_channel(1),sizew,tipofiltro,Q,d);
    CImg<double> imgG=denoise(img.get_channel(2),sizew,tipofiltro,Q,d);
    CImg<double> imgFiltrada;
    ComposeRGB(imgFiltrada,imgR,imgG,imgB);

    return imgFiltrada;
}


///****************************************
///TRANSFORMADA DE HOUGH
///****************************************
Pixel MaximoP( CImg<double>& img ) {
    int xmax=0, ymax=0;
    double maximo = img(0,0);
    cimg_forXY(img, i, j) {
        if( img(i,j) > maximo ) {
            maximo = img(i,j);
            xmax = i;
            ymax = j;
        }
    }
    return Pixel(xmax, ymax, &img);
}
Pixel MinimoP( CImg<double>& img ) {
    int xmin=0, ymin=0;
    double minimo = img(0,0);
    cimg_forXY(img, i, j) {
        if( img(i,j) < minimo ) {
            minimo = img(i,j);
            xmin = i;
            ymin = j;
        }
    }
    return Pixel(xmin, ymin, &img);
}
///INVERSA (modificada)
///se pasa una transformada y numero de lineas acumulado maximo
CImg<double> InversaHough(CImg<double> img, int nLineas) {
    const unsigned M = img.width(),N = img.height();
    CImg<double> iHough(M, N, 1, 1, 0.0);
    double maxRho = sqrt(float(pow(N-1,2)+pow(M-1,2))), stepRho = 2.*maxRho/(N-1), stepTheta = M_PI/(M-1), rho, theta;
    const double blanco[1] = {255.f};
    float x0, x1, y0, y1;
    for( int nl=0; nl < nLineas; nl++ ) {
        Pixel p = MaximoP( img );
        int t = p.x, r = p.y;
        theta=t*stepTheta-M_PI/2;
        rho=r*stepRho-maxRho;
        if (theta>-M_PI/2 && theta<M_PI/2){
            y0=0; y1=M-1;
            x0=rho/cos(theta);
            x1=rho/cos(theta)-(M-1)*tan(theta);
        }
        else {
            x0=0; x1=N-1;
            y0=rho/sin(theta);
            y1=rho/sin(theta)-(N-1)/tan(theta);
        }
        iHough.draw_line(y0,x0,y1,x1,blanco);
        img(t,r) = 0;
    }
    return iHough;
}
////para detectar circulos
template <class T>
CImg<T> HoughCirculos(CImg<T> &img, int r) {
    int M = img.width(), N = img.height();
    CImg<double> iHough(M, N, 1, 1, 0.0);
    cimg_forXY(img, i, j){
        if (img(i, j)) {
            for (int a=0; a<M; ++a){
                double det = r*r-(i-a)*(i-a);
                if (det>0){
                    double b=round(j-sqrt(det));
                    if (b>0 && b<N)
                        iHough(a,b)++;
                }
            }
        }
    }
    return iHough;
}



template <typename T>
CImg<T> splitHough(CImg<T> Hough,double angulo = -180, double row_hough = -1,int ang_tol = 0,int rho_tol = 0,bool just_max = false) {
    // Si le pasamos -180 (por defecto), me devuelve toda la columna (sin importar ang_tol)
    if (angulo == -180) {
        angulo = 0;
        // si es menor o igual a 0, no tiene sentido guardarlo
        ang_tol = Hough.width() / 2;
    }
    double col_hough = (angulo + 90) / 180 * Hough.width();
    if (row_hough == -1) {
        row_hough = Hough.height() / 2;
        rho_tol = Hough.height() / 2;
    }
    // Guardo el maximo pico
    double max_pico = 0;
    double x_max_pico = 0;
    double y_max_pico = 0;
    CImg<double> auxiliar(Hough.width(), Hough.height(), 1, 1, 0);
    for (int i = -ang_tol ; i <= ang_tol ; i++) {
        for (int j = -rho_tol ; j <= rho_tol ; j++) {
            if (col_hough + i < Hough.width() && col_hough + i >= 0 &&
                    row_hough + j < Hough.height()&& row_hough + j >= 0) {
                x_max_pico = col_hough + i;
                y_max_pico = row_hough + j;
                if (just_max) {
                    if (Hough(col_hough + i, row_hough + j) > max_pico) {
                        max_pico = Hough(x_max_pico, y_max_pico);
                    }
                } else {
                    if (Hough(x_max_pico, y_max_pico) > 0) {
                        auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
                        std::cout << auxiliar(x_max_pico, y_max_pico) << "(" << x_max_pico << "," << y_max_pico << ")"<< std::endl;
                    }
                }
            }
        }
    }
    if (just_max) {
        auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
    } else { // Aplico un umbral
        auxiliar.threshold(0.3 * auxiliar.mean() + 0.7 * auxiliar.max());
    }
    return auxiliar;
}


///  coordenada y al eje, me retorna el valor que correspende la transformada Hough en tita y rho
// en grados para tita (t) entre [-90 ; 90] y entre [-sqrt(2)M;sqrt(2)M] el rho (p)
template <typename T>
double coordenadaXY_a_rho_tita(CImg<T> hough, int coord, unsigned char axis) {
    unsigned int M = hough.width();
    unsigned int N = hough.height();
    // Maximos valores absolutos de theta y de rho
    double max_theta = 90;
    double max_rho = pow(pow(M, 2.0) + pow(N, 2.0), 0.5);
    double valor;
    if (axis == 't') { // tita
        valor = (2.0 * coord / M - 1.0) * max_theta;
    } else if (axis == 'p') { //rho
        valor = (2.0 * coord / N - 1.0) * max_rho;
    }
    return valor;
}




///****************************************
///CRECIMIENTO DE REGIONES
///****************************************

///unsigned char la hice en unsigned char por que la funcion que dieron los profesores esta asi
/// supongo que es suficiente??
///
/// podria ponerla dentro de   autom_seg_region_growed y listo.
template <class T>
CImg<T> wrapper_region_growed(CImg<T> img,int x,int y,int delta,int etiqueta,CImg<T>&region_crecida, CImg<T>& segmentacion) {
    cout<<"x_rand:"<<x<<"y_rand:"<<y<<endl;
    CImg<T> aux;
    aux = region_growing(img, x, y, delta, etiqueta); //aux 3 channel

    region_crecida = img - aux;
    CImg<double> compuesta(img.width(),img.height(),1,3,0);
    CImg<double> aux_flood=region_crecida.get_channel(0).normalize(0,1);
   // region_crecida.get_channel(0).display("flooddddddddd");
    //aca tengo que pintar cada nueva zona de un color distinto.
    compuesta.RGBtoHSI();
    int color=rand()%360;
    cimg_forXY(compuesta,i,j){
        if(region_crecida(i,j)!=0)
            compuesta(i,j,0,0)=color;//h
            compuesta(i,j,0,1)=1;//s
            compuesta(i,j,0,2)=aux_flood(i,j);//I

    }
    compuesta.HSItoRGB();
    segmentacion= compuesta+segmentacion;
           // (img, region_crecida, segmentacion).display("imagen, Region fooldd, Seleccion", 0);


        img -= region_crecida;

        return img;
}


/// segmentacion automatica con region_growed
template <class T>
CImg<T> autom_seg_region_growed(CImg<T> img, int delta, int etiqueta, const int max_segm) {
    //if(img.spectrum()!=1) img=img.get_RGBtoHSI().get_channel(2);
    CImg<T> img_auto(img);
    CImg<T> region_crecida;//(img.width(), img.height(), 1, 3,0);
    CImg<T> segmentacion(img.width(), img.height(), 1, 3,0);
    //segmentacion.fill(0);
    //region_crecida.fill(0);
    int x_rand, y_rand;
    int segmentaciones = 0;
    /* initialize ransegmentacionesdom seed: */
    srand(time(0));
    while (img_auto.max() > 0 && segmentaciones < max_segm) {
        x_rand = rand() % img_auto.width();
        y_rand = rand() % img_auto.height();
        if (img_auto(x_rand,y_rand) != 0) {    //semilla en x,y en cada pasada Tiene que ser distinta de cero tiene que ser distinto de cero
            img_auto = wrapper_region_growed(img_auto, x_rand, y_rand, delta, etiqueta, region_crecida, segmentacion);
            segmentaciones++;
            cout<<segmentaciones<<endl;
        }
    }
    return segmentacion;
}


///****************************************
///MORFOLOGIA
///****************************************

template <class T>
void apertura(CImg<T> &img,int ventana){
    img.erode(ventana);//Erosionamos
    img.dilate(ventana);//Dilatamos
}

template <class T>
CImg<T> extraccion_de_regiones(CImg<T> img,int ventana){
    return DifImg(img.get_dilate(ventana),img.get_erode(ventana));
}

template <class T>
CImg<T> relleno_automatico(CImg<T> img,int ventana){
    CImg<T> f(img.width(),img.height());
    CImg<T> bordes = extraccion_de_regiones(img,ventana);//son los bordes de la mascara

    cimg_forXY(img,i,j){
        if(img(i,j)== bordes(i,j)){
            f(i,j)=1.0-img(i,j);//si esta en el borde de la mascara
        }
        else
        {
            f(i,j)=0;
        }
    }
    //Dilato la f
    f.dilate(ventana);

    //Hago la interseccion
    return multiplicacion(f,negativo(img));
}


#endif // FUNCIONES

