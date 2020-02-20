cmake_minimum_required(VERSION 2.8)

project(Rotation3Dim)


if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=c++11)
endif()

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

add_executable(Rotation3Dim MACOSX_BUNDLE Rotation3Dim.cxx)

if( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(Rotation3Dim ITKReview ${ITK_LIBRARIES})
else( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(Rotation3Dim ${ITK_LIBRARIES})
endif( "${ITK_VERSION_MAJOR}" LESS 4 )
