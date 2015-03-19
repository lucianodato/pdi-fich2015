#Nombre de proyecto
project(Puebita)

#Version de CMake minima requerida
cmake_minimum_required(VERSION 2.8)

#Directorio de las fuentes
aux_source_directory(. SRC_LIST)

#Crea un directorio bin en el directorio de compilacion para dejar los binarios ahi (Esto iria siempre!!!)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Nombra el ejecutable de proyecto
add_executable(${PROJECT_NAME} ${SRC_LIST})

#Agrega las librerias X11 para poder sacar por pantalla
find_package(X11)
find_package (Threads)
if (X11_FOUND)
include_directories(${X11_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${X11_LIBRARIES})
endif (X11_FOUND)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
