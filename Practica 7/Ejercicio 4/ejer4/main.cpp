#include "funciones.h"
#define RADIO 5
#define UMBRAL 50
#define WINDOW 3

int main()
{
    CImg<float> img,mascara,f,final;
    int mx,my;

    const char* path = "../../../../images/rosas.jpg";
    img.load(path);
    f.assign(img.width(),img.height(),1,1);
    //f.fill(0);

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

    //proceso la mascara para dejarla binaria
    mascara.RGBtoHSI();
    mascara = mascara.get_channel(2).get_normalize(0,255);
    mascara.threshold(UMBRAL);

    //Estrategia para limpiar la mugre

    //Operacion 1 - Apertura
    mascara.erode(WINDOW);//Erosionamos
    mascara.dilate(WINDOW);//Dilatamos

    //Operacion 2 - Relleno Automatico
    //Armamos el f
    cimg_forXY(mascara,i,j){
        if(mascara(i,j)!=0){
            f(i,j)=1-mascara(i,j);
        }
        else
        {
            f(i,j)=0;
        }
    }
    f.display();
    //armamos la negativa
    CImg<float>negativa = negativo(mascara);

    //Dilato la f
    f.dilate(WINDOW);

    //Hago la interseccion
    final= DifImg(f,negativa);


    final.display();

    return 0;
}

