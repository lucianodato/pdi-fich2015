#include <iostream>
#include <string>
#include <CImg.h>
int main()
{
std::cout << "run CImg hello world..." << std::endl;
cimg_library::CImg<unsigned char> img;
std::string strFileInput = "lena.jpg";
std::string strFileOutput = "lena.png";
img = cimg_library::CImg<unsigned char>(strFileInput.c_str());
std::cout << "load " << strFileInput << "..." << std::endl;
std::cout << "width = " << img.width() << std::endl;
std::cout << "height = " << img.height() << std::endl;
std::cout << "color = " << img.spectrum() << std::endl;
img.display("Input image");
img.save_png(strFileOutput.c_str());
return 0;
}
