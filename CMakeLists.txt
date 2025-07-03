cmake_minimum_required(VERSION 3.29)
project(gps_driver C)

set(CMAKE_C_STANDARD 23)

add_library(gps_driver STATIC gps_driver.c)
