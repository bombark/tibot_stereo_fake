cmake_minimum_required (VERSION 2.6)
project (stereo_fake)
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

find_package( OpenCV REQUIRED )

add_executable (stereo_fake src/main.cpp)
target_link_libraries (stereo_fake tiobj tisys ${OpenCV_LIBS})

install(TARGETS stereo_fake DESTINATION bin)
