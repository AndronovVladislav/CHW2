cmake_minimum_required(VERSION 3.24)
project(CHW2)

set(CMAKE_CXX_STANDARD 17)

add_executable(CHW2 main.cpp Testing/Utils.cpp Testing/Utils.h Testing/TestingManager.cpp Testing/TestingManager.h Containers/KMPTestContainer.cpp Containers/KMPTestContainer.h Containers/NaiveSearchTestContainer.cpp Containers/NaiveSearchTestContainer.h Containers/TestCaseContainer.cpp Containers/TestCaseContainer.h)
