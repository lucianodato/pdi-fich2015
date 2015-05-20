#include "funciones.h"
///CImg<T>& noise	(sigma,noise_type = 0 )
///Add random noise to pixel values.
///Parameters
///sigma	Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global value range.
///noise_type Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician)
int main()
{

    //PARA TEST, LO PODES BORRAR RENA

    CImg<unsigned char> h2;
    CImg<unsigned char> img(512,512,1,1,127); //img con gris cte 127
    //noise type: gaussian
    CImg<unsigned char> res=img.get_noise(2,0);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" gaussian");
    res=img.get_noise(8,0);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" gaussian");
    res=img.get_noise(16,0);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" gaussian");


    //noise type: uniform
    res=img.get_noise(2,1);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" uniform");
    res=img.get_noise(8,1);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" uniform");
    res=img.get_noise(16,1);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" uniform");

    //noise type: salt and pepper
    res=img.get_noise(2,2);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" salt and pepper");
    res=img.get_noise(8,2);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" salt and pepper");
    res=img.get_noise(16,2);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph(" salt and pepper");


    //noise type: possion
    res=img.get_noise(2,3);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("possion");
    res=img.get_noise(8,3);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("possion");
    res=img.get_noise(16,3);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("possion");


    //noise type: Rician
    res=img.get_noise(2,4);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("Rician");
    res=img.get_noise(8,4);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("Rician");
    res=img.get_noise(16,4);
    h2=res.get_histogram(256,0,255).normalize(0,255).display_graph("Rician");

    //salt and pepper y possion : no cambia el histograma si cambio el sigma


    return 0;
}

