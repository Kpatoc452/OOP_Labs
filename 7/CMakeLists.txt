cmake_minimum_required(VERSION 3.10)
project(lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

include_directories(include)
add_library(game_lib
    src/npc.cpp
    src/orc.cpp
    src/knight.cpp
    src/bear.cpp
    src/factory.cpp
    src/visitor.cpp
    src/observer.cpp
    src/editor.cpp
    src/game.cpp
)

target_link_libraries(game_lib Threads::Threads)

add_executable(main main.cpp)
target_link_libraries(main game_lib)

enable_testing()
add_executable(tests tests/tests.cpp)
target_link_libraries(tests game_lib gtest_main)
add_test(NAME tests COMMAND tests)
