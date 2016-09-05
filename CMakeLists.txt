cmake_minimum_required(VERSION 3.4)
project(milk
	LANGUAGES CXX
	VERSION 0.1
)

include_directories("include")

add_subdirectory("include")
add_subdirectory("lib")
add_subdirectory("tools")
add_subdirectory("tests")
