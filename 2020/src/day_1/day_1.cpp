
#include <iostream>

#include "expense_report.h"


int main()
{
  std::cout << "Day 1: Report Repair\n";

  ExpenseReport report;

  std::cout << "Res for test:\n" << report.task_2( INPUT_FILES "/day_1/test_1.txt" ) << std::endl;
  std::cout << "Res for task 1:\n" << report.task_2( INPUT_FILES "/day_1/input_1.txt" ) << std::endl;
}