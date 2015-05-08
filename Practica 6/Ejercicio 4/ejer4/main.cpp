#include "funciones.h"
#include <unordered_map>
#include <functional> // For std::hash<std::string>.
#include <string>
#include <iostream>

///CImg<T>& noise	(sigma,noise_type = 0 )
///Add random noise to pixel values.
///Parameters
///sigma	Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global value range.
///noise_type	Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician).


int main()
{
   // CImg<float> img1;
    //img1.load("../../../../images/camino.tif");

   // cout <<"EL MAXIMO ES: "<<img1.median()<<endl; ---> median me hace la MEDIA NO LA MEDIANA!! programar mediana
CImg<double> img;
    CImgList<double> da,db;
    img.load("../../../../images/camino.tif");
    img.normalize(0,1);
    CImg<double> ruido=img.get_noise(0.2,0);// 0 = gaussian, 1 =inform, 2=salt and pepper, 3 =possion
    CImg<double> imgR=filter(img.get_channel(0),4,1,0);

//http://stackoverflow.com/questions/9683488/repeated-elements-in-a-stdvector
    // Test data.
       std::vector<std::string> v;
       v.push_back("a");
       v.push_back("b");
       v.push_back("c");
       v.push_back("a");
       v.push_back("c");
       v.push_back("d");
       v.push_back("a");

       // Hash function for the hashtable.
       auto h = [](const std::string* s) {
           return std::hash<std::string>()(*s);
       };

       // Equality comparer for the hashtable.
       auto eq = [](const std::string* s1, const std::string* s2) {
           return s1->compare(*s2) == 0;
       };

       // The hashtable:
       //      Key: Pointer to element of 'v'.
       //      Value: Occurrence count.
       std::unordered_map<const std::string*, size_t, decltype(h), decltype(eq)> m(v.size(), h, eq);

       // Count occurances.
       for (auto v_i = v.cbegin(); v_i != v.cend(); ++v_i)
           ++m[&(*v_i)];

       // Print strings that occur more than once:
       for (auto m_i = m.begin(); m_i != m.end(); ++m_i)
           if (m_i->second > 1)
               std::cout << *m_i->first << ": " << m_i->second << std::endl;


    return 0;
}

