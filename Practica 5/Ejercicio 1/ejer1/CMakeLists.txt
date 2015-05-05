project(ejer1)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

##########    COPIAR A PARTIR DE ACA  #################
#### Sobreesciribir la linea de add_executables ####

#banderas de compilacion
set(CMAKE_C_FLAGS "-lm -pthread -lX11 -lfftw3 -lfftw3_threads")
set(CMAKE_CXX_FLAGS "-lm -pthread -lX11 -lfftw3 -lfftw3_threads")

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

#linkea las librerias en tiempo de ejecucion
#added fftw3

FIND_LIBRARY(FFTW3_LIBRARIES libfftw3f.so.3 /usr/lib)
FIND_LIBRARY(FFTW3F_LIBRARIES libfftw3f.so.3 /usr/lib)
FIND_LIBRARY(FFTW3_LIBRARIES_TR libfftw3_threads.so.3 /usr/lib)
FIND_LIBRARY(FFTW3F_LIBRARIES_TR libfftw3f_threads.so.3 /usr/lib)
FIND_LIBRARY(FFTW3_LIBRARIES_O libfftw3.so.3.3.0 /usr/lib)
FIND_LIBRARY(FFTW3F_LIBRARIES_O libfftw3f.so.3.3.0 /usr/lib)
FIND_LIBRARY(FFTW3_LIBRARIES_TR_O libfftw3_threads.so.3.3.0 /usr/lib)
FIND_LIBRARY(FFTW3F_LIBRARIES_TR_O libfftw3f_threads.so.3.3.0 /usr/lib)

target_link_libraries (${PROJECT_NAME} ${FFTW3_LIBRARIES} ${FFTW3F_LIBRARIES} ${FFTW3_LIBRARIES_TR} ${FFTW3F_LIBRARIES_TR} ${FFTW3L_LIBRARIES} ${FFTW3L_LIBRARIES_TR})

