
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
