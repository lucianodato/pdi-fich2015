#include "funciones.h"

int main()
{
    CImg<double> img;
    img.load("../../../../images/cameraman.tif");
    img.display();
    cout << "Hello World!" << endl;
    return 0;
}
