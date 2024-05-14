cmake_minimum_required(VERSION 3.26)
project(lab C)

set(CMAKE_C_STANDARD 11)

add_executable(lab main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c
        libs/data_structures/vector/vectorVoid.c
        libs/data_structures/vector/vectorVoid.h
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
        libs/string/tasks/string_.c
        libs/string/tasks/string_.h
)

add_subdirectory(libs)
target_link_libraries(lab data_structures)
target_link_libraries(lab algorithms)
target_link_libraries(lab string)
target_link_libraries(lab file_io)