cmake_minimum_required(VERSION 3.21)
project(2048-AH)
add_subdirectory("external/SFML-2.5.1")
set(SOURCE
    src/Structure/Grid.cpp
    src/Structure/Cell.cpp
)
add_executable(2048-AH.exe ${SOURCE} "src/main.cpp")
target_include_directories(2048-AH.exe PUBLIC "external/SFML-2.5.1/include")
target_include_directories(2048-AH.exe PUBLIC "include")
target_link_libraries(2048-AH.exe sfml-graphics)
target_link_libraries(2048-AH.exe sfml-window)
target_link_libraries(2048-AH.exe sfml-system)