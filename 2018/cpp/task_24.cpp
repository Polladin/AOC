#include "task_24.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <iostream>
#include <set>
#include <map>


// trim from left
inline std::string& ltrim( std::string& s, const char* t = " \t\n\r\f\v" )
{
    s.erase( 0, s.find_first_not_of( t ) );
    return s;
}

// trim from right
inline std::string& rtrim( std::string& s, const char* t = " \t\n\r\f\v" )
{
    s.erase( s.find_last_not_of( t ) + 1 );
    return s;
}

// trim from left & right
inline std::string& trim( std::string& s, const char* t = " \t\n\r\f\v" )
{
    return ltrim( rtrim( s, t ), t );
}

// string to vector
inline std::vector<std::string> string_to_vector( const std::string & str )
{
    std::vector<std::string> res;

    if ( str.length() == 0 )
        return res;

    std::stringstream ss( str );

    while ( ss.good() )
    {
        std::string str;
        std::getline( ss, str, ',' );
        res.push_back( trim(str) );
    }

    return res;
}


void create_unit(const std::string & line, const std::regex & unitPattern, /*out*/ std::vector<Unit> & v_units, const std::string & unitName )
{

    std::smatch matchUnitPattern;
    std::regex_match( line, matchUnitPattern, unitPattern );


    //std::cout << "---------------------------------------------------\n";
    //std::cout << "Line : " << line << "\n";

    //std::cout << "########################################\n";
    //std::cout << "units : " << matchUnitPattern[ 1 ] << "\n";
    //std::cout << "hp : " << matchUnitPattern[ 2 ] << "\n";

    //std::cout << "immune : " << matchUnitPattern[ 5 ] << "\n";
    //std::cout << "immune_types : " << matchUnitPattern[ 6 ] << "\n";

    //std::cout << "weak : " << matchUnitPattern[ 9 ] << "\n";
    //std::cout << "weak_types : " << matchUnitPattern[ 10 ] << "\n";

    //std::cout << "attack : " << matchUnitPattern[ 12 ] << "\n";
    //std::cout << "attack_type : " << matchUnitPattern[ 13 ] << "\n";
    //std::cout << "initiative : " << matchUnitPattern[ 14 ] << "\n";

    /*if ( matchUnitPattern.size() < 13 )
        throw std::string( "Wrong input file. Less than 13 groups in Immune units" );*/

    int units = std::stoi( matchUnitPattern[ 1 ] );
    int hp = std::stoi( matchUnitPattern[ 2 ] );
    std::string immune = matchUnitPattern[ 5 ];
    std::string immune_types = matchUnitPattern[ 6 ];
    std::string weak = matchUnitPattern[ 9 ];
    std::string weak_types = matchUnitPattern[ 10 ];
    int attack = std::stoi( matchUnitPattern[ 12 ] );
    std::string attack_type = trim( std::string( matchUnitPattern[ 13 ] ) );
    int initiative = std::stoi( matchUnitPattern[ 14 ] );

    std::vector<std::string> v_immuneTypes = string_to_vector( immune_types );
    std::vector<std::string> v_weakTypes = string_to_vector( weak_types );

    v_units.emplace_back( hp, attack, units, initiative, attack_type, v_weakTypes, v_immuneTypes, unitName + std::to_string( v_units.size() + 1 ) );
}

void load_units( std::ifstream & ifs, const std::regex & unitPattern, const std::string & firstLine, std::vector<Unit>& units, const std::string & unitName = "" )
{
    std::string line;

    // First line should be equal to firstLine
    std::getline( ifs, line );

    if ( !line.compare( firstLine ) )
        throw std::string( "Wrong first line" );

    // Load units
    while ( !ifs.eof() )
    {
        // Next line with Unit or empty line
        std::getline( ifs, line );

        if ( line.size() == 0 )
            break;

        // extract unit info from line and create Unit
        create_unit( line, unitPattern, units, unitName );
    }
}


void Unit::print() const
{
    std::cout << m_name << " units : " << m_units << " power : " << get_effect_power() << " initiative : " << m_initiative << std::endl;
}

int Unit::dammage_to( Unit * enemy )
{
    int baseDamage = m_units * m_attack;

    if ( std::find( enemy->m_immune.begin(), enemy->m_immune.end(), m_attackType ) != enemy->m_immune.end() )
        return 0;

    if ( std::find( enemy->m_weakness.begin(), enemy->m_weakness.end(), m_attackType ) != enemy->m_weakness.end() )
        baseDamage *= 2;

    return baseDamage;
}


Task24::Task24()
{
    load_input("C:/Users/alexey.kukushkin/Documents/visual studio 2015/Projects/AOC/AOC/data/tas_24_2.txt");
}

