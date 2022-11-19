
cmake_minimum_required (VERSION 3.24)

project (AdventOfCode)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_EXE_LINKER_FLAGS -pthread )

################ Definitions ###############

add_definitions(-DINPUT_FILES="${CMAKE_CURRENT_SOURCE_DIR}/input")

################ BOOST ######################

SET(Boost_USE_STATIC_LIBS ON)	
set(Boost_USE_MULTITHREADED ON)  

#find_package(Boost 1.64 REQUIRED COMPONENTS
#		program_options
#		filesystem
#		regex
#        iostreams
#	)

#include_directories( ${Boost_INCLUDE_DIRS} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

############## Common ############################

file(GLOB COMMON_SRC src/common/*)


############## day 1 : The Tyranny of the Rocket Equation ##########

file(GLOB day_1_SRC src/day_1/*)
add_executable(day_01 ${day_1_SRC} ${COMMON_SRC})

############## day 2 : 1202 Program Alarm ##########

file(GLOB day_2_SRC src/day_2/*)
add_executable(day_02 ${day_2_SRC} ${COMMON_SRC})

############## day 3 : Crossed Wires ##########

file(GLOB day_3_SRC src/day_3/*)
add_executable(day_03 ${day_3_SRC} ${COMMON_SRC})

############## day 4 : Secure Container ##########

file(GLOB day_4_SRC src/day_4/*)
add_executable(day_04 ${day_4_SRC} ${COMMON_SRC})

############## day 5: Sunny with a Chance of Asteroids ##########

file(GLOB day_5_SRC src/day_5/*)
add_executable(day_05 ${day_5_SRC} ${COMMON_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/day_2/computer.h src/day_2/computer.cpp)

############## day 6: Universal Orbit Map ##########

file(GLOB day_6_SRC src/day_6/*)
add_executable(day_06 ${day_6_SRC} ${COMMON_SRC} )

############## day 7: Amplification Circuit ##########

file(GLOB day_7_SRC src/day_7/*)
add_executable(day_07 ${day_7_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 8: Space Image Format ##########

file(GLOB day_8_SRC src/day_8/*)
add_executable(day_08 ${day_8_SRC} ${COMMON_SRC})

############## day 9: Sensor Boost ##########

file(GLOB day_9_SRC src/day_9/*)
add_executable(day_09 ${day_9_SRC} ${COMMON_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/day_2/computer.h ${CMAKE_CURRENT_SOURCE_DIR}/src/day_2/computer.cpp)

############## day 10: Monitoring Station ##########

file(GLOB day_10_SRC src/day_10/*)
add_executable(day_10 ${day_10_SRC} ${COMMON_SRC})

############## day 11: Space Police ##########

file(GLOB day_11_SRC src/day_11/*)
add_executable(day_11 ${day_11_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 12: The N-Body Problem ##########

file(GLOB day_12_SRC src/day_12/*)
add_executable(day_12 ${day_12_SRC} ${COMMON_SRC})

############## day 13: Care Package ##########

file(GLOB day_13_SRC src/day_13/*)
add_executable(day_13 ${day_13_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 14: Space Stoichiometry ##########

file(GLOB day_14_SRC src/day_14/*)
add_executable(day_14 ${day_14_SRC} ${COMMON_SRC})

############## day 15: Oxygen System ##########

file(GLOB day_15_SRC src/day_15/*)
add_executable(day_15 ${day_15_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 16: Flawed Frequency Transmission ##########

file(GLOB day_16_SRC src/day_16/*)
add_executable(day_16 ${day_16_SRC} ${COMMON_SRC})

############## day 17: Flawed Frequency Transmission ##########

file(GLOB day_17_SRC src/day_17/*)
add_executable(day_17 ${day_17_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 18: Many-Worlds Interpretation ##########

file(GLOB day_18_SRC src/day_18/*)
add_executable(day_18 ${day_18_SRC} ${COMMON_SRC})

############## day 19: Tractor Beam ##########

file(GLOB day_19_SRC src/day_19/*)
add_executable(day_19 ${day_19_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 20: Donut Maze ##########

file(GLOB day_20_SRC src/day_20/*)
add_executable(day_20 ${day_20_SRC} ${COMMON_SRC})

############## day 21: Springdroid Adventure ##########

file(GLOB day_21_SRC src/day_21/*)
add_executable(day_21 ${day_21_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 22: Slam Shuffle ##########

file(GLOB day_22_SRC src/day_22/*)
add_executable(day_22 ${day_22_SRC} ${COMMON_SRC})

############## day 23: Category Six ##########

file(GLOB day_23_SRC src/day_23/*)
add_executable(day_23 ${day_23_SRC} ${COMMON_SRC} src/day_2/computer.h src/day_2/computer.cpp)

############## day 24: Planet of Discord ##########

file(GLOB day_24_SRC src/day_24/*)
add_executable(day_24 ${day_24_SRC} ${COMMON_SRC} )


