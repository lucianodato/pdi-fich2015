#include "funciones.h"

#define UMBRAL 240
#define INTENSIDAD_PROMEDIO 128.0


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
    original.load("../../../../Parcial de Practica/Cervezas/training/02.jpg");
    procesada = original;
    copia = original;
    CImg<bool> B(8,8),B2(3,3),mascara;
    B.fill(1);
    B2.fill(1);

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
    CImg<float> cerveza = ColorMaskHSI(final,color,10).RGBtoHSI().channel(2).normalize(0,255).threshold(10);

    //Elimino los pequeños pixeles y reconstruyo a partir de la que tiene el borde
    cerveza = apertura(cerveza,mask(3));
    cerveza = reconstruccion_dilatacion(cerveza,nerode(cerveza,mask(3),15));
    cerveza = relleno_automatico(cerveza);

    //Cuento el alto de la cerveza en si
    int alto_cerveza=0;
    cimg_forY(final,j){
        if(cerveza(final.width()/2,j)==1){
            alto_cerveza++;
        }
    }

    //Calculo el alto de la espuma haciendo la mascara necesario
    CImg<bool> espuma = (Sobel(final,0) + Sobel(final,1)).get_RGBtoHSI().channel(2).normalize(0,255).threshold(10);

    //Elimino los pequeños pixeles y reconstruyo a partir de la que tiene el borde
    espuma = apertura(espuma,mask(3));
    espuma = reconstruccion_dilatacion(espuma,nerode(espuma,mask(3),5));
    espuma = relleno_automatico(espuma);

    //La parte de la cerveza en blanco

    //Recorro la mascara desde arriba para abajo y almaceno la cantidad de pixeles
    int alto_espuma = 0;
    cimg_forY(final,j){
        if(espuma(final.width()/2,j)==0){
            alto_espuma++;
        }else{
            break;
        }
    }

    //Calculo el porcentaje de espuma
    cout<<"El porcentaje de espuma es: "<<alto_espuma*100/(alto_cerveza+alto_espuma)<<"%"<<endl;


    return 0;
}

