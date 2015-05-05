#include "funciones.h"


using namespace std;

int main()
{
    clock_t start1,start2;
    double duration;

    CImg<float> img,kernel(mask(21)),pasabajos;
    img.load("../../../../images/carlock1.png");

    //Filtrado en el dominio espacial

    //Comienzo la cuenta
    start1 = clock();

    CImg<float> fil_esp = img.get_convolve(kernel);

    //Cuento cantidad de tiempo y muestro
    duration = ( clock() - start1 ) / (double) CLOCKS_PER_SEC;
    cout<<"En el dominio espacial tardo: "<< duration <<'\n';

    //Filtrado en el dominio frecuencial

    //Armo el pasabajos con el mismo tamaño del la imagen original
    pasabajos.assign(img);
    pasabajos.fill(0);
    //Los cuadrantes del circulo en cada esquina
    int radio = pasabajos.width()/32;
    pasabajos.draw_circle(0,0,radio,white,1);
    pasabajos.draw_circle(pasabajos.width(),0,radio,white,1);
    pasabajos.draw_circle(0,pasabajos.height(),radio,white,1);
    pasabajos.draw_circle(pasabajos.width(),pasabajos.height(),radio,white,1);
    pasabajos.normalize(0,1);//Normalizo para que sea un filtro
    //pasabajos.display();

    //Comienzo la cuenta
    start2 = clock();

    //Transformo la imagen y el filtro
    CImgList<float> img_tr = fourier(img);

    //Multiplico en frecuencia la imagen original y el pasabajos armado
    CImg<float> espectro_filtrado = multiplicacion(img_tr.at(0),pasabajos);

    //Antitransformo
    CImg<float> fil_frec = fourier_inv(espectro_filtrado,img_tr.at(1));

    //Cuento cantidad de tiempo y muestro
    duration = ( clock() - start2 ) / (double) CLOCKS_PER_SEC;
    cout<<"En el dominio frecuencial tardo: "<< duration <<'\n';

    //Muestro
    CImgList<float> lista(img,fil_esp,fil_frec);
    lista.display("Original - Filtrado espacial - Filtrado Frecuencial");






    return 0;
}

