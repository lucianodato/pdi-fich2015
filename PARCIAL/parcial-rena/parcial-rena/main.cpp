#include "funciones.h"

#define PATH "../../../Imagenes Parcial/parking6.png"
#define COLOR 113
#define RADIO 5
#define PARKING 40

template<class T>
CImg<T> buscar_parking(CImg<T>img,bool &estaciona){

    CImg<T> estacionamiento;
    CImg<bool> mascara,mascara_copia;
    estaciona = true;

    //Busco el color promedio de las lineas y del estacionamiento
    estacionamiento = img.get_crop(285,17,293,20);

    //Busco por colorslicingRBG
    estacionamiento = ColorMaskHSI(img,estacionamiento,RADIO);

    estacionamiento.display();

    //Calulo la mascara pasando a grises y aplico morfologia
    mascara = estacionamiento.RGBtoHSI().get_channel(2).get_normalize(0,255);
    mascara = mascara.threshold(128);
    //mascara.display();

    //Morfologia
    mascara_copia = mascara.erode(9).dilate(9);
    mascara = reconstruccion_dilatacion(mascara,mascara_copia);
    mascara.display();

    //Ahora bien, tengo la mascara del estacionamiento. Me fijo si hay o no un auto estacionado
    //Recordo de la imagen original junto con la mascara para verificar
    estacionamiento = trim_image(img,mascara);
    estacionamiento.display();

    //Pregunto la media de la imagen recortada para saber si hay mas negro q amarillo
    //Si hay mas negro el estacinamiento esta ocupado
     if(estacionamiento.mean()<PARKING){
         estaciona =false;
     }

    //Calculo el centro de la imagen que color tiene (cuadrado de 20x20)
    //CImg<T> color = estacionamiento.get_crop((img.width()/2)-30,(img.height()/2)-30,(img.width()/2)+30,(img.height()/2)+30);
    //color.display();
    //std::cout<<estacionamiento.mean();

    return mascara;
}


int main()
{
    //Carga de imagen a procesar
    CImg<float> original,vehiculo,copia,trayectoria;
    CImg<bool> mascara_parking,mascara_lineas;
    CImg<int>mascara_vehiculo;
    bool estaciona;
    original.load(PATH);
    original.display();

    //Me traigo la mascara de la funcion
    mascara_parking = buscar_parking(original,estaciona);
    //mascara_parking.display();
    //Pregunto si el estacinamiento esta libre o ocupado
    if(!estaciona){
        std::cout<<"Estacionamiento ocupado";;
    }
    else
    {
        std::cout<<"Estacionamiento libre";

        //Puedo buscar la trajectoria-----

        //a) Obtengo el lugar donde existe estacionamiento. Busco la trayectoria a seguir
        copia = original.get_mul(mascara_parking);
        copia = copia.RGBtoHSI().get_channel(2).get_normalize(0,255);
        //copia.display();

        //Sobel para deteccion de bordes
        mascara_lineas = Sobel(copia,0)+Sobel(copia,1);
        mascara_lineas.threshold(128);
        mascara_lineas.display();

        //CImg<int>ee(3,3);
        //ee.fill(0);
        //mascara_lineas = extraccion_de_contornos(mascara_parking,ee);
        //mascara_lineas.display();

        CImg<double> Hough = hough(mascara_lineas);
        Hough.display("hough");
        CImg<double> linea = InversaHough(Hough,2);
        //linea.display();
        //linea.rotate(90);

        //Guardo las lineas del estacionamiento
        trayectoria=linea;

        //busco la trayectoria del auto

        //Para buscar el auto
        //color de la linea RGB:208,109,161
        mascara_vehiculo=original;
        mascara_vehiculo.fill(0);

        CImg<float>r,g,b;
        r=original.get_channel(0);
        g=original.get_channel(1);
        b=original.get_channel(2);
        cimg_forXY(original,i,j){
            if(r(i,j)==208 && g(i,j)==109 && b(i,j)==161)
                  {mascara_vehiculo(i,j)=1;}
        }

        mascara_vehiculo.get_normalize(0,255);
        mascara_vehiculo.display();

        //Morfologia para mejorar la mascara
        mascara_vehiculo.dilate(3).erode(3);

        //guardo las lineas del auto

        Hough = hough(mascara_vehiculo);
        Hough.display("hough");
        linea = InversaHough(Hough,1);

        //Guardo las lineas del vehiculo
        trayectoria+=linea;

        //Intecepto las lineas para obtener las trayectorias

        //Muestro la trajectoria a seguir
        CImg<float> resultado=original+trayectoria;
        resultado.display("Trayectoria");

    }

    return 0;
}

