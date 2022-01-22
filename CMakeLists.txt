cmake_minimum_required(VERSION 2.8.12)

PROJECT(RK_MPI_MMZ_DRM)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
set(CMAKE_C_COMPILER /home/huangzihan/linux-develop/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/huangzihan/linux-develop/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./include)
include_directories(./include/linux5.10)
link_directories(${CMAKE_SOURCE_DIR}/build)

set(RK_MPI_MMZ_DRM_SRC
      src/rk_mpi_mmz.cpp
      src/rk_dmabuf.cpp
      src/rk_drm.cpp
      )


set(MMZ_LIB
      libmpimmz.so
      )

add_library(mpimmz SHARED ${RK_MPI_MMZ_DRM_SRC})
add_subdirectory(demo)