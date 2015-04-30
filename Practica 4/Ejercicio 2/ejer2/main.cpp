#include <funciones.h>
int main()
{
    CImgList<float> da,db;
///item 1
CImg<float> img(256,256,1,1);
cimg_forXY(img,x,y)
       img(x,y)=y;
da.insert(AplicarPaleta(img,"../../../../images/paletas/bone.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/cool.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/copper.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/gray.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/hot.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/hsv.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/jet.pal"));
da.insert(AplicarPaleta(img,"../../../../images/paletas/pink.pal"));


///item 2
CImg<float> img2;
img2.load("../../../../images/cameraman.tif");
db.insert(AplicarPaleta(img2,"../../../../images/paletas/bone.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/cool.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/copper.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/gray.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/hot.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/hsv.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/jet.pal"));
db.insert(AplicarPaleta(img2,"../../../../images/paletas/pink.pal"));
db.display("paletas cameraman");


///item 3

//pensando

    return 0;
}

