#include "funciones.h"


using namespace std;

//Selecciono que lote de imagenes quiero cargar. Banderas,Caricaturas, Paisajes o Personajes
string imagenes[] = {"Bandera", "Caricaturas", "Paisaje", "Personaje"};
//vector<string> imagenes(strArr);
string tipo_imagen;

int main()
{
    //Uso un string para generalizar el path y poder traerme un bloque completo de imagenes
    string path = "../../../../images/Busqueda_histograma/",path_completo;
    path_completo=path;

    string path_entrada = "../../../../images/Busqueda_histograma/Caricaturas05.jpg";

    //Aloco memoria para las 5 imagenes
    CImg <float> img1,img2,hist1,hist2;
    CImgList<float> lista_histograma,lista_promedio;

    char numeracion[50];

    //recorro los tipos de imagenes y calculo los promedios

    for (int k=0;k<4;k++){

        tipo_imagen =imagenes[k];
        path_completo+=tipo_imagen;

        //Cargo el listado de Imagenes a analizar
        for (int i=1;i<=5;i++){

            sprintf(numeracion,"0%i.jpg",i);
            path_completo+=numeracion;

            //Cargo la imagen y genero su histograma
            img1.load(path_completo.data());
            img1.normalize(0,255);
            hist1 = img1.get_histogram(256,0,255);

            //Push histograma a la lista
            lista_histograma.push_back(hist1);

            //para la proxima imagen. path a cero
            path_completo=path;
            path_completo+=tipo_imagen;
        }

        CImg<float> promedio = promedio_histograma(lista_histograma);
        lista_promedio.push_back(promedio);
        path_completo=path;

    }

    //Cargo la imagen que voy a testear con las clases de imagen
    img2.load(path_entrada.data());
    hist2 = img2.get_histogram(256,0,255);

    //Comparo con los histogramas promedios

    vector<double> puntajes;
    double min =hist2.dot(lista_promedio(0))/lista_promedio(0).magnitude(2);
    int ind =0;
    puntajes.push_back(min);

    cout<<"Puntaje de la categoria - "<<imagenes[0]<<" "<<puntajes[0]<<endl;

    for(int i=1;i<lista_promedio.size();i++){

        puntajes.push_back(hist2.dot(lista_promedio(i)/lista_promedio(i).magnitude(2)));
        if(puntajes[i]>min){
            ind =i;
            min = puntajes[i];
        }

        cout<<"Puntaje de la categoria - "<<imagenes[i]<<" "<<puntajes[i]<<endl;
    }

    cout <<"Pertenece a la categoria "<<imagenes[ind]<<endl;


//    CImg<float> lista =lista_promedio(ind);
//    lista.display_graph();
//    lista = lista_promedio(2);
//    lista.display_graph();
//    hist2.display_graph();



    return 0;
}
