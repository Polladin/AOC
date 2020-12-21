//
// Created by alexpall on 20.12.2020.
//

#include "rambunctious_recitation.h"

#include <map>

#include "common/file_reader.h"



int RambunctiousRecitation::task_1( const std::vector< int > & inputNumbers  )
{
  std::map< int, int > lastSpokenNumbers;

  for ( std::size_t idx = 0; idx < inputNumbers.size(); ++idx )
  {
    lastSpokenNumbers[ inputNumbers[ idx ] ] = idx + 1;
  }

  
}
