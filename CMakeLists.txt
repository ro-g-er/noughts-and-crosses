cmake_minimum_required(VERSION 3.13)  # CMake version check
project(noughts-and-crosses)          # Create project
set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0)
FetchContent_MakeAvailable(SFML)

# Add source files
set(SOURCE_FILES src/main.cpp src/map.cpp src/map.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(noughts_and_crosses ${SOURCE_FILES})

target_link_libraries(noughts_and_crosses PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(noughts_and_crosses PRIVATE cxx_std_23)

install(TARGETS noughts_and_crosses)

# Add GTest
#add_subdirectory(third_party/Google_tests)

# Add tests
#add_subdirectory(tests)