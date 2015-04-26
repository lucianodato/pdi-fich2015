#include <funciones.h>

//Referencia de distancia de la imagen
//89 pixeles 200 metros
//1 pixel   -- x metros
//x=200/89=2,247191011 m
float areaPixel=(200/89)*(200/89);//area en metros cuadrados de cada pixel de imagen
int main()
{
    CImg<float> img,img_hsi,maskRGB,maskHSI,resultado,resultado2,imgOrig,kernel,kernel2,eqGlobal,diferencia,hist;
    CImgDisplay displayImagen, displayMascaraRGB, displayMascaraHSI;
    float radioHSI=50, radioRGB=20;
    unsigned mx, my;

    imgOrig.load("../../../../images/Deforestacion.png");
    img=imgOrig;
    img.crop(152,275,729,705); //recorte estilo bestia
    float areaTotal= (img.width()*img.height())*areaPixel;
    img_hsi = img.get_RGBtoHSI();
    CImg<float>lut(generar_lut_logb( 1));
    CImg<float>canal_I_realzado=transformacion(img_hsi.get_channel(2).get_normalize(0,255), lut);
    kernel=mask(17.0);
    kernel2.fill(0,0.2,0,0.2,0.2,0.2,0.2,0.2,0.2);
    CImg<float> pb=img_hsi.get_channel(2).get_normalize(0,255).get_convolve(kernel2);

    //Muestro el histograma--
    hist = img_hsi.get_channel(1).get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();//


    resultado=img_hsi.get_channel(2).normalize(0,255).get_convolve(mask(28)).get_convolve(mask(9)).get_convolve(mask(18)).get_convolve(mask(21)).get_threshold(160);
    //poner rojo en la zona
    float areaLimpia=0; //acumulo la cantidad de pixel que tiene el area desmontada marcada de rojo
    cimg_forXY(img_hsi,i,j){
        if(resultado(i,j)==1){
        img_hsi(i,j,0,0)=0.0;
        img_hsi(i,j,0,1)=1.0;
        areaLimpia+=areaPixel;
        }
    }


    CImgList<float> lista(img,img_hsi.get_channel(0),img_hsi.get_channel(1),img_hsi.get_channel(2),resultado,img_hsi.get_HSItoRGB());
    cout<<"Area Total "<< areaTotal*0.0001<<" hectareas - Area Limpia "<<areaLimpia*0.0001<<" hectareas " <<endl;
    lista.display("");

    return 0;
}

