#pragma once

#include <string>
#include <vector>


class PassportProcessing
{

private:

    using t_record = std::pair< std::string, std::string >;
    using t_records = std::vector< t_record >;
    using t_passport = std::vector< t_records >;

public:

    int task_1( const std::string & filename );
    int task_2( const std::string & filename );

private:

    static t_passport prepare_input( const std::string & filename );

    static bool is_valid( const t_record & record );

    static bool is_all_mandatory_fields_presented( const t_records & records );
};


