cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(GameNgin)

include_directories(include/)

add_library(glad STATIC "src/glad.c")