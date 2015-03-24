#include <iostream>
#include "CImg.h"
#include <vector>
using namespace cimg_library;
using namespace std;

/*
 *
 *OBTENER VALOR DE PIXELES en Cimg
 * src.data(10, 10, 0, canal)
unsigned char *r = src.data(10, 10, 0, 0);
unsigned char *g = src.data(10, 10, 0, 1);
unsigned char *b = src.data(10, 10, 0, 2);
 *
 *
 *
 *
 * */
struct infOffset  {
    int offset,flag,xini;
};


int main(int argc, char *argv[])
{
    CImg<unsigned char> image,aux;
    image.load("../../../../images/botellas.tif");
    //image.load("/home/asusn56/Copy cristiaan3003@gmail.com/PDI-2015/pdi-fich2015/images/botellas2.tif");
    CImgDisplay main_disp(image,"Original");
    vector<infOffset> offsets;
    CImgList<> img;
    infOffset auxiliar;
    const int y = image.height()/2;//tomo fila a la mitad de la foto original
    aux=image.get_crop(0,y,0,0,image.width()-1,y,0,0);
    // aux(aux.width(),0)=0;
    int cont=0,cont0=0,cantBotellas=0;

    //offsets
    for(int i;i<aux.width();i++)
        if((int)*aux.data(i,0,0,0)!=0) {
            cont++;
            if((int)*aux.data(i+1,0,0,0)==0){
                auxiliar.offset=cont-1;
                auxiliar.flag=1;
                auxiliar.xini=i-auxiliar.offset;
                offsets.push_back(auxiliar);
                cont0=0;}
        }
        else {cont0++;
            if((int)*aux.data(i+1,0,0,0)!=0){
                auxiliar.offset=cont0-1;
                auxiliar.flag=0;
                auxiliar.xini=i-auxiliar.offset;
                offsets.push_back(auxiliar);
                cont=0;
            }
        }

    //recortar
    for(int i;i<offsets.size();i++){
        auxiliar=offsets[i];
        if(auxiliar.flag==1) //es botella-->entonces recorto y guardo
            img.push_back(image.get_crop(auxiliar.xini,0,0,0,auxiliar.xini+auxiliar.offset-1,image.height(),0,0));
    }
    //buscar vacias
    for(int i;i<offsets.size();i++)
        if((int)*img(i).data(img(i).width()/2,50,0,0)==255)
            cout<<"VACIA"<<endl;
        else
            cout<<"LLENA"<<endl;

    for(int i;i<offsets.size();i++){
        auxiliar=offsets[i];
        cout<<"Offset: "<<auxiliar.offset<<" Flag: "<<auxiliar.flag <<" x:"<<auxiliar.xini <<endl;
    }
    for(int i;i<offsets.size();i++){
        auxiliar=offsets[i];
        if(auxiliar.flag==1) cantBotellas++;
    }

    cout<<"Botellas: "<<cantBotellas<<endl;

    aux.display("Fila de imagen");
    img.display("Recortes");




    while (!main_disp.is_closed() ) {
        main_disp.wait_all();

    }


    return 0;
}

