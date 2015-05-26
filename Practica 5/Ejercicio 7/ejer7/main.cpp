#include "funciones.h"

using namespace std;

//Parametros para el filtro Hap (Alta potencia) y Hpa (Enfasis de alta potencia)
int A = 2.25;
int alpha;
int b;

int main()
{
    CImg<double>img("../../../images/camaleon.tif");
    CImg<double>img_Hap,img_Heaf;
    CImgList<double>frec_Hap,frec_Heaf;

    //Obtengo alta potencia (Hap)
    //Con a=(A-1) y b=1 realizo un filtro de Alta Potencia
    alpha = A-1;
    b=1;
    img_Hap= filtroAP_frecuencia(img,alpha,b);


    //Obtengo enfasis en alta potencia (Heaf)
    //Con alpha=(A-1); b>1 y b>alpha realizo un filtro de Alta Potencia
    A=2.25;
    alpha = A-1;
    b=1.5;
    img_Heaf= filtroAP_frecuencia(img,alpha,b);

    CImgList<double> lista(img,img_Hap,img_Heaf);
    lista.display("Original - Alta Potencia (AP) - Enfasis de Alta Potencia (EAF)");

    frec_Hap= fourier(img_Hap);
    frec_Heaf= fourier(img_Heaf);

    //Muestro los resultados en frecuencia
    (frec_Hap[0],frec_Heaf[0]).display();

    return 0;
}
