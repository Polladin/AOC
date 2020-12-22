//
// Created by alexey on 21.12.2020.
//


#include <iostream>

#include "ticket_translation.h"


int main()
{
  TicketTranslation ticketTranslation;

  std::cout << "Res test 1: " << ticketTranslation.task_1( INPUT_FILES "/day_16/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << ticketTranslation.task_1( INPUT_FILES "/day_16/input_1.txt" ) << std::endl;

//  std::cout << "Res TASK 2: " << ticketTranslation.task_2( INPUT_FILES "/day_16/test_2.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << ticketTranslation.task_2( INPUT_FILES "/day_16/input_1.txt" ) << std::endl;
}
