//
// Created by alexpall on 03.12.2020.
//

#include "toboggan_trajectory.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  TobogganTrajectory tobogganTrajectory;

  std::cout << "Res test 1: " << tobogganTrajectory.task_1( INPUT_FILES "/day_3/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << tobogganTrajectory.task_1( INPUT_FILES "/day_3/input_1.txt" ) << std::endl;

//  Right 1, down 1.
//  Right 3, down 1. (This is the slope you already checked.)
//  Right 5, down 1.
//  Right 7, down 1.
//  Right 1, down 2

  std::vector< std::pair< int, int > > trajectories { { 1, 1 }, { 3, 1 }, { 5, 1 }, { 7, 1 }, { 1, 2} };

  std::cout << "Res test 2: " << tobogganTrajectory.task_2( INPUT_FILES "/day_3/test_1.txt", trajectories ) << std::endl;
  std::cout << "Res TASK 2: " << tobogganTrajectory.task_2( INPUT_FILES "/day_3/input_1.txt", trajectories ) << std::endl;
}