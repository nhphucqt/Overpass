cmake_minimum_required(VERSION 3.10)
project(SFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SFML library
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


# Add your source files here
add_executable(main main.cpp)

# Link your executable to SFML
target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-network sfml-audio opengl32)

# cmake -S. -Bbuild -G "MinGW Makefiles"
# cmake --build build
# cmake --build build --verbose