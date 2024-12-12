
cmake_minimum_required (VERSION 3.12)

project (AdventOfCode2024)

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

############## --- Day 1: Historian Hysteria --- ##########

file(GLOB DAY_1_SRC src/day_01/*)
add_executable(day_01 ${DAY_1_SRC} ${COMMON_SRC})

############## --- Day 2: Red-Nosed Reports --- ##########

file(GLOB DAY_2_SRC src/day_02/*)
add_executable(day_02 ${DAY_2_SRC} ${COMMON_SRC})

############## --- Day 3: Mull It Over --- ##########

file(GLOB DAY_3_SRC src/day_03/*)
add_executable(day_03 ${DAY_3_SRC} ${COMMON_SRC})

############## --- Day 4: Ceres Search --- ##########

file(GLOB DAY_4_SRC src/day_04/*)
add_executable(day_04 ${DAY_4_SRC} ${COMMON_SRC})

############## --- Day 5: Print Queue --- ##########

file(GLOB DAY_5_SRC src/day_05/*)
add_executable(day_05 ${DAY_5_SRC} ${COMMON_SRC})

############## --- Day 6: Guard Gallivant --- ##########

file(GLOB DAY_6_SRC src/day_06/*)
add_executable(day_06 ${DAY_6_SRC} ${COMMON_SRC})

############## --- Day 7: Bridge Repair --- ##########

file(GLOB DAY_7_SRC src/day_07/*)
add_executable(day_07 ${DAY_7_SRC} ${COMMON_SRC})

############## --- Day 8: Resonant Collinearity --- ##########

file(GLOB DAY_8_SRC src/day_08/*)
add_executable(day_08 ${DAY_8_SRC} ${COMMON_SRC})

############## --- Day 9: Disk Fragmenter --- ##########

file(GLOB DAY_9_SRC src/day_09/*)
add_executable(day_09 ${DAY_9_SRC} ${COMMON_SRC})

############## --- Day 10: Hoof It --- ##########

file(GLOB DAY_10_SRC src/day_10/*)
add_executable(day_10 ${DAY_10_SRC} ${COMMON_SRC})

############## --- Day 11: Plutonian Pebbles --- ##########

file(GLOB DAY_11_SRC src/day_11/*)
add_executable(day_11 ${DAY_11_SRC} ${COMMON_SRC})

############## --- Day 12: Garden Groups --- ##########

file(GLOB DAY_12_SRC src/day_12/*)
add_executable(day_12 ${DAY_12_SRC} ${COMMON_SRC})
