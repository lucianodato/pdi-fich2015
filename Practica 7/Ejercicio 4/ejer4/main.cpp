#include "funciones.h"
#define RADIO 15
#define UMBRAL 50
#define RADIO_CIRCULOS 30
int main()
{
    CImg<float> img,final;
    CImg<int> etiqueta;
    CImg<bool> mascara,vent(3,3);
    int mx,my;
    //vent.fill(0,1,0,1,1,1,0,1,0);
    vent.fill(1);
    const char* path = "../../../../images/rosas.jpg";
    img.load(path);
    mascara.assign(img.width(),img.height(),1,1);
    final.assign(img);
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
    //mascara.display("Color Slicing y Threshold");

    //Estrategia para limpiar la mugre

    //Operacion 1 - Erosion y dilatacion
    mascara = mascara.get_erode(vent);
    mascara = mascara.get_dilate(vent);
    mascara = mascara.get_dilate(vent);
    mascara = mascara.get_dilate(vent);
    //mascara.display("Erosion y Dilatacion");

    //Operacion de etiquetado
    etiqueta = label_cc(mascara);
    //etiqueta.display("Etiquetado");

    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
    vector<int> grises = grises_disponibles(etiqueta);
    cout<<"La cantidad total de rosas es: "<<cant_rosas<<endl;

    //Dibujar un circulo rojo encima de cada rosa
    //Armo la macara encontrando los centros de cada rosa y el diametro minimo en el cuadrado que la encierra
    CImg<float> masc(etiqueta.width(),etiqueta.height(),1,1,0);

    //Recorro el vector de grises
    for(int g=0;g<grises.size();g++){
        //Primero encuentro las coordenadas maximas y minimas
        int max_x=0,max_y=0,min_x=etiqueta.width(),min_y=etiqueta.height(),radio,centro_x,centro_y;
        cimg_forXY(etiqueta,i,j){
            if(etiqueta(i,j)==grises.at(g)){
                //Estoy en un pixel del gris buscado - actualizo los maximos y los minimos
                i>max_x ? max_x=i:max_x=max_x;
                j>max_y ? max_y=j:max_y=max_y;
                i<min_x ? min_x=i:min_x=min_x;
                j<min_y ? min_y=j:min_x=min_x;
            }
        }
        //Calculo el radio del circulo y el pixel medio
        radio=min((max_x-min_x),(max_y-min_y))-12;//El -12 es para achicar un poco los circulos (a ojo)
        centro_x=min_x + ((max_x-min_x)/2);
        centro_y=min_y + ((max_y-min_y)/2);
        //Creo una mascara a partir del ciculo
        masc.draw_circle(centro_x,centro_y,radio,white);
    }
    //masc.display("Mascara de circulos");

    //Pinto la imagen original con los circulos rojos (en realidad hago un balance de color con un aumento grande)
    final = balancecolorRGB(final,0,300).get_mul(masc) + final.get_mul(negativo(masc));

    final.display("Coloreando");
    return 0;
}

