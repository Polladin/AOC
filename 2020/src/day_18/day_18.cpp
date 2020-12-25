#include <iostream>

#include "operation_order.h"


int main()
{
  OperationOrder operationOrder;

  std::cout << "Res test 1: " << operationOrder.task_1( INPUT_FILES "/day_18/test_2.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << operationOrder.task_1( INPUT_FILES "/day_18/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << operationOrder.task_2( INPUT_FILES "/day_18/test_2.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << operationOrder.task_2( INPUT_FILES "/day_18/input_1.txt" ) << std::endl;
}