cmake_minimum_required(VERSION 3.1)

project(Snake)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB town_src
    "src/*.cpp"
)

add_executable(Snake main.cpp ${town_src})
target_link_libraries(Snake sfml-graphics sfml-audio sfml-window sfml-system)
target_include_directories(Snake PRIVATE src)
