cmake_minimum_required(VERSION 3.9)
project(Engine)

set(CMAKE_CXX_STANDARD 11)

add_executable(Engine easy_image.cc easy_image.h engine.cc ini_configuration.cc ini_configuration.h Makefile Color.cpp Color.h Point2D.cpp Point2D.h Line2D.cpp Line2D.h
        2D_L-systemen.cc 2D_L-systemen.h l_parser.cc l_parser.h 3D_LineDrawings.cc 3D_LineDrawings.h Face.cpp Face.h Figure.cpp Figure.h 3D_Figures.cc 3D_Figures.h 3D_L-systemen.cc 3D_L-systemen.h ZBuffer.cc ZBuffer.h Light.cc Light.h)