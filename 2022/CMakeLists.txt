
cmake_minimum_required (VERSION 3.12)

project (AdventOfCode2022)

################ Definitions ###############

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DINPUT_FILES="${CMAKE_CURRENT_SOURCE_DIR}/input")
add_compile_options(-Wall -Wextra -pedantic)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

############## Common ############################

file(GLOB COMMON_SRC src/common/*)

############### UTests ############################

#file(GLOB UTESTS_SRC src/tests/*)
#add_executable(utests ${UTESTS_SRC} ${COMMON_SRC})

############## --- Day 1: Calorie Counting --- ##########

file(GLOB DAY_1_SRC src/day_01/*)
add_executable(day_01 ${DAY_1_SRC} ${COMMON_SRC})

############## --- Day 2: Rock Paper Scissors --- ##########

file(GLOB DAY_2_SRC src/day_02/*)
add_executable(day_02 ${DAY_2_SRC} ${COMMON_SRC})

############## --- Day 3: Rucksack Reorganization --- ##########

file(GLOB DAY_3_SRC src/day_03/*)
add_executable(day_03 ${DAY_3_SRC} ${COMMON_SRC})

############## --- Day 4: Camp Cleanup --- ##########

file(GLOB DAY_4_SRC src/day_04/*)
add_executable(day_04 ${DAY_4_SRC} ${COMMON_SRC})

############## --- Day 5: Supply Stacks --- ##########

file(GLOB DAY_5_SRC src/day_05/*)
add_executable(day_05 ${DAY_5_SRC} ${COMMON_SRC})

############## --- Day 6: Tuning Trouble --- ##########

file(GLOB DAY_6_SRC src/day_06/*)
add_executable(day_06 ${DAY_6_SRC} ${COMMON_SRC})

############## --- Day 7: No Space Left On Device --- ##########

file(GLOB DAY_7_SRC src/day_07/*)
add_executable(day_07 ${DAY_7_SRC} ${COMMON_SRC})

############## --- Day 8: Treetop Tree House --- ##########

file(GLOB DAY_8_SRC src/day_08/*)
add_executable(day_08 ${DAY_8_SRC} ${COMMON_SRC})

############## --- Day 9: Rope Bridge --- ##########

file(GLOB DAY_9_SRC src/day_09/*)
add_executable(day_09 ${DAY_9_SRC} ${COMMON_SRC})

