#include "funciones.h"

#define SOPA 100
#define MOSCA 25
#define PLATO 200
#define RADIO 5.0
#define RUTA "../../../../Parcial de Practica/Moscas/Platos0.jpg"
#define REF_SOPA  113

const float blanco[] = {1, 1, 1};

template<class T>
CImg<T> buscar_plato(CImg<T>img){

    CImg<T> mascara(img.width(),img.height(),1,1);
    CImg<T> grises = img.get_RGBtoHSI().get_channel(2).get_normalize(0,255);

    //busco el plato y luego hago la mascara para recorte
    mascara = grises.get_threshold(PLATO);
    mascara = mascara.erode(5).dilate(7);
    //mascara=relleno_automatico(mascara); muyyyy lento!!!

    //Me armo la mascara buscando los maximos y minimos del circulo
    //Puntos x e y maximos y minimos
    vector<punto> coordenadas;
    punto max,min;
    int maxx,maxy,minx,miny;

    //Calculo las coordenas min y max de la mascara
    coordenadas=maxmin_coord(mascara);
    max=  coordenadas[1];
    min = coordenadas[0];
    maxx=max.x;maxy=max.y;
    minx=min.x;miny=min.y;

    //Coordenadas del centro del circulo
    int c_x = (maxx+minx)/2, c_y = (maxy+miny)/2;
    int radio = maxx - c_x;

    //mascara a cero y luego dibujo el circulo
    mascara.draw_circle(c_x, c_y,radio,blanco);

    mascara.display();
    //Dibujo el circulo

    //retorno el plato
    CImg<T> plato = trim_image(img,mascara);

    //Lleno de blanco el fondo (Sino no puedo calcular
    mascara = NOTimg(trim_image(mascara,mascara));
    mascara.display();
    cimg_forXY(plato,i,j){
        if(mascara(i,j)==1)
        {
            plato(i,j)=255;
        }
    }

    plato.display();
    return plato;
}

template<class T>
CImg<T> buscar_sopa(CImg<T>img,int &tipo_sopa){

    CImg<T> sopa;
    CImg<int> mascara;

    //Genero una mascara del centro del plato para determinar el color promedio
    //El amarrilo, sopa de la casa, tiene una media mas alta que el naranja de la sopa de zapatallo

    CImg<T> color = img.get_crop((img.width()/2)-10,(img.height()/2)-10,(img.width()/2)+10,(img.height()/2)+10);
    //Naranja 102, Amarillo arriba de 113
    tipo_sopa = 1;
    if(color.mean()>REF_SOPA){ tipo_sopa=2;}

    //Busco por colorslicingRBG el color de la sopa para usar de mascara
    sopa = ColorMaskHSI(img,img.width()/2,img.height()/2,RADIO);

    //Calulo la mascara pasando a grises, umbralizo, aplico apertura y luego busco las coordenadas
    //del circulo para tener una buena mascara
    sopa = sopa.RGBtoHSI().get_channel(2).get_normalize(0,255);
    mascara = sopa.threshold(SOPA);
    mascara = mascara.erode(5).dilate(5);

    //Me armo la mascara buscando los maximos y minimos del circulo
    //Puntos x e y maximos y minimos
    vector<punto> coordenadas;
    punto max,min;
    int maxx,maxy,minx,miny;

    //Calculo las coordenas min y max de la mascara
    coordenadas=maxmin_coord(mascara);
    max=  coordenadas[1];
    min = coordenadas[0];
    maxx=max.x;maxy=max.y;
    minx=min.x;miny=min.y;

    //Coordenadas del centro del circulo
    int c_x = (maxx+minx)/2, c_y = (maxy+miny)/2;
    int radio = maxx - c_x;

    //mascara a cero y luego dibujo el circulo
    mascara.draw_circle(c_x, c_y,radio,blanco);

    mascara.display();

    sopa = trim_image(img,mascara);

    //Lleno de blanco el fondo (Sino no puedo calcular
    mascara = NOTimg(trim_image(mascara,mascara));
    cimg_forXY(sopa,i,j){
        if(mascara(i,j)==1)
        {
            sopa(i,j)=255;
        }
    }

    //retorno el plato
    sopa.display();
    return sopa;

}

template<class T>
CImg<T> cuenta_moscas(CImg<T>img,double &cant_moscas){

    CImg<T> grises = img.RGBtoHSI().get_channel(2).get_normalize(0,255);
    CImg<int> moscas;
    //detecto las moscas en la imagen
    //Escala de grises --> Convoluciono con pasa bajos para borronear
    //--> umbralizado bajo (30) --> negativo de la imagen. La necesito en blanco
    moscas = grises.get_convolve(mask(19));
    moscas = grises.get_threshold(MOSCA);

    //Invierto para obtener las moscas en blanco
    moscas = NOTimg(moscas);

    //Morfologia - Hago una apertura custom para para borrar puntos espureos
    moscas = moscas.get_dilate(5).erode(9);

    //Etiqueto para buscar la cantidad de objetos en la imagen
    moscas = label_cc(moscas);

    //Cuento la cantidad de moscas
    cant_moscas = cant_grises(moscas);

    return moscas;

}

int main()
{
    //Variables
    CImg<double> original,grises,plato,sopa;
    CImg<int> moscas_imagen,moscas_plato,moscas_sopa;
    CImg<double> kernel(3,3,1,1,1);
    double cant_moscas_img,cant_moscas_plato,cant_moscas_sopa;
    int tipo_sopa; //1 zapallo - 2 de la casa
    //Asignacion de Variables
    original.load(RUTA);
    kernel.fill(1);

    //busco el plato y luego hago la mascara para recorte
    plato = buscar_plato(original);

    //Busco la sopa en el plato e identifico el tipo. hago el recorte
    sopa = buscar_sopa(original,tipo_sopa);

    (original,plato,sopa).display("Mesa - Plato - Sopa");

    //Cuento las moscas totales en: la Mesa,el plato y la sopa

    moscas_imagen = cuenta_moscas(original,cant_moscas_img);
    moscas_plato = cuenta_moscas(plato,cant_moscas_plato);
    moscas_sopa = cuenta_moscas(sopa,cant_moscas_sopa);

    //Muestro las mascaras de las moscas
    (moscas_imagen,moscas_plato,moscas_sopa).display("Moscas en: Mesa - Plato - Sopa");


    std::cout<<"Moscas en la mesa:"<<cant_moscas_img<<endl;
    std::cout<<"Moscas en el plato:"<<cant_moscas_plato<<endl;
    std::cout<<"Moscas en la sopa:"<<cant_moscas_sopa<<endl;

    //Detemino si la sopa se puede o no tomar
    if(tipo_sopa ==1){
        if(cant_moscas_plato<=3){
            std::cout<<"Ricas sopa de zapallo. A comer!"<<endl;}
        else{std::cout<<"Sopa de zapallos, muchas moscas!"<<endl;
        }
    }

    if(tipo_sopa ==2){
        if(cant_moscas_plato<=4){
            std::cout<<"Ricas sopa de la casa. A comer!"<<endl;}
        else{std::cout<<"Sopa de la casa, muchas moscas!"<<endl;
        }
    }

    return 0;

}
