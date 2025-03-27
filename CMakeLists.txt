cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	PolynomProcessor
	VERSION 0.9.0
	LANGUAGES CXX
	DESCRIPTION "A small program to solve a problem that I was given at an interview a long time ago"
)

add_library(
	${PROJECT_NAME}
	src/PolynomProcessor.hpp
	src/Lexer.h src/Lexer.cpp
	src/Parser.h src/Parser.cpp)

add_executable(run_tests src/main.cpp)
target_link_libraries(run_tests PRIVATE ${PROJECT_NAME})

add_executable(test_polynom_generator src/generator.cpp)

add_custom_command(
	TARGET run_tests
	POST_BUILD
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/polynoms.txt ${CMAKE_CURRENT_BINARY_DIR}/polynoms.txt
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tests
)