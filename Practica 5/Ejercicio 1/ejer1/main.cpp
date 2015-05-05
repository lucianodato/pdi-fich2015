#include "funciones.h"

using namespace std;

int main()
{

    CImg<float> img,img_fft,img_hsi,mag;
    img.load("../../../../images/FFT2_Patrones.png");
    img_fft.load("../../../../images/FFT2_Activacion.png");

    img.display();

    //Consigna 1

    //Las imagenes son de 4 x 4 por lo tanto las transformadas tambien

    //La primera tiene una periodicidad a lo largo de y por lo tanto en la transformada se veria un palito en x

    //La segunda es una imagen plana sin alteraciones por lo tanto solo tendria la frecuencia 0 en 1

    //La tercera es tiene variaciones diagonales que parecen ser periodicad por lo tanto las frecuencias tendria diagonal espejada
    //con respecto a la original

    //La cuarta tiene perturbaciones de intensidad a lo largo de y entonces se verian en x en frecuencias

    CImgList<> lista(img,img_fft);
    lista.display();

    //La primera se corresponde con la segunda
    //La segunda con la primera
    //La tercera con la cuarta
    //La cuarta con la tercera



    return 0;
}

