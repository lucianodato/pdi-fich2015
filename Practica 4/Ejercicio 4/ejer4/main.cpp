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

    /// Consigna 1

    CImg<float> ec_rgb,ec_hsi,ec_hsi_i;

    //Ecualizacion en RGB
    ec_rgb = img1.get_equalize(256,0,255);

    //Ecualizacion en HSI (todos los canales)
    //ec_hsi = img1.get_RGBtoHSI();
    //ec_hsi = ec_hsi.get_equalize(256,0,255);

    //Ecualizacion en HSI (solo el canal de intensidad)
    ec_hsi = img1.get_RGBtoHSI();
    //Guardo el canal intensidad
    ec_hsi_i = ec_hsi.get_channel(2);
    //Ecualizo el canal intensidad
    ec_hsi_i = ec_hsi_i.get_equalize(256);

    //Reemplazo el canal intensidad de la original por el ecualizado
    cimg_forXYZ(ec_hsi,i,j,k)
            ec_hsi(i,j,k,2) = ec_hsi_i(i,j,k,0);

    CImgList<float> lista1(img1,ec_rgb,ec_hsi.get_HSItoRGB());
    lista1.display("Original - Ecualizacion RGB - Ecualizacion HSI");

    /// Consigna 2

    CImg<float> ap_rgb,ap_hsi,ap_hsi_i;

    //Creo el kernel de filtrado
    CImg<float> kernel(mask(5));
    float amp = 0.5;

    //Aplico alta potencia en RGB
    ap_rgb = filtroAP3(img2,kernel,amp);

    //Aplico alta potencia en HSI (en todos los canales)
    //ap_hsi = img2.get_RGBtoHSI();
    //ap_hsi = filtroAP3(ap_hsi);

    //Aplico alta potencia en HSI (en el canal intensidad)
    ap_hsi = img2.get_RGBtoHSI();
    ap_hsi_i = filtroAP(ap_hsi.get_channel(2),kernel,amp);

    //Reemplazo el canal intensidad de la original por el ecualizado
    cimg_forXYZ(ap_hsi,i,j,k)
            ap_hsi(i,j,k,2) = ap_hsi_i(i,j,k,0);

    CImgList<float> lista2(img2,ap_rgb,ap_hsi.get_HSItoRGB());
    lista2.display("Original - Alta potencia RGB - Alta potencia HSI");

    return 0;
}

