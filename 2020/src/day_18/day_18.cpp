#include <iostream>

#include "operation_order.h"


int main()
{
  OperationOrder operationOrder;

//  std::cout << "Res test 1: " << operationOrder.task_1( INPUT_FILES "/day_18/test_1.txt" ) << std::endl;
  std::cout << "Res test 2: " << operationOrder.task_1( INPUT_FILES "/day_18/test_2.txt" ) << std::endl;
//  std::cout << "Res test 3: " << operationOrder.task_1( INPUT_FILES "/day_18/test_3.txt" ) << std::endl;
//  std::cout << "Res test 4: " << operationOrder.task_1( INPUT_FILES "/day_18/test_4.txt" ) << std::endl;
//  std::cout << "Res test 5: " << operationOrder.task_1( INPUT_FILES "/day_18/test_5.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << operationOrder.task_1( INPUT_FILES "/day_18/input_1.txt" ) << std::endl;
}