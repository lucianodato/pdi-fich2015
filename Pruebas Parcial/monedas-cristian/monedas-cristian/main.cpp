#include "funciones.h"
#define RADIO 15
#define UMBRAL 253
#define RADIO_CIRCULOS 30
int main()
{
    CImg<float> img,img_intensidad,final;
    CImg<float> etiqueta;
    CImg<bool> mascara,se1(3,3);
    se1.fill(1);
    int mx,my;
    const char* path = "../../../../Parcial de Practica/Monedas/02_Monedas.jpg";
    img.load(path);
    //img.display("monedas");
    mascara.assign(img.width(),img.height(),1,1);
    //Proceso la mascara para dejarla binaria
    img_intensidad=img.get_RGBtoHSI().get_channel(2).get_normalize(0,255);
    mascara = NOTimg(img_intensidad.threshold(UMBRAL));
//     CImg<bool> recorte=mascara.get_crop(744,332,838,435);
//     recorte.display("recorte");
//     int contador=0;
//             cimg_forXY(recorte,i,j) {
//                if(recorte(i,j)==1){
//                    //Estoy en un pixel del gris buscado - actualizo  e incremento el contador de pixel en 1
//                    contador++; //cuento todos los pixeles que tienen ese nivel de gris particular
//                }
//            }
//     cout<<"contador"<<contador<<endl;


    (img,img_intensidad,mascara).display("");
    //Operacion de etiquetado
    etiqueta = label_cc(mascara);
    etiqueta.display("Etiquetado");

    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
    vector<int> grises = grises_disponibles(etiqueta);
    cout<<"La cantidad total de monedas es: "<<cant_rosas<<endl;
    vector<int> contadordepixeles;
    int contador=0;
    //Recorro el vector de grises disponibles y cuento cuantos pixel hay en cada posicion de gris
    for(int g=0;g<grises.size();g++){
        //Primero encuentro las coordenadas maximas y minimas
         cimg_forXY(etiqueta,i,j) {
            if(etiqueta(i,j)==grises.at(g)){
                //Estoy en un pixel del gris buscado - actualizo  e incremento el contador de pixel en 1
                contador++; //cuento todos los pixeles que tienen ese nivel de gris particular
            }
        }
        contadordepixeles.push_back(contador); //cuando recorri toda la imagen guardo el contador
        contador=0;
    }

    //sumar la cantidad de dinero
    float suma=0;
    for(int i=1;i<contadordepixeles.size();i++){
        if(contadordepixeles.at(i)>=3160 && contadordepixeles.at(i)<=3380) suma+=0.01;
        if(contadordepixeles.at(i)>=4150 && contadordepixeles.at(i)<=4360) suma+=0.02;
        if(contadordepixeles.at(i)>=5420 && contadordepixeles.at(i)<=5630) suma+=0.05;
        if(contadordepixeles.at(i)>=4600 && contadordepixeles.at(i)<=4820) suma+=0.1;
        if(contadordepixeles.at(i)>=5870 && contadordepixeles.at(i)<=6096) suma+=0.2;
        if(contadordepixeles.at(i)>=7020 && contadordepixeles.at(i)<=7240) suma+=0.5;
        if(contadordepixeles.at(i)>=6350 && contadordepixeles.at(i)<=6560) suma+=1;
        if(contadordepixeles.at(i)>=7770 && contadordepixeles.at(i)<=7996) suma+=2;

    }

    cout<<"La cantidad de dinero es "<<suma<<endl;

    //Chequeo las monedas
    CImgList<float> miedo = trim_image_wrapper(img,etiqueta);
    miedo.display("Monetaaaa!");

    return 0;
}

