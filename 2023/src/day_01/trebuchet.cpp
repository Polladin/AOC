 #include "trebuchet.h"

#include <algorithm>
#include <cctype>
#include <limits>
#include <iostream>

#include "common/file_reader.h"

namespace
{
struct FoundDigit
{
    FoundDigit(int iPos) : pos{ iPos } {}

    int pos;
    int value {0};
};

std::pair<FoundDigit, FoundDigit> getDigit(const std::string& line)
{
    FoundDigit first {std::numeric_limits<int>::max()};
    FoundDigit second {std::numeric_limits<int>::min()};

    for (size_t pos = 0; pos < line.size(); ++pos)
    {
        if (std::isdigit(line[pos]))
        {
            first.value = (line[pos] - '0');
            first.pos = pos;
            break;
        }
    }

    for (size_t pos = line.size(); pos > 0; --pos)
    {
        if (std::isdigit(line[pos - 1]))
        {
            second.value = (line[pos - 1] - '0');
            second.pos = pos - 1;
            break;
        }
    }

    return {first, second};
}

std::pair<FoundDigit, FoundDigit> getDigitWords(const std::string& line)
{
    static const std::vector<std::string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    FoundDigit first {std::numeric_limits<int>::max()};
    FoundDigit second {std::numeric_limits<int>::min()};

    for (size_t digitIdx = 0; digitIdx < digits.size(); ++digitIdx)
    {
        const auto pos = line.find(digits[digitIdx]);

        if (pos != std::string::npos && static_cast<int>(pos) < first.pos)
        {
            first.value = digitIdx + 1;
            first.pos = pos;
        }
    }

    for (size_t digitIdx = 0; digitIdx < digits.size(); ++digitIdx)
    {
        const auto pos = line.rfind(digits[digitIdx]);

        if (pos != std::string::npos && static_cast<int>(pos) > second.pos)
        {
            second.value = digitIdx + 1;
            second.pos = pos;
        }
    }

    return {first, second};
}

}// namespace

int Trebuchete::task_1( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    int result {0};

    for( const auto & _line : sInput )
    {
        int num {0};

        for (auto itChar = _line.begin(); itChar != _line.end(); ++itChar)
        {
            if (std::isdigit(*itChar))
            {
                num = (*itChar - '0') * 10;
                break;
            }
        }

        for (auto itChar = _line.rbegin(); itChar != _line.rend(); ++itChar)
        {
            if (std::isdigit(*itChar))
            {
                num += (*itChar - '0');
                break;
            }
        }

        result += num;
    }

    return result;
}

int Trebuchete::task_2( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    int result {0};

    for( const auto & _line : sInput )
    {
        const std::pair<FoundDigit, FoundDigit> digits = getDigit(_line);
        const std::pair<FoundDigit, FoundDigit> wordDigits = getDigitWords(_line);

        int num = (digits.first.pos < wordDigits.first.pos) ? digits.first.value * 10
                                                            : wordDigits.first.value * 10;

        num += (digits.second.pos > wordDigits.second.pos) ? digits.second.value
                                                           : wordDigits.second.value;

        std::cout << _line << " : " << num << std::endl;
        result += num;
    }

    return result;
}
