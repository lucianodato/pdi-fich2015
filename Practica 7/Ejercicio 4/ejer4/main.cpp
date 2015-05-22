#include "funciones.h"
#define RADIO 15
#define UMBRAL 50
#define WINDOW 3
#define RADIO_CIRCULOS 30
int main()
{
    CImg<float> img,mascara,final,etiqueta,circulos;
    int mx,my;

    const char* path = "../../../../images/rosas.jpg";
    img.load(path);
    mascara.assign(img.width(),img.height(),1,1);

    //Color Slicing

    CImgDisplay v1(img,"Presione sobre el color deseado"),v2(img,"Resultado");

    while(!v1.is_closed() || !v2.is_closed()){
        v1.wait();
        if(v1.button()==1){

            mx=v1.mouse_x();
            my=v1.mouse_y();

            mascara = ColorMaskHSI(img,mx,my,RADIO);

            v2.render(mascara);
            v2.paint();
        }
    }

    //Proceso la mascara para dejarla binaria
    mascara.RGBtoHSI();
    mascara = mascara.get_channel(2).get_normalize(0,255);
    mascara.threshold(UMBRAL);

    //Estrategia para limpiar la mugre

    //Operacion 1 - Apertura
    apertura(mascara,WINDOW);

    //Operacion 2 - Relleno Automatico
    final = relleno_automatico(mascara,WINDOW);

    //Operacion 3 - Normalizado y correccion de numeros de la mascara
    final = negativo(final).get_normalize(0,1);

    //Operacion de etiquetado
    etiqueta = label_cc(final);

    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
    cout<<"La cantidad total de rosas es: "<<cant_rosas<<endl;

    //Dibujar un circulo rojo encima de cada rosa


    return 0;
}