bool Task24::run( int boost )
{
    //std::cout << std::endl;
    //for ( const auto & unit : immuneUnits )
    //    unit.print();
    //for ( const auto & unit : infectionUnits )
    //    unit.print();

    for ( auto & unit : immuneUnits )
        unit.m_attack += boost;

    while ( true )
    {
        int immuneLiveUnits = live_units( immuneUnits );
        int infectionLiveUnits = live_units( infectionUnits );

        if ( immuneLiveUnits == 0 || infectionLiveUnits == 0 )
        {
            std::cout << "End game\n";
            break;
        }

        step();

        /*int newImmuneLiveUnits = live_units( immuneUnits );
        int newInfectionLiveUnits = live_units( infectionUnits );*/

        /*if ( newImmuneLiveUnits == immuneLiveUnits && newInfectionLiveUnits == infectionLiveUnits )
            break;*/

        //std::cout << std::endl;
        //for ( const auto & unit : immuneUnits )
        //    unit.print();
        //for ( const auto & unit : infectionUnits )
        //    unit.print();
    }

    int immuntUnitsCount = 0;

    for ( const auto & unit : immuneUnits )
        if ( unit.m_units > 0)
            immuntUnitsCount += unit.m_units;
    std::cout << "Immune : " << immuntUnitsCount << "\n";

    int infectionUnitsCount = 0;
    for ( const auto & unit : infectionUnits )
        if ( unit.m_units > 0 )
            infectionUnitsCount += unit.m_units;

    std::cout << "Infection : " << infectionUnitsCount << "\n";

    return immuntUnitsCount > 0 && infectionUnitsCount == 0;
}

void Task24::step()
{
    // Get enemy for all units
    std::map<Unit*, Unit*> unitEnemySelection = target_selection();

    // Get units in step order
    std::vector<Unit*> unitsInStepOrder = get_units_in_step_order();

    for ( Unit * activeUnit : unitsInStepOrder )
    {
        if ( activeUnit->m_units <= 0 )
            continue;

        // Is enemy choosen
        if ( unitEnemySelection.find(activeUnit) == unitEnemySelection.end() )
            continue;
        
        //std::cout << activeUnit->m_name << " attack " << unitEnemySelection[ activeUnit ]->m_name << " with dmg : " << activeUnit->dammage_to( unitEnemySelection[ activeUnit ] ) 
        //          << " hp : " << unitEnemySelection[ activeUnit ]->m_hp
        //          << " kill enemies : " << activeUnit->dammage_to( unitEnemySelection[ activeUnit ] ) / unitEnemySelection[ activeUnit ]->m_hp << "\n";

        // Attack !!!
        unitEnemySelection[ activeUnit ]->m_units -= activeUnit->dammage_to( unitEnemySelection[ activeUnit ] ) / unitEnemySelection[ activeUnit ]->m_hp;
    }
}


void Task24::load_input( const std::string & filename )
{
    std::ifstream ifs( filename );
    std::string line;

    // Create regex pattern fo units
    //std::regex unitPattern( R"reg((\d+) units each with (\d+) hit points \(((immune) to (.*); )?((weak) to (.*)\)) with an (attack) that does (\d+) (\w+) damage at initiative (\d+))reg" );
    std::regex unitPattern( R"reg((\d+) units each with (\d+) hit points( \(((immune) to (.*?))?(; )?((weak) to (.*))?\))? with an (attack) that does (\d+) (\w+) damage at initiative (\d+))reg" );

    // Load immune units
    load_units(ifs, unitPattern, "Immune System:\n", immuneUnits, "immune" );

    // Load infection units
    load_units( ifs, unitPattern, "Infection:\n", infectionUnits, "infection" );
}

std::map<Unit*, Unit*> Task24::target_selection()
{
    // Units with enemy selection : <Unit, Enemy>
    std::map<Unit*, Unit*> allUnitsSelection;

    // Infection Selecting
    fill_selection( infectionUnits, immuneUnits, allUnitsSelection );

    // Immune Selecting
    fill_selection( immuneUnits, infectionUnits, allUnitsSelection );

    return allUnitsSelection;
}

