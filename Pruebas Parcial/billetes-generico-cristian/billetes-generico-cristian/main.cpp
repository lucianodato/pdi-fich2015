#include "funciones.h"

using namespace std;
#define UMBRAL 127
#define VALOR_MEDIA 0.97


int main()
{

    //kernels
    CImg<bool> img,se2(3,3),se1(3,3),se0(5,5,1,1,0);
    se0(0,0)=se0(1,1)=se0(2,2)=se0(3,3)=se0(4,4)=se0(5,5)=1;
    se0(1,2)=se0(2,3)=se0(3,2)=se0(2,1)=se0(4,3)=se0(3,4)=1;
    se1.fill(0,0,1,0,1,0,1,0,0);   //  Structuring element 1
    se2.fill(1);
    //imagen
    CImg<double> original,intensidad;
     CImg<int> etiqueta;
    original.load("../../../../Parcial de Practica/Billetes/Billetes_Generico/5_4.jpg");
    intensidad=original.get_RGBtoHSI().get_channel(2);
    img = intensidad.get_normalize(0,255).get_threshold(UMBRAL);//.get_dilate(se0).get_erode(se1).get_erode(se1).get_erode(se1);//.get_dilate(se1);
    (img,original).display();

    //para determinar si el billete esta girado o no
    double aux= img.get_crop(53,84,161,227).mean();
    if (aux<VALOR_MEDIA){
     img.rotate(180);
    }

    //Operacion de etiquetado
    etiqueta = label_cc(NOTimg(img.get_crop(134,5,186,97)));
    etiqueta.display("Etiquetado");

    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
    vector<int> grises = grises_disponibles(etiqueta);
    switch(cant_rosas){
    case 6:
        cout<<"2 PESOS";
        break;
    case 4:
        cout<<"10 PESOS";
        break;
    case 5:
        cout<<"5 PESOS";
        break;
    case 2:
        cout<<"50 PESOS";
        break;
    case 1:
        cout<<"100 PESOS";
        break;
    case 3:
        cout<<"20 PESOS";
        break;
    }



    return 0;
}

