//
// Created by alexpall on 20.12.2020.
//

#include "rambunctious_recitation.h"

#include <map>
#include <unordered_map>
#include <iostream>

#include "common/file_reader.h"



int RambunctiousRecitation::task_1( const std::vector< int > & inputNumbers  )
{
  std::unordered_map< int, int > lastSpokenNumbers;

  for ( std::size_t idx = 0; idx < inputNumbers.size() - 1; ++idx )
  {
    lastSpokenNumbers[ inputNumbers[ idx ] ] = idx + 1;
  }

  int lastNumber = inputNumbers.back();
  int currentStep = inputNumbers.size();

  while ( currentStep < 30000000 )
  {
//    std::cout << "Last number: " << lastNumber << " step: " << currentStep << std::endl;

    auto it = lastSpokenNumbers.find( lastNumber );

    // Number not found
    if ( it == lastSpokenNumbers.end() )
    {
      lastSpokenNumbers[ lastNumber ] = currentStep;
      ++currentStep;
      lastNumber = 0;
      continue;
    }

    // Found
    int newNumber = currentStep - it->second;
    lastSpokenNumbers[ lastNumber ] = currentStep;
    ++currentStep;
    lastNumber = newNumber;
  }

  return lastNumber;
}
