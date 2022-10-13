# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(
	Lab1 main.cpp
	generalFunc.cpp generalFunc.h
	mealyToMoore.cpp mealyToMoore.h
	mooreToMealy.cpp mooreToMealy.h
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
