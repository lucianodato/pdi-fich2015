#include "funciones.h"

int main()
{
    //imagen
    CImg<float> original;
    original.load("../../../../images/Morfologia/Cuerpos.jpg");

    //Calculo los esqueletos con Hamilton-Jacobi
    const int median = 1;
    const bool invert = true;
    const float thresh = -0.5f;
    const bool curve = true;
    const bool correction = true;
    const float dlt1 = 2;
    const float dlt2 = 1.0f;

    //Tengo que usar la imagen original pero guardar una version binaria
    CImg<unsigned int> mascara = original.get_norm().quantize(2).normalize(0.0f,1.0f);
    if (median) mascara.blur_median(median);
    if (invert) (mascara-=1)*=-1;

    //Calculo el mapa de distancia
    CImg<float> distance = mascara.get_distance(0);

    //Calculo el gradiente de la funcion y el flujo o divergencia del gradiente
    const CImgList<float> grad = distance.get_gradient("xyz");
    CImg<float> flux = mascara.get_flux(grad,1,1);

    //Uso la correccion de Torsello del flujo si es necesaria
    if (correction) {
        CImg<float>
                logdensity = mascara.get_logdensity(distance,grad,flux,dlt1),
                nflux = mascara.get_corrected_flux(logdensity,grad,flux,dlt2);
        flux = nflux;
    }

    //Calculo el esqueleto
    const CImg<unsigned int> skel = mascara.get_skeleton(flux,distance,curve,thresh);

    (original,mascara,skel).display();


    return 0;
}

