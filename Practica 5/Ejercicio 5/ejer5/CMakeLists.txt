project(ejer5)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

##########    COPIAR A PARTIR DE ACA  #################
#### Sobreesciribir la linea de add_executables ####

#banderas de compilacion
set(CMAKE_C_FLAGS "-lm -lpthread -lX11 -lfftw3 -lfftw3_threads")
set(CMAKE_CXX_FLAGS "-lm -lpthread -lX11 -lfftw3 -lfftw3_threads")

#Paths
set(FUNCTIONS_DIRECTORY ../../../funciones)
set(functions ../../../funciones/funciones.h)
set(cimg ../../../funciones/CImg.h)
set(fPDI ../../../funciones/PDI_functions.h)

#Adds directories
include_directories(${FUNCTIONS_DIRECTORY})

#Add auxiliary libraries or funcion files
file(GLOB MySources *.c *.h *.cpp)

#change outputs directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Agrega el ejecutable
add_executable(${PROJECT_NAME} ${SRC_LIST} ${MySources} ${cimg} ${functions} ${fPDI})
