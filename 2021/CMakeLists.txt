
cmake_minimum_required (VERSION 3.12)

project (AdventOfCode2021)

################ Definitions ###############

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DINPUT_FILES="${CMAKE_CURRENT_SOURCE_DIR}/input")

################# BOOST ######################
#
#SET(Boost_USE_STATIC_LIBS ON)	
#set(Boost_USE_MULTITHREADED ON)  
#
#find_package(Boost 1.64 REQUIRED COMPONENTS 
#		program_options 
#		filesystem
#		regex 
#        iostreams
#	)
#
#include_directories( ${Boost_INCLUDE_DIRS} )	
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

############## Common ############################

file(GLOB COMMON_SRC src/common/*)

############## UTests ############################

file(GLOB UTESTS_SRC src/tests/*)
add_executable(utests ${UTESTS_SRC} ${COMMON_SRC})

############## --- Day 1: Report Repair --- ##########

file(GLOB DAY_1_SRC src/day_1/*)
add_executable(day_01 ${DAY_1_SRC} ${COMMON_SRC})

############## --- Day 2: Dive --- ##########

file(GLOB DAY_2_SRC src/day_2/*)
add_executable(day_02 ${DAY_2_SRC} ${COMMON_SRC})

############## --- Day 3: Binary Diagnostic --- ##########

file(GLOB DAY_3_SRC src/day_3/*)
add_executable(day_03 ${DAY_3_SRC} ${COMMON_SRC})

############## --- Day 4: Gian Squid --- ##########

file(GLOB DAY_4_SRC src/day_4/*)
add_executable(day_04 ${DAY_4_SRC} ${COMMON_SRC})

############## --- Day 5: Hydrothermal Venture --- ##########

file(GLOB DAY_5_SRC src/day_5/*)
add_executable(day_05 ${DAY_5_SRC} ${COMMON_SRC})

############## --- Day 6: Lanternfish --- ##########

file(GLOB DAY_6_SRC src/day_6/*)
add_executable(day_06 ${DAY_6_SRC} ${COMMON_SRC})

############## --- Day 7: The Treachery of Whales --- ##########

file(GLOB DAY_7_SRC src/day_7/*)
add_executable(day_07 ${DAY_7_SRC} ${COMMON_SRC})

############## --- Day 8: Seven Segment Search --- ##########

file(GLOB DAY_8_SRC src/day_8/*)
add_executable(day_08 ${DAY_8_SRC} ${COMMON_SRC})

############## --- Day 9: Smoke Basin --- ##########

file(GLOB DAY_9_SRC src/day_9/*)
add_executable(day_09 ${DAY_9_SRC} ${COMMON_SRC})

############## --- Day 10: Syntax Scoring --- ##########

file(GLOB DAY_10_SRC src/day_10/*)
add_executable(day_10 ${DAY_10_SRC} ${COMMON_SRC})
