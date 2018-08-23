cmake_minimum_required(VERSION 3.5)
project(azlib)

add_library(${PROJECT_NAME} azdata.cpp azstring.cpp azlist.cpp azlib.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)