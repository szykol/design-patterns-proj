cmake_minimum_required(VERSION 3.5)

project(Design)
set (CMAKE_CXX_STANDARD 17)

file(GLOB DESIGN_SRC
    "src/*.h"
    "src/*.cpp"
)
list(REMOVE_ITEM DESIGN_SRC "src/main.cpp")
add_executable(design "src/main.cpp")
add_library(DesignLib STATIC ${DESIGN_SRC})

target_link_libraries(design DesignLib)