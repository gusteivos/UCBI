
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ucbi VERSION 0.0.0.1 LANGUAGES C)


file(GLOB executable_source_files
    "./main.c"
    "./*.c"
)

set(executable_header_files
    ./
)


add_executable(${CMAKE_PROJECT_NAME} ${executable_source_files})

include_directories(${executable_header_files})


target_link_libraries(${CMAKE_PROJECT_NAME} m)
