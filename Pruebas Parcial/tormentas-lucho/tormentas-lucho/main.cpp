#include "funciones.h"

#define UMBRAL_MASC 1
#define CENTRO_COLOR_ESCALA 32
#define COORD_MAX_DBZ 32
#define RADIO_CS 75

int main()
{
    //imagen
    CImg<float> original;
    original.load("../../../../Parcial de Practica/tormentas/4.png");

    //Guardo el color que esta centrado entre 48 y 68 para hacer color slicing
    CImg<float> maxdbz(1,1,1,3);

    maxdbz(0,0,0,0) = original(461,COORD_MAX_DBZ,0,0);
    maxdbz(0,0,0,1) = original(461,COORD_MAX_DBZ,0,1);
    maxdbz(0,0,0,2) = original(461,COORD_MAX_DBZ,0,2);

    //maxdbz.display();

    //Hago Colour Slicing
    CImg<float> img_cs = ColorMaskHSI(original,maxdbz,RADIO_CS);

    //Creo mascara para aislar el circulo central (Me va a servir para sacar el area afectada)
    CImg<bool> mascara = img_cs.get_RGBtoHSI().channel(2).normalize(0,255).threshold(UMBRAL_MASC);
    mascara = apertura(mascara,mask(3));
    //Deberia quedarme con la parte que esta dentro del circulo para contar el area
    mascara.crop(0,0,439,original.height());
    //Cuento la cantidad de pixeles blancos
    int area = 0;
    cimg_forXY(mascara,i,j){
        if(mascara(i,j)==1)
            area++;
    }

    //Identifico el pixel con mayor dbZ
    int pix_x=0,pix_y=0;
    int cont = 0;
    CImg<float> aux = img_cs.get_crop(0,0,439,original.height());
    CImg<float> maxdbz_act = maxdbz;
    while(pix_x ==0 && pix_y == 0){
        cimg_forXY(aux,i,j){
            if(aux(i,j,0,0)==maxdbz_act(0,0,0,0) && aux(i,j,0,1)==maxdbz_act(0,0,0,1) && aux(i,j,0,2)==maxdbz_act(0,0,0,2)){
                pix_x=i;
                pix_y=j;
            }
        }
        cont++;
        //Si no encontro el color avanzo de color
        maxdbz_act(0,0,0,0) = img_cs(461,COORD_MAX_DBZ+cont,0,0);
        maxdbz_act(0,0,0,1) = img_cs(461,COORD_MAX_DBZ+cont,0,1);
        maxdbz_act(0,0,0,2) = img_cs(461,COORD_MAX_DBZ+cont,0,2);
    }


    //Pinto el pixel sobre la imagen
    CImg<float> orig_pix(original);
    orig_pix.draw_circle(pix_x,pix_y,5,red);

    //Calculo de latitud y longitud del punto maximo
    float latitud=0,longitud=0;
    //Centro aproximado del circulo (a ojo!)
    int cent_x = original.width()/2-23;
    int cent_y = original.height()/2-7;
    //orig_pix.draw_circle(cent_x,cent_y,170,green);
    if(cent_x>pix_x){
        longitud = -60.5 - (fabs(cent_x-pix_x)*fabs(-61.9+60.5)/170);
    }else{
        longitud = -60.5 + (fabs(cent_x-pix_x)*fabs(-61.9+60.5)/170);
    }
    if(cent_y>pix_y){
        latitud = -31.8 + (fabs(cent_y-pix_y)*fabs(-32.9+31.8)/170);
    }else{
        latitud = -31.8 - (fabs(cent_y-pix_y)*fabs(-32.9+31.8)/170);
    }

    //Muestro
    cout<<"Extension: "<<area*0.5<<" km2 / "<<"Maximo dbZ: "<<68-cont<<" / Latitud: "<<latitud<<" / Longitud: "<<longitud<<endl;
    (img_cs,mascara,orig_pix).display();


    return 0;
}