void Task24::fill_selection( std::vector<Unit>& alliesUnits, std::vector<Unit>& enemyUnits, /*out*/ std::map<Unit*, Unit*> & unitsSelection )
{
    // Target selection queue in order decreasing effective power oin a tie group with the higher initiative
    std::vector<Unit *> selectingQueue;

    // Function to sort selected Queue by effective power and initiative
    static const auto sortedFunc = []( const Unit * lhs, const Unit * rhs )
    {
        return lhs->get_effect_power() == rhs->get_effect_power() ? ( lhs->m_initiative > rhs->m_initiative )
            : ( lhs->get_effect_power() > rhs->get_effect_power() );
    };

    // Initialize selected Queue
    for ( auto & unit : alliesUnits )
        selectingQueue.push_back( &unit );

    // Sort selected queue
    std::sort( selectingQueue.begin(), selectingQueue.end(), sortedFunc );

    // Choosen enemy
    std::set<Unit *> choosenEnemy;

    // Sorted enemies by decreasing dammage to it or if tie by decreasing initiative : std::pair<damage, initiative>
    static const auto damage_sorter = []( const std::pair<int, int> & lhs, const std::pair<int, int> & rhs )
    {
        return lhs.first == rhs.first ? lhs.first > rhs.first
            : lhs.second > rhs.second;
    };

    // <damage, initiative> , <allyUnit, enemyUnit>
    std::map<std::pair<int, int>, std::pair<Unit *, Unit *>, decltype( damage_sorter )> damage( damage_sorter );

    std::set<Unit *> choosenUnits;

    // For each unit choose his enemy
    for ( auto * allyUnit : selectingQueue )
    {
        // Get enemy to attack
        Unit * enemyToAttack = get_enemy( allyUnit, enemyUnits, choosenEnemy );

        if ( enemyToAttack == nullptr )
            continue;

        unitsSelection.emplace( allyUnit, enemyToAttack );

        choosenEnemy.insert( enemyToAttack );
    }
}


Unit * Task24::get_enemy( Unit * allyUnit, std::vector<Unit>& enemyUnits, const std::set<Unit *> & choosenEnemy )
{
    // Sorted enemies by decreasing dammage to it or if tie by decreasing initiative : std::pair<damage, initiative>
    // sorted enemy by :
    //      1 - deal the most damage 
    //      2 - the defending group with the largest effective power
    //      3 - group with the highest initiative
    static const auto damage_sorter = []( const std::tuple<int, int, int> & lhs, const std::tuple<int, int, int> & rhs )
    {
        if ( std::get<0>( lhs ) > std::get<0>( rhs ) )
            return true;
        if ( std::get<0>( lhs ) < std::get<0>( rhs ) )
            return false;

        if ( std::get<1>( lhs ) > std::get<1>( rhs ) )
            return true;
        if ( std::get<1>( lhs ) < std::get<1>( rhs ) )
            return false;

        if ( std::get<2>( lhs ) > std::get<2>( rhs ) )
            return true;

        return false;
    };

    // <damage, initiative> , <allyUnit, enemyUnit>
    std::map<std::tuple<int, int, int>, Unit *, decltype( damage_sorter )> damageToEnemies( damage_sorter );

    // calc damage for enemy units
    for ( auto & enemyUnit : enemyUnits )
    {
        // Enemy is dead
        if ( enemyUnit.m_units <= 0 )
            continue;

        // Enemy already choosen
        if ( choosenEnemy.find( &enemyUnit ) != choosenEnemy.end() )
            continue;

        // Calculate damage to an enemy
        int possibleDamageToEnemy = allyUnit->dammage_to( &enemyUnit );

        //std::cout << allyUnit->m_name << " possible dmg to " << enemyUnit.m_name << " with dmg : " << possibleDamageToEnemy << "\n";

        if ( possibleDamageToEnemy > 0 )
            damageToEnemies.emplace( std::make_tuple( possibleDamageToEnemy, enemyUnit.get_effect_power(), enemyUnit.m_initiative ), &enemyUnit );
    }

    if ( damageToEnemies.size() == 0 )
        return nullptr;

    return damageToEnemies.begin()->second;
}

std::vector<Unit*> Task24::get_units_in_step_order()
{
    std::vector<Unit *> unitsInStepOrder;

    // Insert infection units
    for ( auto & unit : infectionUnits )
        unitsInStepOrder.push_back( &unit );

    // Insert immune units
    for ( auto & unit : immuneUnits )
        unitsInStepOrder.push_back( &unit );

    // Sort units by decreasing initiative
    std::sort( unitsInStepOrder.begin(), unitsInStepOrder.end(), 
               []( const Unit * lUnit, const Unit * rUnit ){ return lUnit->m_initiative > rUnit->m_initiative; } );

    return unitsInStepOrder;
}

int Task24::live_units( const std::vector<Unit>& units )
{
    int countLiveUnits = 0;

    for ( const auto & unit : units )
        countLiveUnits += unit.m_units > 0 ? 1 : 0;

    return countLiveUnits;
}

