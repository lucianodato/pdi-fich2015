#ifndef PROCESAR_BOTELLAS
#define PROCESAR_BOTELLAS


#include <CImg.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "pasar_binario.h"

using namespace cimg_library;
using namespace std;


const unsigned char negro[] = { 0,0,0 };
const unsigned char blanco[] = { 255,255,255 };


struct dbotella{
    int ce;
    int cs;
    float porcentaje;
};

CImg<unsigned char>  recortar_botella(CImg<unsigned char> original,int ini_corte, int fin_corte,int nivel_seleccionado){

    return original.get_crop(ini_corte,nivel_seleccionado,fin_corte,original.height());

}

float calcular_porcentaje(CImg<unsigned char> *botella){

    int x = floor(botella->width()/2.0);
    float nivel = botella->height();
    for (int i=0;i<botella->height();i++){
        if( (int)*botella->data(x,i,0,0) <= 180.0 ){
            nivel = botella->height() - i;
            break;
        }
    }
    //    cout<<"Nivel "<<nivel<<endl;

    return (nivel*100.0/botella->height());

}

CImg<unsigned char> procesar_botellas(CImg<unsigned char> original,int umbral_de_evaluacion,int nivel_seleccionado)
{
    CImg<unsigned char> detectada(original);
    int columna_ce,columna_ct;
    //Datos de botellas
    vector<dbotella> datos;


    //Hay que tener cuidado con los extremos negro o blanco porque las columnas borde de las botellas son grises
    for(int i=0;i<original.width();i++){//imagen
        if ((int)*original.data(i,umbral_de_evaluacion,0,0) != 0 && (int)*original.data(i,umbral_de_evaluacion,0,0) < 255){

            columna_ce = i;
            int j=i;

            while((int)*original.data(j,umbral_de_evaluacion,0,0) != 0 && (int)*original.data(j,umbral_de_evaluacion,0,0) < 255)//botella
            {
                columna_ct = j;
                j++;
            }

            CImg<unsigned char> botella = recortar_botella(original,columna_ce,columna_ct,nivel_seleccionado);

            dbotella aux = {columna_ce,columna_ct,calcular_porcentaje(&botella)};
            datos.push_back(aux);

            //Actualizo el indice de recorrida global
            i=columna_ct;

        }
    }

//    //Muestro Datos
//    for(int i = 0; i < datos.size() ; i++){
//        cout<<"Botella "<<i<<endl;
//        cout<<"CE "<<datos[i].ce<<endl;
//        cout<<"CS "<<datos[i].cs<<endl;
//        cout<<"Porcentaje "<<datos[i].porcentaje<<endl;
//    }

    //Generar la modificada
    for (int i = 0;i<datos.size();i++)
    {
        if(datos[i].porcentaje < 95.0) {
            //Dibujamos un recuadro y el procentaje
            detectada.draw_rectangle(datos[i].ce,0,datos[i].cs,original.height(),blanco,0.5);
            //int posx = datos[i].cs - 2*floor((datos[i].cs-datos[i].ce)/3.0);
            int posx = datos[i].ce + 5;
            int posy = floor(original.height()*0.5);
            char porc[120];
            sprintf(porc,"%f",datos[i].porcentaje);
            detectada.draw_text(posx,posy,porc,blanco,negro,1,13);
        }
    }

    return detectada;

}



#endif // PROCESAR_BOTELLAS

