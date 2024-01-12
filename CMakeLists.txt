cmake_minimum_required(VERSION 3.10.2)

project(to-do-list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(${wxWidgets_USE_FILE})

set(source_dir "${PROJECT_SOURCE_DIR}/src")
set(include_dir "${PROJECT_SOURCE_DIR}/include")

file (GLOB source_files "${source_dir}/*.cpp")
file (GLOB include_files "${include_dir}/*.h")
include_directories(${include_dir})

add_executable(to-do-list ${source_files})

target_link_libraries(to-do-list
    PRIVATE
    ${wxWidgets_LIBRARIES}
)
