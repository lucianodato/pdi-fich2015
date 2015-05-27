#include "funciones.h"

int main()
{
    CImg <float> original,img,img_aux,img_res1,img_res2,seleccion,bordes;
    const char* path = "../../../../images/iguazu.jpg";
    original.load(path);
    original = original.RGBtoHSI().get_channel(2).get_normalize(0,255);

    path = "../../../../images/iguazu_ruidogris.jpg";
    img.load(path);

    //1 paso - Restauracion. Imagen con ruido gaussiano o impulsivo

    //Media Alfa Recortada d = la cantidad de pixeles de la ventana que puede recortar
    img_res1 = denoise(img,3,5,-1,2);//media armonica y d=2
    //Mediana y dsp punto medio. Bueno para mezcla de ruido impulsivo y gaussiano
    img_aux = denoise(img,3,3);//Mediana
    img_res2 = denoise(img_aux,3,4);//Media Punto Medio

    //original.display("Original");
    (img,img_res1,img_res2).display("Ruidosa - Restaurada(AlfaRecort) - Restaurada(MedianayPunMedio)");

    //Aqui trataria de enmascarar la pista para poder realzar solo la parte de la pista
    //Podria ser umbralado
    //seleccion = greyslicing(img_res1,25);
    //seleccion.display("Seleccion");

    //Enfasis de alta frecuencia
    //float A=2.25;
    //float alpha = A-1;
    //float b=4;
    //img_aux = filtroAP_frecuencia(img_res1,alpha,b);
    //img_aux.display("Enfasis");

    //Paso 3 - Segmentacion (Sobel) y transformada de hough
    bordes = LoG(img_res1);
    img_aux = laplaciano();
    bordes.display("Bordes");



    //Paso 4 -


    return 0;
}
