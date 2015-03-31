#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

float numImagenes=100,desvio_ruido=20;

int main()
{

    CImg<unsigned char> img1,img2;
    CImgList<unsigned char> disp;

    img1.clear();
    img1.load("../../../../images/cameraman.tif");//carga imagen en memo
    CImg<unsigned char> noiseImg(img1),promedio;
    CImgList<unsigned char> listaImagenes;
    //Hacer Imagen Ruidosa
    //noise(desvio, tipo ruido)
    //(0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician).
    noiseImg.noise(desvio_ruido,0);
    for(int i=0;i<numImagenes;i++)
        listaImagenes.push_back(img1.get_noise(desvio_ruido,0));
    promedio=reducRuido(listaImagenes);//pasar lista de imagenes con ruido
    disp.insert(img1);disp.insert(noiseImg);disp.insert(promedio);
    //disp(img1,noise,suma,promedio);
    CImgDisplay displayImagen(disp,"Original - Noise - Suma");
    while (!displayImagen.is_closed()) {
        displayImagen.wait();
    }

    return 0;
}

