#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>


class Unit
{
public:

    Unit( int hp
        , int attack
        , int units
        , int initiative
        , const std::string & attackType
        , const std::vector<std::string> & weakness = {}
        , const std::vector<std::string> & immune = {}
        , std::string name = "")
    : m_hp{hp}
    , m_attack{ attack }
    , m_units{ units }
    , m_initiative{ initiative }
    , m_attackType{ attackType }
    , m_weakness{ weakness }
    , m_immune{ immune }
    , m_name{ name }
    {}

    int get_effect_power() const { return m_units * m_attack; }

    void print() const;

    int dammage_to( Unit * enemy );

public:

    int m_hp;
    int m_attack;
    int m_units;
    int m_initiative;

    std::string m_attackType;

    std::vector<std::string> m_weakness;
    std::vector<std::string> m_immune;

    std::string m_name;
};


class Task24
{
public:
    Task24();

    bool run( int boost );

    void step();

    void load_input( const std::string & filename );

    std::map<Unit*, Unit*> target_selection();

    void fill_selection( std::vector<Unit> & alliesUnits, std::vector<Unit> & enemyUnits, /*out*/ std::map<Unit*, Unit*> & unitsSelection );
    Unit * get_enemy( Unit * allyUnit, std::vector<Unit>& enemyUnits, const std::set<Unit *> & choosenEnemy );

    std::vector<Unit *> get_units_in_step_order();

    int live_units( const std::vector<Unit> & units );

    std::vector<Unit> immuneUnits;
    std::vector<Unit> infectionUnits;
};
