#include "funciones.h"

#define UMBRAL 243

int main()
{
    //imagen
    CImg<float> original,copia,copia2,aux,magnitud;
    CImgList<float> ff;
    original.load("1.jpg");
    CImg<bool> B(8,8),B2(3,3),mascara;
    B.fill(1);
    B2.fill(1);
    //Imagen en escala de grises
    //copia = negativo(original.RGBtoHSI().get_channel(2).get_normalize(0,255));
    copia = original;
    copia.display();
    //Mascara
    mascara = NOTimg(copia.get_RGBtoHSI().get_channel(2).get_normalize(0,255).threshold(230));
    mascara = apertura(mascara,mask(5));
    //Trimeo a lo cabeza de tacho
    copia2=original.get_mul(mascara);

    mascara = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    mascara.display();


    // Y me quedo con una region central para evitar ser afectado por bordes
    //copia.crop(copia.width()/5, copia.height()/5, copia.width()*4/5, copia.height()*4/5);
    //copia.display();
    mascara = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    mas
    // Y ahora aplicamos hough
    aux = hough(mascara);

    //buscamos el maximo pico
    double max_theta = 0;
    double max_rho_coord = 0;

    copia = get_max_peak<double>(aux, max_theta, max_rho_coord);

    // Ahora que se donde esta el maximo pico, se cual es su inclinacion, por lo que deberia
    // rotarlo hacia 90 o hacia 0, depende cual este mas cerca
    std::cout << max_theta << std::endl;

    // Si theta es negativo, tomo consideracion especial
    max_theta = (max_theta < 0) ? 180 + max_theta : max_theta;

    // Me va dar 0 (<45), 90 (< 135), 180 (< 225), 270 (<315), o 360
    double degree_to_go = round(max_theta / 90) * 90;

    // Y lo rotamos
    CImg<double> page_rotate(copia2.get_rotate(max_theta - degree_to_go));

    (original,aux.get_normalize(0,255),copia2.get_normalize(0,255),page_rotate,trim_image(page_rotate,page_rotate)).display();


    return 0;
}

