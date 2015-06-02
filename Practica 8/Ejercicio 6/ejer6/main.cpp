#include <funciones.h>
#define RADIO1 5
#define RADIO2 95
#define UMBRAL 127
#define AUMENTO -255
#define ALPHA 1.0
#define BETA 2.0

int main()
{
    //kernels
    CImg<bool> se1(3,3);
    se1.fill(1);   //  Structuring element 1


    CImg<double> original,copia,final;
    const char* path = "../../../../images/Morfologia/Rio.jpeg";
    original.load(path);
    copia=original;

    CImg<bool> mascara_rdlp(original.width(),original.height(),1,1),mascara_afl(original.width(),original.height(),1,1),mascara_afl1,mascara_afl2,vent1(3,3),vent(8,8);
    vent.fill(1);
    vent1.fill(1);

    //Visualizo el histograma del canal I para hallar el umbral optimo
    //original.get_RGBtoHSI().channel(2).normalize(0,255).histogram(256,0,255).display_graph();

    //Estrategia crear 2 mascaras una para el rio de la plata y otra para los afluentes

    //Mascara para el rio de la plata

//    mascara_rdlp= colourslicing(original,RADIO1);
//    mascara_rdlp.RGBtoHSI().channel(2).normalize(0,255).threshold(UMBRAL).normalize(0,1);
//    mascara_rdlp= apertura(mascara_rdlp,vent1);
//    mascara_rdlp.display();

    //Mascara para los afluentes


//    copia = denoiseRGB(copia,3,2);
//    copia=filtroAP3_frecuencia(copia,ALPHA,BETA);
//    mascara_afl=colourslicing(copia,RADIO2);
//    mascara_afl.RGBtoHSI().channel(2).normalize(0,255);
//    mascara_afl.threshold(UMBRAL).normalize(0,1);
//    mascara_afl1 = reconstruccion_dilatacion(mascara_afl,apertura(mascara_afl,vent));
//    mascara_afl2 = reconstruccion_dilatacion(mascara_afl,apertura(mascara_afl,vent));
//    mascara_afl = reconstruccion_dilatacion(mascara_afl2,mascara_afl1);

//    final = extraccion_de_contornos(mascara_afl,vent1);

//    (original.get_mul(final),final).display();

    //Hago la combinacion de ambas mascaras


    //Otro aprouch
    double A=2.25;
    double alpha = A-1;
    double b=1.5;

    copia = negativo(copia.RGBtoHSI().get_channel(2).get_normalize(0,255));
    copia = transformacion(copia,generar_lut_expb((double) 1.0,(double) 0.25));
    copia= filtroAP_frecuencia(copia,alpha,b);
    copia.display();
    mascara_afl = greyslicing(copia,150);

    mascara_afl = negativo(mascara_afl);
    mascara_afl.display();
    mascara_afl = componentes_conectadas(mascara_afl);
    mascara_afl.display();




    return 0;
}

