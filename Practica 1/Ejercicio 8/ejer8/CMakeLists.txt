project(ejer8)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

#Add auxiliary libraries or funcion files
file(GLOB MyCSources *.c)
file(GLOB MyHSources *.h)
file(GLOB MyCPPSources *.cpp)

#change outputs directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MyCSources} ${MyHSources} ${MyCPPSources})

#added X11 config
find_package(X11)
find_package (Threads)
if (X11_FOUND)
include_directories(${X11_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${X11_LIBRARIES})
endif (X11_FOUND)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

