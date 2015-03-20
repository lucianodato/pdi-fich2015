#include <iostream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;


// funcion circulo cuadrado item 4
CImg <unsigned char> circulocuadrado(int x, int y,int r)
{
    CImg<unsigned char> img4(x,y,1,1,0);
    int xx[]={255,0,0};
    img4.draw_circle(x/2,y/2,r,xx,1);
 // img4.draw_circle(x,y,radio,color,opacity);
    return img4;
}

int main(int argc, char *argv[]) {
    cimg_usage("Ejercicio 4.");
    CImgDisplay da, db, dc, dd;


//item 1
  //CImg<unsigned char> img1(x,y,z,canales)
    CImg<unsigned char> img1(256,256,1,1);
    cimg_forX(img1,x)
        cimg_forY(img1,y)
        img1(x,y)=y;
    da.assign(img1);
    da.set_title("Item 1");

//item 2

    CImg<unsigned char> img2(100,100,1,1);
    cimg_forX(img2,x)
        cimg_forY(img2,y)
        img2(x,y)=y;
    img2.resize(256,256);// o normalize?
    db.assign(img2);
    db.set_title("Item 2");

//item 3

//	CImg<unsigned char> img3(100,100,1,1);
//	cimg_forX(img3,x){
//		int a=x%2;
//		cimg_forY(img3,y)
//			img3(x,y)=a;
//	}
    CImg<unsigned char> img3(100, 100, 1, 1);
    for(int x=0; x<100; x++){
        for(int y=0; y<100; y++){
            img3(x, y)=(x%2)*255;
        }
    }
    dc.assign(img3);
    dc.set_title("Item 3");

//item 4


    dd.assign(circulocuadrado(256,256,50));
    dd.set_title("Item 4");


    // esperamos que alguno de todos los displays sea cerrado para salir
    while(!da.is_closed() && !db.is_closed() && !dc.is_closed() && !dd.is_closed()){
        da.wait_all(); // esperamos un evento en cualquier display

        if(db.is_key('n')){
            static int n=0;
            n=(n==0)?1:0; // enciende/apaga la normalizacion del display
            db.assign(img2,(n==0)?"No normalizado":"Normalizado",n); // setea el display normalizado o no reasignando la imagen
        }
    }


    return 0;
}
