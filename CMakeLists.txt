cmake_minimum_required(VERSION 3.13)  # CMake version check
project(noughts-and-crosses)          # Create project
set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard


find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Add source files
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(noughts_and_crosses ${SOURCE_FILES})

target_link_libraries(noughts_and_crosses PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
target_compile_features(noughts_and_crosses PRIVATE cxx_std_23)

install(TARGETS noughts_and_crosses)

# Add GTest
#add_subdirectory(third_party/Google_tests)

# Add tests
#add_subdirectory(tests)