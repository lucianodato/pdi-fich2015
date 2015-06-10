#include "funciones.h"

#define UMBRAL 10

int main()
{
    //imagen
    CImg<float> original;
    original.load("../../../../Parcial de Practica/tenis/tenis01.jpg");

    //En primera instancia deberia detectar la linea de saque
    //Tengo en cuenta entonces solo la imagen de la mitad para abajo
    CImg<float> recorte = original.get_crop(0,original.height()*2/3,original.width(),original.height()).get_RGBtoHSI().channel(2).normalize(0,255);
    recorte = filtroAP(recorte,mask(3));
    CImg<bool> mascara = detectar_lineas_cond(recorte,UMBRAL,1,0,15);

    //Deduzco las dimensiones y coordenadas del cartel a partir de la deteccion de linea
    int posx=0,posy=0,ancho=0,alto=0;
    bool entro=false;
    for(int i = 0;i<mascara.width();i++){
        for(int j = 0;j<mascara.height();j++){
            if(mascara(i,j)==1 && entro == false){
                posx=i;
                posy=(original.height()*2/3)+j;
                ancho=original.width()-(2*i);
                alto=(original.height()-posy)/2;
                entro=true;
            }
        }
    }


    cout<<posx<<" "<<posy<<endl;

    //Dibujo el rectangulo sobre la cancha cuidando que no dibuje por encima de los bordes
    //Cartel
    CImg<bool> cartel(original.width(),original.height(),1,1,0);
    cartel.draw_rectangle(posx,posy,posx+ancho,posy+alto,white).normalize(0,1);
    //Bordes (es una combinacion de los bordes con sobel y un threshold de la imagen en greyscale)
    CImg<float> aux = original.get_RGBtoHSI().channel(2).normalize(0,255);
    CImg<bool> bordes = (Sobel(aux,0)+Sobel(aux,1)).threshold(UMBRAL).normalize(0,1)+negativo(aux.get_threshold(100)).normalize(0,1);
    bordes = apertura(bordes,mask(3));
    //bordes = relleno_automatico(bordes);
    //Interseccion
    CImg<bool> mascara_trans = ANDimg(cartel,bordes);
    //(cartel,bordes,mascara_trans).display();

    CImg<float> final(original);
    cartel= cartel.get_mul(NOTimg(mascara_trans));
    CImg<float> cartel2(original.width(),original.height(),1,3,0);
    cartel2.draw_rectangle(posx,posy,posx+ancho,posy+alto,red);
    final=final.get_mul(NOTimg(cartel))+cartel2.get_mul(cartel);

    (original,final).display();

    return 0;
}

