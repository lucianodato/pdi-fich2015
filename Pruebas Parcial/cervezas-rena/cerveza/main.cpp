#include "funciones.h"

#define UMBRAL 240
#define INTENSIDAD_PROMEDIO 160.0
#define RADIO_SLICE 100
#define CANT_EROSION 15


//Este metodo identifica dos tipos rubia o negra. True si es rubia, false es negra o cualquier otra
template<typename T>
bool tipo_cerveza(CImg<T> img){

    double img_mean = img.RGBtoHSI().get_channel(2).get_normalize(0,255).mean();

    // Ahora determino si es rubia o negra, en base a intensidad promedio
    if (img_mean > INTENSIDAD_PROMEDIO) { // es rubia
        return true;
    } else { // es negra
        return false;
    }
}

int main()
{
    //imagen
    CImg<float> original,byn,procesada,copia,final;
    original.load("../../../../Parcial de Practica/Cervezas/training/13.jpg");
    procesada = original;
    copia = original;
    CImg<bool> mascara;

    //a)Encontrar la mascara del objeto.
    //1- mascara difusa, 2- escala de grises, 3 - binarizo con threadhold alto y obtengo el negativo (el fondo es blanco)
    procesada = transformacion3(procesada,generar_lut_logb((float)1));
    procesada = procesada.get_blur(3);
    byn =procesada.get_RGBtoHSI().channel(2).normalize(0,255);
    mascara = negativo(byn.get_threshold(UMBRAL));

    final = trim_image(original,mascara);
    //c)determinar tipo de cerveza (negra o rubia)

    if(tipo_cerveza(final)){
        cout<<"Cerveza Rubia!!"<<endl;
    }
    else{
        cout<<"Cerveza Negra!!"<<endl;
    }

    //d)Determino el porcentaje de espuma

    //Hago una mascara que me distinga la linea de la espuma
    //Hay que tener en cuenta que el porcentaje seria sin contar la parte de la base del vaso
    //por eso no seria teniendo en cuenta la altura de final.width()

    //Calculo el alto de la cerveza haciendo la mascara necesaria

    //Primero hago el promedio de una ventana centrada para obtener el color promedio de la cerveza
    int cent_x = final.width()/2;
    int cent_y = final.height()/2;
    CImg<float> color(1,1,1,3);
    color(0,0,0,0)=final.get_crop(cent_x-1,cent_y-1,cent_x+1,cent_y+1).channel(0).mean();
    color(0,0,0,1)=final.get_crop(cent_x-1,cent_y-1,cent_x+1,cent_y+1).channel(1).mean();
    color(0,0,0,2)=final.get_crop(cent_x-1,cent_y-1,cent_x+1,cent_y+1).channel(2).mean();

    //Genero la mascara
    mascara = ColorMaskRGB(final.get_blur(9),color,RADIO_SLICE).RGBtoHSI().channel(2).normalize(0,1).threshold(0.01);

    //Elimino los pequeños pixeles y reconstruyo a partir de la que tiene el borde
    mascara = apertura(mascara,mask(3));
    mascara = reconstruccion_dilatacion(mascara,nerode(mascara,mask(3),CANT_EROSION));
    mascara = relleno_automatico(mascara);

    //Cuento el alto de la cerveza en si
    int alto_cerveza=0;
    int alto_espuma=0;
    //Cuenta espuma
    cimg_forY(final,j){
        if(mascara(final.width()/2,j)==0){
            alto_espuma++;
        }else{
            break;
        }
    }
    //Cuenta cerveza
    cimg_forY(final,j){
        if(mascara(final.width()/2,j)==1){
            alto_cerveza++;
        }
    }

    (original,final,color,mascara).display();

    //Calculo el porcentaje de espuma
    cout<<"El porcentaje de espuma es: "<<alto_espuma*100/(alto_cerveza+alto_espuma)<<"%"<<endl;


    return 0;
}

