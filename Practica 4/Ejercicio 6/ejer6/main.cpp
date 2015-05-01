#include <funciones.h>

//Referencia de distancia de la imagen
//89 pixeles 200 metros
//1 pixel   -- x metros
//x=200/89=2,247191011 m
float areaPixel=(200/89)*(200/89);//area en metros cuadrados de cada pixel de imagen
int main()
{
    CImg<float> img,img_hsi,img_hsi_p,maskRGB,maskHSI,resultado,resultado2,resultado0,resultado1,imgOrig,kernel,kernel2,eqGlobal,diferencia,hist;
    CImgDisplay displayImagen, displayMascaraRGB, displayMascaraHSI;
    float radioHSI=50, radioRGB=20;
    unsigned mx, my;

    imgOrig.load("../../../../images/Deforestacion.png");
    //img es la imagen auxiliar a procesar (RGB)
    img=imgOrig;
    //Recorte de la zona de interes
    img.crop(152,275,729,705); //recorte estilo bestia
    //Area total de la zona de interes
    float areaTotal= (img.width()*img.height())*areaPixel;
    //imagen auxiliar HSI
    img_hsi = img.get_RGBtoHSI();

    //Muestra el histograma del canal I de la HSI
    hist = img_hsi.get_channel(2).get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    //Procesamiento final donde se normaliza se filtra multiples veces y luego se aplica umbralado
    //Todos sobre el canal de intensidad

    //Primero normalizo
    resultado = img_hsi.get_channel(2).normalize(0,255);
    resultado.display("Canal I Normalizado");

    //Ecualizo el resultado
    resultado = resultado.get_equalize(256);
    resultado.display("Ecualizando");

    //Separo los grises medios claros de los grises medios oscuros
    resultado = transformacion(resultado,generar_lut_logb(float(1),0));
    resultado.display("Aplicando una lut");

    //Aplicacion de mascaras de promediado

    //Mascara para detalles grandes
    int pasadas = 10;
    for (int i = 0 ; i <=pasadas ; i++){
        resultado = resultado.get_convolve(mask(3));
    }
    //Mascara para detalles chico
    pasadas = 1;
    for (int i = 0 ; i <=pasadas ; i++){
        resultado = resultado.get_convolve(mask(9));
    }

    resultado.display("Canal I Fitrado");
    hist = resultado.get_histogram(256,0,255);
    hist.display_graph("Histograma Canal I Filtrado");

    //Aplico el umbralado
    resultado = resultado.get_threshold(170);

    //Muestro la mascara obtenida
    resultado.display("Mascara Final");

    //poner rojo en la zona
    float areaLimpia=0; //acumulo la cantidad de pixel que tiene el area desmontada marcada de rojo
    //Trabajo sobre una auxiliar
    img_hsi_p = img_hsi;
    cimg_forXYZ(img_hsi,i,j,k){
        if(resultado(i,j)==1){
        img_hsi_p(i,j,k,0)=0.0;
        img_hsi_p(i,j,k,1)=1.0;
        areaLimpia+=areaPixel;
        }
    }

    //Muestra los resultados de los calculas de Area (en hectareas)
    cout<<"Area Total "<< areaTotal*0.0001<<" hectareas - Area Limpia "<<areaLimpia*0.0001<<" hectareas " <<endl;

    //Carga los canales en una lista y muestra el resultado final
    CImgList<float> lista(img,img_hsi.get_channel(0),img_hsi.get_channel(1),img_hsi.get_channel(2),img_hsi_p.get_HSItoRGB());
    lista.display("Original - H - S - I - Imagen Final");

    return 0;
}

