#include "funciones.h"

#define UMBRAL 243

//Este metodo identifica dos tipos rubia o negra. True si es rubia, false es negra o cualquier otra
template<typename T>
bool tipo_cerveza(CImg<T> img){

    //Calculo el centro de masa del vaso
    int cordx = img.width()/2;
    int cordy = img.height()/2;

    //ColorMaskHSI()
    vector<float> cerveza(255,255,0);



    return true;

}

int main()
{
    //imagen
    CImg<float> original,byn,procesada,copia;
    original.load("../../../../Parcial de Practica/Cervezas/training/01.jpg");
    procesada = original;
    copia = original;
    //original.display();
    CImg<bool> B(8,8),B2(3,3),mascara;
    B.fill(1);
    B2.fill(1);
    //cordenadas para crop
    vector<punto> coordenadas;
    punto max,min;
    int minx,miny,maxx,maxy;

    //a)Encontrar la mascara del objeto.
    //1- mascara difusa, 2- escala de grises, 3 - binarizo con threadhold alto y obtengo el negativo (el fondo es blanco)
    procesada = procesada.get_convolve(mask(15));
    byn =procesada.RGBtoHSI().get_channel(2).normalize(0,255);
    mascara = negativo(byn.get_threshold(UMBRAL));
    //multiplico la mascara x original y obtengo el vaso de cerveza
    (original,copia.mul(mascara),mascara).display();

    //b) recortar imagen usando para esto la mascara y el convexhull
    //1 -convexhull,2- obtengo cordendas minimas y maximas de x,y para recortar
    //3-get crop con las cordenadas a la imagen original
    mascara = ConvexHull(mascara,true,false);

    coordenadas = maxmin_coord(mascara);
    max=  coordenadas[1];
    min = coordenadas[0];
    maxx = max.x;
    minx = min.x;
    maxx = max.y;
    minx = min.y;
    cout<<"minx: "<<minx;
    cout<<" maxx: "<<maxx;
    cout<<" miny: "<<miny;
    cout<<" maxy: "<<maxy;

    procesada = original.get_crop(maxx,maxy,minx,miny);
    procesada.display();

    //mascara.display();


    //c)determinar tipo de cerveza (negra o rubo)

    //d)Determino si la cerveza fue bien tirada

    return 0;
}

