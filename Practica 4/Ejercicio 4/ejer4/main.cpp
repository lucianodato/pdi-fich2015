#include <funciones.h>

int main()
{
    const char* path1 = "../../../../images/chairs_oscura.jpg";
    const char* path2 = "../../../../images/camino.tif";
    CImg<float> img1,img2,hist1,hist2;
    img1.load(path1);
    img2.load(path2);

    //Muestro el histograma
    hist1 = img1.get_histogram(256,0,255);
    hist2 = img2.get_histogram(256,0,255);
    //hist1.display_graph();
    //hist2.display_graph();

//    /// Consigna 1

//    CImg<float> ec_rgb,ec_hsi;

//    //Ecualizacion en RGB
//    ec_rgb = img1.get_equalize(256,0,255);

//    //Ecualizacion en HSI (solo se ecualiza el canal intensidad segun el Gonzales)
//    ec_hsi = img1.get_RGBtoHSI();
//    ec_hsi = ec_hsi.get_equalize(256,0,255);

//    //Faltaria probar ecualizando solo el canal Intensidad
//    CImgList<float> lista1(img1,ec_rgb,ec_hsi.get_HSItoRGB());
//    lista1.display("Original - Ecualizacion RGB - Ecualizacion HSI");

    /// Consigna 2

    CImg<float> ap_rgb,ap_hsi;

    //Aplico alta potencia en RGB
    ap_rgb = filtroAP(img2);

    //Aplico alta potencia en HSI
    ap_hsi = img2.get_RGBtoHSI();
    ap_hsi = filtroAP(ap_hsi);

    CImgList<float> lista2(img2,ap_rgb,ap_hsi);
    lista2.display("Original - Ecualizacion RGB - Ecualizacion HSI");

    return 0;
}

