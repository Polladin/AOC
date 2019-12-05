
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
add_executable(day_1 ${DAY_1_SRC} ${COMMON_SRC})

############## Day 2 : 1202 Program Alarm ##########

file(GLOB DAY_2_SRC src/Day_2/*)
add_executable(day_2 ${DAY_2_SRC} ${COMMON_SRC})

############## Day 3 : Crossed Wires ##########

file(GLOB DAY_3_SRC src/Day_3/*)
add_executable(day_3 ${DAY_3_SRC} ${COMMON_SRC})





