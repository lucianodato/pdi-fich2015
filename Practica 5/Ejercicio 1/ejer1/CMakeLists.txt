project(ejer1)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

#banderas de compilacion
set(CMAKE_C_FLAGS "-lfftw3")
set(CMAKE_CXX_FLAGS "-lfftw3")

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

#added X11 config
find_package(X11)
find_package (Threads)
if (X11_FOUND)
include_directories(${X11_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${X11_LIBRARIES})
endif (X11_FOUND)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

