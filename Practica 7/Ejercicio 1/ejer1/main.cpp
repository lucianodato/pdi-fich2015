#include "funciones.h"
///CImg<T>& noise	(sigma,noise_type = 0 )
///Add random noise to pixel values.
///Parameters
///sigma	Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global value range.
///noise_type Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician).
///
int main()
{
    CImg<double> img,img_robert;
    const char* path = "../../../../images/estanbul.tif";
    img.load(path);

    //Llamo al metodo que detecta los bordes con el operador de roberts
    img_robert = roberts(img).normalize(0,255);

    //Punto 1.1 Detector de bordes de Roberts
    (img,img_robert).display("1.1: Original - Roberts");


    //Punto 1.2 Detector de border con operadores tipo: Roberts,Sobel, Prewitt,Laplaciano y LoG

    (img,roberts(img),Sobel(img,0),prewitt(img,0),laplaciano(img,0),LoG(img)).display("1.2: Original - Roberts - Sobel - Prewitt - Laplaciano - LoG");


    //Punto 1.3 Generar imagen con ruido Gaussino (sigma = 0 ; Desvio = varios) y pruebo los operadores

    CImg<double> mosq,copia,mosq_ruidozo1,mosq_ruidozo2,mosq_ruidozo3;
    const char* path_2 = "../../../../images/mosquito.jpg";
    mosq.load(path_2);
    copia = mosq;

    mosq_ruidozo1 = copia.noise(8,0);

    //Original - Ruido con desvio (8)
    (mosq,mosq_ruidozo1).display("Original - Ruido con desvio (8)");

    //Todos los operadores toma 1
    (mosq_ruidozo1,roberts(mosq_ruidozo1),Sobel(mosq_ruidozo1,0),prewitt(mosq_ruidozo1,0),laplaciano(mosq_ruidozo1,0),LoG(mosq_ruidozo1)).display("1.3: Mosq.Ruidozo (Desvio 8) - Roberts - Sobel - Prewitt - Laplaciano - LoG");

    mosq_ruidozo2 = copia.noise(16,0);

    //Original - Ruido con desvio (16)
    (mosq,mosq_ruidozo2).display("Original - Ruido con desvio (8)");

    //Todos los operadores toma 2
    (mosq_ruidozo2,roberts(mosq_ruidozo2),Sobel(mosq_ruidozo2,0),prewitt(mosq_ruidozo2,0),laplaciano(mosq_ruidozo2,0),LoG(mosq_ruidozo2)).display("1.3: Mosq.Ruidozo (Desvio 16) - Roberts - Sobel - Prewitt - Laplaciano - LoG");

    mosq_ruidozo3 = copia.noise(32,0);

    //Original - Ruido con desvio (32)
    (mosq,mosq_ruidozo3).display("Original - Ruido con desvio (8)");

    //Todos los operadores toma 2
    (mosq_ruidozo3,roberts(mosq_ruidozo3),Sobel(mosq_ruidozo3,0),prewitt(mosq_ruidozo3,0),laplaciano(mosq_ruidozo3,0),LoG(mosq_ruidozo3)).display("1.3: Mosq.Ruidozo (Desvio 32) - Roberts - Sobel - Prewitt - Laplaciano - LoG");

    return 0;
}

