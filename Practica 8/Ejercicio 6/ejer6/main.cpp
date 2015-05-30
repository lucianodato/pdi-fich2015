#include <funciones.h>
#define RADIO 10|
#define UMBRAL 50
#define RADIO_CIRCULOS 30

int main()
{
    //kernels
    CImg<bool> se1(3,3);
    se1.fill(1);   //  Structuring element 1


    CImg<float> original,img,resultado;
    CImg<int> etiqueta,final;
    CImg<bool> mascara,vent(3,3);
    int mx,my;
    vent.fill(1);
    const char* path = "../../../../images/Morfologia/Rio.jpeg";
    original.load(path);
    mascara.assign(img.width(),img.height(),1,1);
    //final.assign(img.width(),img.height(),1,3);
    //img = balancecolorRGB_condicional(original,2,300);
    //img = balancecolorRGB_condicional(original,2,300);
    img = original.RGBtoHSI().get_channel(2).get_normalize(0,255);
    //img = negativo(original.RGBtoHSI().get_channel(2).get_normalize(0,255));
    final = img.get_histogram(256,0,255);
    final.display_graph();


    //img = original;
    //mascara.fill(0);

    //(original,img).display();
    //Color Slicing

    //llamo a la mascara para los afluentes
    mascara = greyslicing(img,10);
    mascara.display();

    //CImgDisplay v1(img,"Presione sobre el color deseado"),v2(img,"Resultado");

    //while(!v1.is_closed() || !v2.is_closed()){
      //  v1.wait();
        //if(v1.button()==1){

          //  mx=v1.mouse_x();
           // my=v1.mouse_y();

            //mascara = greyslicing(img,RADIO);

      //      v2.render(greyslicing(img,RADIO));
       //     v2.paint();

        //}
   // }




    //Posproceso la mascara
//    mascara = mascara.RGBtoHSI().get_channel(2).get_threshold(UMBRAL);

//    mascara = apertura(mascara,se1).dilate(se1);

//    mascara.display();
//    mascara = extraccion_de_contornos(mascara,se1);
//    mascara.display();


    return 0;
}

