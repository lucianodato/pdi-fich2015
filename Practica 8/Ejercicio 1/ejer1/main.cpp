#include "funciones.h"

int main()
{
    CImg<double> img(11,12,1,1,1),se1(3,3,1,1,0),se2(3,3,1,1,0),se3(3,3,1,1,0),se4(3,3,1,1,0),se5(3,3,1,1,0),se6(3,3,1,1,0);
    se1.fill(0);   //  Structuring element 1
    se2.fill(1,0,1,0,0,0,1,0,1); //  Structuring element 2
    se3.fill(1,0,1,1,0,0,1,0,1); //  Structuring element 3
    se4.fill(1,0,1,1,0,0,1,1,1); //  Structuring element 4
    se5.fill(1,0,0,1,0,0,1,0,0); //  Structuring element 5
    se6.fill(1,1,0,1,1,0,1,1,0); //  Structuring element 6
img(1,1)=img(2,1)=img(3,1)=img(3,2)=img(3,3)=img(3,4)=img(2,4)=img(4,4)=0;
img(7,4)=img(8,4)=img(9,4)=img(7,3)=img(8,3)=img(9,3)=img(8,2)=0;
img(7,7)=img(8,7)=img(9,7)=img(9,8)=img(9,9)=img(9,10)=img(8,10)=img(7,10)=0;
img(7,9)=img(8,9)=img(6,9)=img(1,10)=img(1,6)=img(2,7)=img(3,8)=0;


(img,se1,img.get_dilate(se1)).display("se1 dilate");
(img,se2,img.get_dilate(se2)).display("se2 dilate");
(img,se3,img.get_dilate(se3)).display("se3 dilate");
(img,se4,img.get_dilate(se4)).display("se4 dilate");
(img,se5,img.get_dilate(se5)).display("se5 dilate");
(img,se6,img.get_dilate(se6)).display("se6 dilate");


(img,se1,img.get_erode(se1)).display("se1 erode");
(img,se2,img.get_erode(se2)).display("se2 erode");
(img,se3,img.get_erode(se3)).display("se3 erode");
(img,se4,img.get_erode(se4)).display("se4 erode");
(img,se5,img.get_erode(se5)).display("se5 erode");
(img,se6,img.get_erode(se6)).display("se6 erode");

    return 0;
}

