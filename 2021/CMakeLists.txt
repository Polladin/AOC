
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

############## --- Day 11: Dumbo Octopus --- ##########

file(GLOB DAY_11_SRC src/day_11/*)
add_executable(day_11 ${DAY_11_SRC} ${COMMON_SRC})

############## --- Day 12: Passage Pathing --- ##########

file(GLOB DAY_12_SRC src/day_12/*)
add_executable(day_12 ${DAY_12_SRC} ${COMMON_SRC})

############# --- Day 13: Transparent Origami --- ##########

file(GLOB DAY_13_SRC src/day_13/*)
add_executable(day_13 ${DAY_13_SRC} ${COMMON_SRC})

############# --- Day 14: Extended Polymerization --- ##########

file(GLOB DAY_14_SRC src/day_14/*)
add_executable(day_14 ${DAY_14_SRC} ${COMMON_SRC})

############# --- Day 15: Chiton --- ##########

file(GLOB DAY_15_SRC src/day_15/*)
add_executable(day_15 ${DAY_15_SRC} ${COMMON_SRC})

############# --- Day 16: Packet Decoder --- ##########

file(GLOB DAY_16_SRC src/day_16/*)
add_executable(day_16 ${DAY_16_SRC} ${COMMON_SRC})

############# --- Day 17: Trick Shot --- ##########

file(GLOB DAY_17_SRC src/day_17/*)
add_executable(day_17 ${DAY_17_SRC} ${COMMON_SRC})

############# --- Day 18: Snailfish --- ##########

file(GLOB DAY_18_SRC src/day_18/*)
add_executable(day_18 ${DAY_18_SRC} ${COMMON_SRC})

############# --- Day 19: Beacon Scanner --- ##########

file(GLOB DAY_19_SRC src/day_19/*)
add_executable(day_19 ${DAY_19_SRC} ${COMMON_SRC})