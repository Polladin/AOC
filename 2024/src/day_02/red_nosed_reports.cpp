
#include "red_nosed_reports.h"

#include <vector>
#include <sstream>

#include "common/file_reader.h"


namespace {

using Reports = std::vector<std::vector<int>>;

Reports prepare_input(const std::string & filename)
{
    Reports result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    for (const std::string & _str : sInput)
    {
        // Add a new report
        result.emplace_back();

        std::istringstream oss ( _str );

        while (!oss.eof())
        {
            int newLevel;
            oss >> newLevel;

            result.back().push_back(newLevel);
        }
    }

    return result;
}

bool isValidLevelsTask1(int lhs, int rhs, bool isDescend)
{
    return isDescend ? (lhs > rhs && (lhs - rhs) <= 3)
                     : (rhs > lhs && (rhs - lhs) <= 3);
}

bool isValidReport(const std::vector< int > & report)
{
    const bool isDescend = report[ 0 ] > report[ 1 ];

    for ( size_t idx = 1; idx < report.size(); ++idx )
    {
        if ( !isValidLevelsTask1( report[ idx - 1 ], report[ idx ], isDescend) )
        {
            return false;
        }
    }

    return true;
}

bool isValidReportTask2(const std::vector< int > & report)
{
    if ( isValidReport( report ) )
    {
        return true;
    }

    for ( size_t idx = 0; idx < report.size(); ++idx)
    {
        std::vector< int > newReport { report };
        newReport.erase( newReport.begin() + idx );

        if ( isValidReport( newReport ) )
        {
            return true;
        }
    }

    return false;
}

}// namespace


long long RedNosedReports::task_1(const std::string & filename)
{
    Reports reports = prepare_input( filename );

    long long result { 0 };

    for ( const auto& report : reports )
    {
        result += isValidReport( report ) ? 1 : 0;
    }

    return result;
}

long long RedNosedReports::task_2(const std::string & filename)
{
    Reports reports = prepare_input( filename );

    long long result { 0 };

    for ( const auto& report : reports )
    {
        result += isValidReportTask2( report ) ? 1 : 0;
    }

    return result;
}
