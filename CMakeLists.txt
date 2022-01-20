cmake_minimum_required(VERSION 2.8.12)

PROJECT(RK_MPI_MMZ_DRM)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
set(GCC_COMPILER_PATH /home/huangzihan/linux-develop/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu)
set(CMAKE_C_COMPILER ${GCC_COMPILER_PATH}/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${GCC_COMPILER_PATH}/bin/aarch64-none-linux-gnu-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./include)
set(RK_MPI_MMZ_DRM_SRC
      src/rk_mpi_mmz.cpp
      )


# ocr_test
add_library(mpimmz SHARED ${RK_MPI_MMZ_DRM_SRC})