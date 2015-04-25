#include <funciones.h>
int main()
{
    CImg<float> img,img_hsi,maskRGB,maskHSI,resultado,resultado2,kernel,kernel2,eqGlobal,diferencia;
    CImgDisplay displayImagen, displayMascaraRGB, displayMascaraHSI;
    float radioHSI=50, radioRGB=20;
    unsigned mx, my;

    img.load("../../../../images/Deforestacion.png");
    img.crop(152,275,729,705); //recorte estilo bestia
    img_hsi = img.get_RGBtoHSI();
    CImg<float>lut(generar_lut_logb( 1));
    CImg<float>canal_I_realzado=transformacion(img_hsi.get_channel(2).get_normalize(0,255), lut);
    kernel=mask(17.0);
    kernel2.fill(0,0.2,0,0.2,0.2,0.2,0.2,0.2,0.2);
    CImg<float> pb=img_hsi.get_channel(2).get_normalize(0,255).get_convolve(kernel2);

    resultado=img_hsi.get_channel(2).normalize(0,255).get_convolve(mask(28)).get_convolve(mask(9)).get_convolve(mask(18)).get_convolve(mask(21)).get_threshold(160);
    //poner rojo en la zona
    cimg_forXY(img_hsi,i,j){
        if(resultado(i,j)==1)
        img_hsi(i,j,0,0)=0.0;
    }

    CImgList<float> lista(img,resultado,img_hsi.get_HSItoRGB());
    lista.display();

    return 0;
}

