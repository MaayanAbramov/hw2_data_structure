cmake_minimum_required(VERSION 3.21)
project(RecordsCompany)

set(CMAKE_CXX_STANDARD 11)

add_executable(RecordsCompany recordsCompany.cpp recordsCompany.h Costumer.cpp Costumer.h Record.cpp Record.h utilesWet2.h mainWet2.cpp AvlTree.h Group.cpp Group.h)
