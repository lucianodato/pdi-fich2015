#include "funciones.h"

#define UMBRAL_SOBEL 50
#define UMBRAL_MASCARA 2
#define UMBRAL_CORTE 240
#define UMBRAL_ROMBO 140
#define RUTA "../../../../Parcial de Practica/Billetes/Billetes_Girados/1.jpg"
#define REF_VALUE  0.97

//GIRA BILLETE
//en funcion de la media chequeo como esta el billete, del derecho o del revez
template<typename T>
void enderezar_billete(CImg <T> &img){
    CImg <T>intensidad = img.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(180);
    //Pregunto si la dimension del ancho no es mas chica q el largo.
    //Si esto sucede, el objeto no fue rotado adecuadamente, quedo vertical
    if(img.width()<img.height()){
        //Tengo que rotar la mascara y la imagen 90 grados
        intensidad.rotate(90);
        img.rotate(90);
    }
    //Rota la imagen si corresponde
    double aux = intensidad.get_crop(53,84,161,227).mean();
    if (aux<REF_VALUE)
        img.rotate(180);
}

//VALOR BILLETE
//Determina en funcion de la cantidad de rombos el valor nominal del billete
template<typename T>
int valor_billete(CImg <T> img){

    img = img.get_RGBtoHSI().get_channel(2).get_normalize(0,255);

    //Hago un crop de la zona de interes (Se que estan son las coordenadas donde se ubican los rombos)
    img = img.get_crop(img.width()*0.2084,img.height()*0.0278,img.width()*0.29,img.height()*0.3585);
    //Desgasto con una mascara promedio por q es una imagen muy pixelada
    img = img.get_convolve(mask(5));

    //Calculo la mascara negativa con el valor de UMBRAL_ROMBO
    img = NOTimg(img.get_threshold(UMBRAL_ROMBO));
    //img.display("Mascara rombos");

    //Operacion de etiquetado (calculo cuantos objetos tengo en la mascara)
    CImg <T>etiqueta = label_cc(img);

    //Cuenta la cantidad de rombos (Contar niveles de grises diferentes)
    int cant_rombos = cant_grises(etiqueta);
    switch(cant_rombos){
    case 6:
        cout<<"2 PESOS";
        return 2;
    case 5:
        cout<<"5 PESOS";
        return 5;
    case 4:
        cout<<"10 PESOS";
        return 10;
    case 3:
        cout<<"20 PESOS";
        return 20;
    case 2:
        cout<<"50 PESOS";
        return 50;
    case 1:
        cout<<"100 PESOS";
        return 100;

    }
}

int main()
{
    //Variables auxiliares
    CImg<float> original,copia,billete,r,g,b;
    CImg<int> mascara;
    CImg<float>se0(3,3);
    double peso;

    //asignacion de variales
    original.load(RUTA);
    se0.fill(1);   //  Structuring element 1

    //Obtengo la Mascara del billete. Lo hago en RGB por que las componentes de intensidad en escala de grises entre
    //fondo y billete se confunden y me arman una mala mascara. Este proceso es mas caro pero efectivo

    copia = original.get_convolve(mask(5));

    r=copia.get_channel(0);
    g=copia.get_channel(1);
    b=copia.get_channel(2);
    //lleno inicialmente la mascara de unos..
    //voy a buscar los blancos mas blancos y hacerlos ceros
    mascara = original.get_RGBtoHSI().get_channel(2).fill(1);
    cimg_forXY(copia,i,j){
        if(r(i,j)>=UMBRAL_CORTE && g(i,j)>=UMBRAL_CORTE && b(i,j)>=UMBRAL_CORTE){
            mascara(i,j) = 0;
        }
    }

    mascara = mascara.erode(7).dilate(7);

    //Morfologia - Arreglo la mascara
    mascara = apertura(mascara,se0);

    //Arreglo la imagen para pasarsela a rotate_image
    copia = trim_image(original,mascara);

    //Roto el billete (sobel,hough y trim_image)
    billete = rotate_image(copia,UMBRAL_SOBEL,UMBRAL_MASCARA,true,true); /*bandera true si hay q chequear si es horizontal*/
    billete.display("Billete Rotado resp. al Eje theta");

    //Verifico si el billete esta del derecho o del revez. Roto si corresponde
    enderezar_billete(billete);
    billete.display("Billete enderezado");

    //Determino la denominacion del billete
    peso = valor_billete(billete);

    (original,billete).display("Original - Billete");

    return 0;

}




//    //Aplico un denoise previo
//    //original=denoise(original,3,12,0,4);/*

//    //Obtengo la Mascara del billete. Lo hago en RGB por que las componentes de intensidad en escala de grises entre
//    //fondo y billete se confunden y me arman una mala mascara. Este proceso es mas caro pero efectivo
//    r=original.get_channel(0);
//    g=original.get_channel(1);
//    b=original.get_channel(2);
//    //lleno inicialmente la mascara de unos..
//    //voy a buscar los blancos mas blancos y hacerlos ceros
//    mascara = original.get_RGBtoHSI().get_channel(2).fill(1);
//    cimg_forXY(original,i,j){
//        if(r(i,j)>=UMBRAL && g(i,j)>=UMBRAL && b(i,j)>=UMBRAL){
//            mascara(i,j) = 0;
//        }
//    }

//mascara = NOTimg(original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).threshold(UMBRAL));

//    //Mejoro la mascara con tecnica de apertura y relleno automatico
//    mascara = apertura(mascara,mask(5));
//    mascara=relleno_automatico(mascara);

//    //Trimeo a lo cabeza de tacho para traerme el billete
//    billete=original.get_mul(mascara);
//    billete.display("Billete rotado");

//    //Me quedo con el contorno de la mascara. Es la parte importante para calcular la inclinacion
//    mascara = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
//    mascara.display("Mascara Contorno");

//    // Y ahora aplicamos hough
//    aux_hough = hough(mascara);

//    //buscamos el maximo pico
//    double max_theta = 0;
//    double max_rho_coord = 0;

//    get_max_peak<double>(aux_hough, max_theta, max_rho_coord);

//    // Ahora que se donde esta el maximo pico, se cual es su inclinacion, por lo que deberia
//    // rotarlo hacia 90 o hacia 0, depende cual este mas cerca
//    //std::cout << max_theta << std::endl;

//    // Si theta es negativo, tomo consideracion especial
//    max_theta = (max_theta < 0) ? 180 + max_theta : max_theta;

//    // Me va dar 0 (<45), 90 (< 135), 180 (< 225), 270 (<315), o 360
//    double degree_to_go = round(max_theta / 90) * 90;

//    // Y lo rotamos
//    CImg<double> billete_rotado(billete.get_rotate(max_theta - degree_to_go));

//    //No me queda bien la imagen final, no me ocupa el total de las dimensiones del imagen
//    //Calculo una nueva mascara y hago nuevamente un trim
//    mascara = billete_rotado.get_RGBtoHSI().get_channel(2).get_normalize(0,255).threshold(50);
//    //Hago una apertura para eliminar la basura alrededor de la mascara... no me sirve para cortar
//    //Mejoro la mascara con tecnica de apertura y relleno automatico
//    mascara = apertura(mascara,mask(5));
//    //mascara=relleno_automatico(mascara);
//    //mascara.display();

//    //Recordo nuevamente el billete pero esta ves con la mascara derecha
//    billete_rotado = trim_image(billete_rotado,mascara);
