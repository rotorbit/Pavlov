cmake_minimum_required(VERSION 2.8)

project("Pavlov")
set(CMAKE_BUILD_TYPE Release)

#set(VTK_DIR "/usr/local/include/vtk-6.2")
#find_package(VTK REQUIRED NO_MODULE)
find_package(VTK COMPONENTS vtkCommonCore vtkIOXML NO_MODULE)
include(${VTK_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(rtbt_pavlov SHARED formats/vtk/rtbtVTK.cpp output/def_output.cpp output/output.cpp main.cpp)

target_link_libraries(rtbt_pavlov ${VTK_LIBRARIES})
