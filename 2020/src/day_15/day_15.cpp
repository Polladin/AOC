//
// Created by alexpall on 20.12.2020.
//


#include <iostream>

#include "rambunctious_recitation.h"


int main()
{
  RambunctiousRecitation rambunctiousRecitation;

  std::cout << "Res test 1: " << rambunctiousRecitation.task_1( { 0, 3, 6 } ) << std::endl;
  std::cout << "Res TASK 1: " << rambunctiousRecitation.task_1( { 8, 0, 17, 4, 1, 12 } ) << std::endl;

}