#include "funciones.h"

int main()
{
    CImg <float> original,img,img_aux,img_aux2,img_res1,img_res2;
    const char* path = "../../../../images/corrientes.jpg";
    original.load(path);
    original = original.RGBtoHSI().get_channel(2).get_normalize(0,255);

    path = "../../../../images/corrientes_ruidogris.jpg";
    img.load(path);

    //Media Alfa Recortada d = la cantidad de pixeles de la ventana que puede recortar + mediana
    img_res1 = denoise(img,3,4);//Mediana
    img_res1 = denoise(img_res1,3,5,0,9);//Media alfarecortado
    //img_res1 = denoise(img,3,5,0,3);

    //Mediana y dsp punto medio. Bueno para mezcla de ruido impulsivo y gaussiano
    img_aux = denoise(img,3,3);//Mediana
    img_res2 = denoise(img_aux,3,4);//Media Punto Medio

    //1 paso - Restauracion. Imagen con ruido gaussiano o impulsivo
    original.display("Original");
    (img,img_res1,img_res2).display("Ruidosa - Restaurada(AlfaRecort) - Restaurada(MedianayPunMedio)");

    float A=2.25;
    float alpha = A-1;
    float b=4;
    img_aux = filtroAP_frecuencia(img_res1,alpha,b);

    //img_aux.display("Enfasis");
    //Paso 3 - Segmentacion (Sobel) y transformada de hough

    img_aux = Sobel(img_res2,1);
    img_aux = img_aux.erode(5);
    img_aux = img_aux.dilate(5);
    img_aux.display();

    //Paso 4 -



    return 0;
}
