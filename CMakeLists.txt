cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if(NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

project(FFT)

add_executable(fft fft.h fft.cpp test_fft.cpp)

add_executable(contrastePoisson fft.h fft.cpp
                                poisson.h poisson.cpp
                                contrastePoisson.cpp)
ImagineUseModules(contrastePoisson Images)

add_executable(clonePoisson fft.h fft.cpp
                            poisson.h poisson.cpp
                            clonePoisson.cpp)
ImagineUseModules(clonePoisson Images)
