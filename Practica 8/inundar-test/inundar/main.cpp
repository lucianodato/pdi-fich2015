#include "funciones.h"

int main()
{
    CImg<bool> img(11,12,1,1,0);
img(1,1)=img(2,1)=img(3,1)=img(3,2)=img(3,3)=img(3,4)=img(2,4)=img(4,4)=1;
img(7,4)=img(8,4)=img(9,4)=img(7,3)=img(8,3)=img(9,3)=img(8,2)=1;
img(7,7)=img(8,7)=img(9,7)=img(9,8)=img(9,9)=img(9,10)=img(8,10)=img(7,10)=1;
img(7,9)=img(8,9)=img(6,9)=img(1,10)=img(1,6)=img(2,7)=img(3,8)=1;

CImg<bool> Inundada=Inundar(img,0.5,1,1);
(img,Inundada).display();
return 0;
}
