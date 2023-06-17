cmake_minimum_required(VERSION 3.16.3)
project(RecordsCompany)

set(CMAKE_CXX_STANDARD 11)

add_executable(RecordsCompany Customer.cpp Customer.h Record.cpp Record.h utilesWet2.h mainWet2.cpp AvlTree.h hash_table.h Union_Find_not_final.h RankTree.h)
