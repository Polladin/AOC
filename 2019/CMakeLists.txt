
cmake_minimum_required (VERSION 3.12)

project (AdventOfCode)

################ Definitions ###############

add_definitions(-DINPUT_FILES="${CMAKE_CURRENT_SOURCE_DIR}/input")

################ BOOST ######################

SET(Boost_USE_STATIC_LIBS ON)	
set(Boost_USE_MULTITHREADED ON)  

find_package(Boost 1.64 REQUIRED COMPONENTS 
		program_options 
		filesystem
		regex 
        iostreams
	)

include_directories( ${Boost_INCLUDE_DIRS} )	
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

############## Common ############################

file(GLOB COMMON_SRC src/common/*)


############## Day 1 : The Tyranny of the Rocket Equation ##########

file(GLOB DAY_1_SRC src/Day_1/*)
add_executable(day_01 ${DAY_1_SRC} ${COMMON_SRC})

############## Day 2 : 1202 Program Alarm ##########

file(GLOB DAY_2_SRC src/Day_2/*)
add_executable(day_02 ${DAY_2_SRC} ${COMMON_SRC})

############## Day 3 : Crossed Wires ##########

file(GLOB DAY_3_SRC src/Day_3/*)
add_executable(day_03 ${DAY_3_SRC} ${COMMON_SRC})

############## Day 4 : Secure Container ##########

file(GLOB DAY_4_SRC src/Day_4/*)
add_executable(day_04 ${DAY_4_SRC} ${COMMON_SRC})

############## Day 5: Sunny with a Chance of Asteroids ##########

file(GLOB DAY_5_SRC src/Day_5/*)
add_executable(day_05 ${DAY_5_SRC} ${COMMON_SRC} src/Day_2/computer.h src/Day_2/computer.cpp)

############## Day 6: Universal Orbit Map ##########

file(GLOB DAY_6_SRC src/Day_6/*)
add_executable(day_06 ${DAY_6_SRC} ${COMMON_SRC} )

############## Day 7: Amplification Circuit ##########

file(GLOB DAY_7_SRC src/Day_7/*)
add_executable(day_07 ${DAY_7_SRC} ${COMMON_SRC} src/Day_2/computer.h src/Day_2/computer.cpp)

############## Day 8: Space Image Format ##########

file(GLOB DAY_8_SRC src/Day_8/*)
add_executable(day_08 ${DAY_8_SRC} ${COMMON_SRC})

############## Day 9: Sensor Boost ##########

file(GLOB DAY_9_SRC src/Day_9/*)
add_executable(day_09 ${DAY_9_SRC} ${COMMON_SRC} src/Day_2/computer.h src/Day_2/computer.cpp)

############## Day 10: Monitoring Station ##########

file(GLOB DAY_10_SRC src/Day_10/*)
add_executable(day_10 ${DAY_10_SRC} ${COMMON_SRC})

############## Day 11: Space Police ##########

file(GLOB DAY_11_SRC src/Day_11/*)
add_executable(day_11 ${DAY_11_SRC} ${COMMON_SRC} src/Day_2/computer.h src/Day_2/computer.cpp)


