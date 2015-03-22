#include <iostream>
#include "CImg.h"
#include <vector>
using namespace cimg_library;
using namespace std;

using namespace std;

 CImg<unsigned char> umbral( CImg<unsigned char>img,int val1,int val2){
     cimg_forX(img,i)
             cimg_forY(img,j)
             if (img(i,j)<val1) img(i,j)=0; else
             if (img(i,j)>val2) img(i,j)=255; else img(i,j)=127;

     return img;
 }

int main(int argc, char *argv[])
{
    CImg<unsigned char> imgOrig,aux;
    vector<int> v;
    imgOrig.load("../../../../images/botellas.tif");
    CImgDisplay displayImagen;
   // um=umbral(um,50,250);
    displayImagen.assign(imgOrig);
    char window_title[50];
    //varias imagenes en una pantalla
       CImgList<> img;
       // img.insert(img1);
       // img.insert(img2);
       // img.display("My List");
    int contador=0,m=0,l=0;
    int j=imgOrig.height()/2;
    bool flag=true;
    cimg_forX(imgOrig,i){
            if(imgOrig(i,j)!=0){
                if (i=0) flag=false;
                v.push_back(m);
                contador++;
                m=0;
            }
            else
            {    v.push_back(contador);
                m++;
                contador=0;
            }

            for(int i=0;i<v.size()-1;i++)
               img.insert( aux.get_crop(v[i],0,v[i+1],imgOrig.height()));
            aux.clear();


    }




    while(!displayImagen.is_closed()){
        displayImagen.wait_all(); // esperamos algun evento en el display
        displayImagen.render(imgOrig);
        sprintf(window_title,"Botellas");
        displayImagen.set_title(window_title);
        displayImagen.paint();
    }


    return 0;
}

