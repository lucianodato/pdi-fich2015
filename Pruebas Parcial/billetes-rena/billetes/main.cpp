#include "funciones.h"

#define UMBRAL 235
#define RUTA "../../../../Parcial de Practica/Billetes/Billetes_Girados/1.jpg"


int main()
{
    //imagen
    CImg<float> original,billete,aux_hough;
    original.load(RUTA);
    CImg<bool> mascara;

    //Mascara
    mascara = NOTimg(original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).threshold(UMBRAL));
    mascara = apertura(mascara,mask(5));
    //Trimeo a lo cabeza de tacho para traerme el billete
    billete=original.get_mul(mascara);
    billete.display("Billete rotado");

    //Me quedo con el contorno de la mascara. Es la parte importante para calcular la inclinacion
    mascara = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    mascara.display("Mascara Contorno");

    // Y ahora aplicamos hough
    aux_hough = hough(mascara);

    //buscamos el maximo pico
    double max_theta = 0;
    double max_rho_coord = 0;

    get_max_peak<double>(aux_hough, max_theta, max_rho_coord);

    // Ahora que se donde esta el maximo pico, se cual es su inclinacion, por lo que deberia
    // rotarlo hacia 90 o hacia 0, depende cual este mas cerca
    std::cout << max_theta << std::endl;

    // Si theta es negativo, tomo consideracion especial
    max_theta = (max_theta < 0) ? 180 + max_theta : max_theta;

    // Me va dar 0 (<45), 90 (< 135), 180 (< 225), 270 (<315), o 360
    double degree_to_go = round(max_theta / 90) * 90;

    // Y lo rotamos
    CImg<double> billete_rotado(billete.get_rotate(max_theta - degree_to_go));

    //No me queda bien la imagen final, no me ocupa el total de las dimensiones del imagen
    //Calculo una nueva mascara y hago nuevamente un trim
    mascara = billete_rotado.get_RGBtoHSI().get_channel(2).get_normalize(0,255).threshold(50);
    //Hago una apertura para eliminar la basura alrededor de la mascara... no me sirve para cortar
    mascara = apertura(mascara,mask(5));
    mascara.display();
    billete_rotado = trim_image(billete_rotado,mascara);


    (original,aux_hough.get_normalize(0,255),billete,billete_rotado).display("Original - Hough - Billete - Billete rotado");


    return 0;
}

