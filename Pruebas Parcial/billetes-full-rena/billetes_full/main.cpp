#include "funciones.h"

#define UMBRAL_SOBEL 50
#define UMBRAL_MASCARA 2
#define UMBRAL_ROMBO 140
#define RUTA "../../../../Parcial de Practica/Billetes/Billetes_mezclados/2.jpg"
#define REF_VALUE  0.97

//GIRA BILLETE
//en funcion de la media chequeo como esta el billete, del derecho o del revez
template<typename T>
void enderezar_billete(CImg <T> &img){
    CImg <T>intensidad = img.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(150);
    double aux= intensidad.get_crop(53,84,161,227).mean();
    if (aux<REF_VALUE)
        img.rotate(180);
}

//VALOR BILLETE
//Determina en funcion de la cantidad de rombos el valor nominal del billete
template<typename T>
int valor_billete(CImg <T> img){

    img = img.get_RGBtoHSI().get_channel(2).get_normalize(0,255);
    //img.display("bN");
    //Hago un crop de la zona de interes (Se que estan son las coordenadas donde se ubican los rombos)
    img = img.get_crop(img.width()*0.2084,img.height()*0.0278,img.width()*0.29,img.height()*0.3585);
    //Desgasto con una mascara promedio por q es una imagen muy pixelada
    img = img.get_convolve(mask(5));

    //Calculo la mascara negativa con el valor de UMBRAL_ROMBO
    img = NOTimg(img.get_threshold(UMBRAL_ROMBO));
    img.display("Mascara rombos");

    //Operacion de etiquetado (calculo cuantos objetos tengo en la mascara)
    CImg <T>etiqueta = label_cc(img);

    //Cuenta la cantidad de rombos (Contar niveles de grises diferentes)
    int cant_rombos = cant_grises(etiqueta);
    switch(cant_rombos){
    case 6:
        cout<<"2 PESOS";
        return 2;
    case 5:
        cout<<"5 PESOS";
        return 5;
    case 4:
        cout<<"10 PESOS";
        return 10;
    case 3:
        cout<<"20 PESOS";
        return 20;
    case 2:
        cout<<"50 PESOS";
        return 50;
    case 1:
        cout<<"100 PESOS";
        return 100;

    }
}

int main()
{
    //imagen
    CImg<double> original,billete,r,g,b;
    original.load(RUTA);
    CImg<bool> mascara(original.width(),original.height());
    double peso=0,total=0;

    //Mascara. El fondo es fijo con RGB:
    //Obtengo la Mascara del billete. Lo hago en RGB por que el fondo es fijo: {37,53,26}
    r=original.get_channel(0);
    g=original.get_channel(1);
    b=original.get_channel(2);
    //lleno inicialmente la mascara de unos.
    //voy a buscar los blancos mas blancos y hacerlos ceros
    mascara = original.get_RGBtoHSI().get_channel(2).fill(1);
    cimg_forXY(original,i,j){
        if(r(i,j)==37 && g(i,j)==53 && b(i,j)==26){
            mascara(i,j) = 0;
        }
    }
    //apertura para eliminar la basura alrededor de las mascaras
    mascara = apertura(mascara,mask(3));

    //etiqueto toda la mascara para subdivir los billetes
    CImg<int> mascara_etiqueta = label_cc(mascara);

    //Recorto los billetes de la imagen original
    CImgList<double> billetes = trim_image_wrapper(original,mascara_etiqueta);

    //Muestro la imagen original y las subimagenes
    (original,billetes).display("Original - Billetes");

    //Billetes rotados. Empiezo a rotar uno a uno,calculo su valor nominal y guardo en el vector su suma
    CImgList<double> billetes_rotados;
    for(int indice =0;indice<billetes.size();indice++){

    billete = billetes(indice);
    //Roto el billete (sobel,hough y trim_image)

    billete = rotate_image(billete,UMBRAL_SOBEL,UMBRAL_MASCARA);

    //Hough solo rota respecto al eje theta. Hay que arreglar rotando 90 respecto a theta
    if(billete.width()<billete.height()){
        billete.get_rotate(90);
    }
    billete.display("Billete Rotado resp. al Eje theta");

    //Verifico si el billete esta del derecho o del revez. Roto si corresponde
    enderezar_billete(billete);
    //billete.display("Billete enderezado");

    //Determino el valor trim_image_wrapper del billete
    peso = valor_billete(billete);

    //Push de billetes y calculo total de monto
    total +=peso;
    billetes_rotados.push_back(billete);

    }

    //Muestro el listado de billetes rotados y muestro el total de pesos calculados
    billetes_rotados.display("Billetes Rotados");
    cout<<"El total de pesos es de:"<<total<<endl;

    return 0;

}


