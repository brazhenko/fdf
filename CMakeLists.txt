cmake_minimum_required(VERSION 3.13)
project(fdf C)

set(CMAKE_C_STANDARD 11)


FILE(GLOB FDF_SRC ./src/*.c)
include_directories(./inc/)

#add_library(myLogicalExtLib SHARED IMPORTED)



#set_target_properties(myLogicalExtLib PROPERTIES IMPORTED_LOCATION "/Users/lreznak-/Documents/ls/libft.a")


add_executable(fdf ${FDF_SRC} )
target_link_libraries(fdf "/Users/lreznak-/Documents/ls/libft.a")