# CMakeList.txt: проект CMake для LW2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (
	${PROJECT_NAME} 
	LW2.cpp
	stdafx.h
	generalFunc.h
	generalFunc.cpp
	mealyMinimisationFunc.h
	mealyMinimisationFunc.cpp
	mooreMinimisationFunc.h
	mooreMinimisationFunc.cpp)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
