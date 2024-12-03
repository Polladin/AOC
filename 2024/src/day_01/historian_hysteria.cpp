
#include "historian_hysteria.h"

#include <vector>
#include <sstream>
#include <algorithm>

#include "common/file_reader.h"

namespace
{
    using Locations = std::pair<std::vector<int>, std::vector<int>>;

    Locations prepare_input(const std::string & filename)
    {
        Locations result;

        // Read the file
        std::vector< std::string > sInput = FileReader::read_file( filename );

        for (const std::string & _str : sInput)
        {
            std::istringstream oss ( _str );

            int firstNum, secondNum;
            oss >> firstNum >> secondNum;

            result.first.push_back(firstNum);
            result.second.push_back(secondNum);
        }

        return result;
    }
}// namespace

long long HistorianHysteria::task_1(const std::string & filename)
{
    Locations locations = prepare_input( filename );

    std::sort(locations.first.begin(), locations.first.end());
    std::sort(locations.second.begin(), locations.second.end());

    long long result { 0 };

    for (size_t idx = 0; idx < locations.first.size(); ++idx)
    {
        result += std::abs(locations.first[idx] - locations.second[idx]);
    }

    return result;
}

long long HistorianHysteria::task_2(const std::string & filename)
{
    Locations locations = prepare_input( filename );

    std::sort(locations.second.begin(), locations.second.end());

    long long result { 0 };

    for (size_t idx = 0; idx < locations.first.size(); ++idx)
    {
        auto equalRange = std::equal_range(locations.second.begin(), locations.second.end(), locations.first[idx]);
        result += std::distance(equalRange.first, equalRange.second) * locations.first[idx];
    }

    return result;
}
