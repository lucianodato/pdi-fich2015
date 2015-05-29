#include <funciones.h>
#define RADIO 70
#define UMBRAL 50
#define RADIO_CIRCULOS 30

int main()
{
    //kernels
    CImg<bool> se1(3,3);
    se1.fill(1);   //  Structuring element 1


    CImg<float> img,final;
    CImg<int> etiqueta;
    CImg<bool> mascara,vent(3,3);
    int mx,my;
    vent.fill(1);
    const char* path = "../../../../images/Morfologia/Rio.jpeg";
    img.load(path);
    mascara.assign(img.width(),img.height(),1,1);
    final.assign(img);
    //Color Slicing

    CImgDisplay v1(img,"Presione sobre el color deseado"),v2(img,"Resultado");

    while(!v1.is_closed() || !v2.is_closed()){
        v1.wait();
        if(v1.button()==1){

            mx=v1.mouse_x();
            my=v1.mouse_y();

            mascara = ColorMaskHSI(img,mx,my,RADIO);

            v2.render(mascara);
            v2.paint();
        }
    }

    //Posproceso la mascara
    mascara = mascara.RGBtoHSI().get_channel(2).get_threshold(UMBRAL);

    mascara = apertura(mascara,se1).dilate(se1);
    mascara.display();
    mascara = extraccion_de_contornos(mascara,se1);
    mascara.display();

}

