#include "funciones.h"


using namespace std;

int main()
{
   /*
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





    //APUNTE DEFINICION DE FILTRO--> crear H
    //DEFINICION Y CARGA DE IMAGEN
    CImg<double>img(kj);
    M=img.width();
    N=img.height();
    img.resize(M,N);


    //DEFINICION DEL H  a PATA
    bool pasabajo=1;
    int n=5;
    double D0=0.1;//frec de corte
    int P=M+N-1;
    int Q=M+N-1;
    CImg<double>U(P,Q,1,1),V(P,Q,1,1);
    CImg<double>D(P,Q,1,1),H(P,Q,1,1);
    for (int i=0;i<P;i++){
        for (int j=0;j<Q;j++){
            //Variables de frecuencia U y V:
            U(i,j)=-1.+i*2./P;
            V(i,j)=-1.+j*2./Q;
            D(i,j)=sqrt(pow(U(i,j),2)+pow(V(i,j),2));
            //Definicion de la magn. de rta. en frec. de H en funcion de D:
            H(i,j)=1/(1+pow(D(i,j)/D0,2*n)); //butter
        }
    }

*/
int e=21;
    CImg<float> img,kernel(mask(e)),espacial;
    img.load("../../../../images/cameraman.tif");
    //filtrado espacial
    espacial=img.get_convolve(kernel);
    (img,espacial).display("fil espacial");

    //filtrado frec
    //directamente como dice la teoria, si agregar cero--> el resultado sera la conv circular

        int M=img.width(),N=img.height(),T=kernel.width(),L=kernel.height();
        int P = (M + T - 1);
        int Q = (N + L - 1);

        kernel.resize(P, Q, -100, -100, 0);
        CImg<float> aux_img=img.get_resize(P, Q, -100, -100, 0);

//    CImg<float> frec=filtrar(aux_img,kernel);

        CImgList<double> filtro_frec;
        filtro_frec=kernel.get_FFT();

    //Obtenemos las transformadas de Fourier de la imagen y el filtro
    CImgList<double> fft_img = aux_img.get_FFT();
    //Multiplicamos en frecuencia
    CImgList<double> tempy(2, img.width(), img.height(), img.depth(), img.spectrum(), 0);

    cimg_forXY(img,x,y) {
        //Capturamos los valores
        std::complex<double> factor1 (fft_img[0](x,y), fft_img[1](x,y)),
            factor2 (filtro_frec[0](x,y), filtro_frec[1](x,y));

        //Realizamos el producto de binomios
        std::complex<double> prod = factor1*factor2;
        //Asignamos en real e imaginario
        tempy[0](x,y) = std::real(prod);
        tempy[1](x,y) = std::imag(prod);
    }
    //Calculamos la inversa
   CImg<float> frec= tempy.get_FFT(true)[0];



   //falta recortar

    (img,frec).display();






    return 0;
}

