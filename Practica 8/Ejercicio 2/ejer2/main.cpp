#include "funciones.h"

///#include <plugins/skeleton.h>
///#define cimg_plugin "plugins/skeleton.h"

int main()
{
    CImg<bool> img(17,9,1,1,0);
    CImg<bool> se1(3,3,1,1,1),se2(3,3,1,1,1),se3(3,3,1,1,1),se4(3,3,1,1,1),se5(3,3,1,1,1),se6(3,3,1,1,1);
    se1.fill(1);   //  Structuring element 1
    se2.fill(0,1,0,1,1,1,0,1,0); //  Structuring element 2
    se3.fill(0,1,0,0,1,1,0,1,0); //  Structuring element 3
    se4.fill(0,1,0,0,1,1,0,0,0); //  Structuring element 4
    se5.fill(0,1,1,0,1,1,0,1,1); //  Structuring element 5
    se6.fill(0,0,1,0,0,1,0,0,1); //  Structuring element 6

    img(15,1)=img(15,2)=img(15,6)=img(15,7)=1;
    img(14,1)=img(14,2)=img(14,6)=img(14,7)=1;
    img(13,1)=img(13,2)=img(13,6)=img(13,7)=1;
    img(12,1)=img(12,2)=img(12,3)=img(12,4)=img(12,5)=img(12,6)=img(12,7)=1;
    img(11,1)=img(11,2)=img(11,3)=img(11,4)=img(11,5)=img(11,6)=img(11,7)=1;
    img(10,1)=img(10,2)=img(10,3)=img(10,4)=img(10,5)=img(10,6)=img(10,7)=1;
    img(7,4)=img(8,4)=img(9,4)=1;
    img(6,1)=img(6,2)=img(6,3)=img(6,4)=img(6,5)=img(6,6)=img(6,7)=1;
    img(5,1)=img(5,2)=img(5,3)=img(5,4)=img(5,5)=img(5,6)=img(5,7)=1;
    img(4,1)=img(4,2)=img(4,3)=img(4,4)=img(4,5)=img(4,6)=img(4,7)=1;
    img(2,1)=img(2,2)=img(2,3)=img(2,5)=img(2,6)=img(2,7)=1;
    img(3,1)=img(3,2)=img(3,3)=img(3,5)=img(3,6)=img(3,7)=1;
    img(1,1)=img(1,2)=img(1,3)=img(1,5)=img(1,6)=img(1,7)=1;


    // Compute the skeleton
    //CImg<float> flux = img.get_flux(grad,1,1);
    //    float distance=1;
    //    bool curve=1;
    //    int thresh=1;
    //   const CImg<unsigned int> skel = img.get_skeleton(flux,distance,curve,thresh);

    (img,apertura(img,se1)).display("apertura");
    (img,cierre(img,se1)).display("cierre");

    return 0;
}

