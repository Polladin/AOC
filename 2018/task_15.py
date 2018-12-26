import copy

UNIT_ELF = 'E'
UNIT_GOBLIN = 'G'


class Unit:

    def __init__(self, x, y, unit_race):

        self.hp = 200
        self.position = [x, y]
        self.race = unit_race
        self.attack = 3

    def do_step(self, field, units):

        # print('Find path')
        # Is it not in range
        in_range, nearest_enemy, all_enemies = self.is_in_range(field)
        # print('in_range', in_range)
        if not in_range:

            # Find paths
            is_path_found, path_to_enemy = self.find_path(field, units)

            # Do step
            if is_path_found:
                self.move_unit(path_to_enemy[-2], field)
                in_range, nearest_enemy, all_enemies = self.is_in_range(field)

        if in_range:

            # Is it in range
            # print('In range : ', self.position)

            # print('Get enemy')
            nearest_enemy = self.get_enemy_to_attack(units, all_enemies)[0]
            # nearest_enemy = self.get_unit(units, nearest_enemy)

            # print('Attack unit ', nearest_enemy.position, ' with hp ', nearest_enemy.hp)
            # Attack
            nearest_enemy.hp -= self.attack
            # print('Hp ', nearest_enemy.hp, ' pos : ', nearest_enemy.position)
            if nearest_enemy.hp <= 0:
                field[nearest_enemy.position[1]] = field[nearest_enemy.position[1]][:nearest_enemy.position[0]] + '.' \
                                          + field[nearest_enemy.position[1]][nearest_enemy.position[0] + 1:]

    def get_enemy_to_attack(self, units, all_enemies):

        units_with_min_hp = [self.get_unit(units, all_enemies[0])]
        min_hp = self.get_unit(units, all_enemies[0]).hp

        for _enemy_pos in all_enemies:

            _unit = self.get_unit(units, _enemy_pos)
            if _unit.hp < min_hp:
                units_with_min_hp = [_unit]
                min_hp = _unit.hp

        return sorted(units_with_min_hp, key=lambda x: (x.position[1], x.position[0]))

    def move_unit(self, next_pos, field):

        # print('field : ', field)
        # print('next pos : ', next_pos)
        # print('field[self.position[1]][self.position[0]] :', field[self.position[1]][self.position[0]])
        # field[self.position[1]][self.position[0]] = '.'
        field[self.position[1]] = field[self.position[1]][:self.position[0]] + '.' \
                                  + field[self.position[1]][self.position[0] + 1:]
        field[next_pos[1]] = field[next_pos[1]][:next_pos[0]] + self.race \
                                  + field[next_pos[1]][(next_pos[0] + 1):]
        # field[next_pos[1]][next_pos[0]] = self.race

        self.position = [next_pos[0], next_pos[1]]

    def get_unit(self, units, pos):

        for _unit in units:
            # print('Unit pos:', _unit.position)
            # print('pos:', pos)
            if _unit.position == pos and _unit.hp > 0:
                return _unit

        raise RuntimeError('No unit with position ' + str(pos))

    def find_path_one_step(self, next_queue, cur_queue, field, color, units, steps_history):

        next_queue = []

        while len(cur_queue) > 0:
            # print('cur_queue : ', cur_queue)
            _pos = cur_queue.pop(0)
            choose_matrix = self.get_matrix_to_find(_pos, [len(field[0]), len(field)])

            for _x_offset, _y_offset in choose_matrix:
                _cur_x = _pos[0] + _x_offset
                _cur_y = _pos[1] + _y_offset

                if field[_cur_y][_cur_x] == self.get_enemy():
                    steps_history[_cur_y][_cur_x] = (_pos[0], _pos[1])
                    return self.get_unit(units, [_cur_x, _cur_y]), None

                if field[_cur_y][_cur_x] == '.' and color[_cur_y][_cur_x] == 0:
                    next_queue.append([_cur_x, _cur_y])
                    color[_cur_y][_cur_x] = 1
                    steps_history[_cur_y][_cur_x] = (_pos[0], _pos[1])

        return None, next_queue

    def find_path(self, field, units):

        enemy = None
        color = [[0 for _ in range(len(field[0]))] for _ in range(len(field))]
        cur_queue = [(self.position[0], self.position[1])]
        color[self.position[1]][self.position[0]] = 1
        next_queue = []
        steps_history = [[(-1, -1) for _ in range(len(field[0]))] for _ in range(len(field))]

        while len(cur_queue) > 0 and not enemy:
            # print('cur_queue :', cur_queue)
            enemy, next_queue = self.find_path_one_step(next_queue, cur_queue, field, color, units, steps_history)
            if not enemy:
                cur_queue = sorted(next_queue, key=lambda x: (x[1], x[0]))

        if enemy:
            psteps = [enemy.position]
            while psteps[-1] != (-1, -1):
                next_cell = steps_history[psteps[-1][1]][psteps[-1][0]]
                if next_cell != (-1, -1):
                    psteps.append(next_cell)
                else:
                    break
            # print('Enemy found in ', enemy.position)
            # print('Path:', psteps)

            return True, psteps

        return False, None

    def get_matrix_to_find(self, pos, border):
        """
        :param pos: [x, y]
        :param border:  [x_max, y_max]
        :return: [[x_offset, y_offset], ...]
        """

        x = pos[0]
        y = pos[1]
        x_max = border[0]
        y_max = border[1]

        res = []

        # Priority in top -> bot and left -> right
        if y > 0:
            res.append([0, -1])
        if x > 0:
            res.append([-1, 0])
        if x + 1 < x_max:
            res.append([1, 0])
        if y + 1 < y_max:
            res.append([0, 1])

        return res

    def get_enemy(self):
        return UNIT_ELF if self.race == UNIT_GOBLIN else UNIT_GOBLIN

    def is_in_range(self, field):
        """

        :param field:
        :return:
        """
        choose_matrix = self.get_matrix_to_find(self.position, [len(field[0]), len(field)])
        enemy_units_race = self.get_enemy()
        in_range = False
        nearest_enemy_pos = None
        all_enemies = []

        # print('hp : ', self.hp)
        # print('pos : ', self.position)
        # print('choose_matrix', choose_matrix)
        # print('enemy : ', enemy_units_race)
        # print('race : ', self.race)

        for _pos_offset in choose_matrix:
            _x = self.position[0] + _pos_offset[0]
            _y = self.position[1] + _pos_offset[1]
            # print('field[_y][_x] : ', field[_y][_x])
            if field[_y][_x] == enemy_units_race:
                in_range = True
                if not nearest_enemy_pos:
                    nearest_enemy_pos = [_x, _y]
                all_enemies.append([_x, _y])

        return in_range, nearest_enemy_pos, all_enemies


def load_input(filename):

    units = []

    with open(filename) as f:
        field = [_line.strip() for _line in f.readlines()]

    for _y, _line in enumerate(field):

        for _x, _ch in enumerate(_line):
            if _ch == 'E' or _ch == 'G':
                units.append(Unit(_x, _y, UNIT_ELF if _ch == 'E' else UNIT_GOBLIN))

        # print(_line)

    return field, units


def get_count_elves(units):
    return sum([_unit.race == UNIT_ELF for _unit in units])


def get_count_goblins(units):
    return sum([_unit.race == UNIT_GOBLIN for _unit in units])


def is_any_action_able(units):

    alive_units = []
    for _unit in units:
        if _unit.hp > 0:
            alive_units.append(_unit)

    return get_count_elves(alive_units) > 0 and get_count_goblins(alive_units) > 0


def run_battle(field, units):

    round = 0

    # One of a race should win
    while get_count_elves(units) > 0 and get_count_goblins(units) > 0:

        some_action = False

        # Do step for each unit
        for _idx, _unit in enumerate(units):

            if _unit.hp > 0:
                # print('Unit : ', _unit.position)
                some_action = is_any_action_able(units)
                _unit.do_step(field, units)

            # for _line in field:
            #     print(_line)

        alive_units = []
        for _unit in units:
            if _unit.hp > 0:
                alive_units.append(_unit)
        units = sorted(alive_units, key=lambda x: (x.position[1], x.position[0]))

        if some_action:
            round += 1

        # for _unit in units:
        #     print('Unit ', _unit.position, ' hp : ', _unit.hp)

    hp_scores = 0
    for _unit in units:
        if _unit.hp > 0:
            hp_scores += _unit.hp
            # print('Unit ', _unit.position, ' hp : ', _unit.hp)

    # print('last round : ', round)
    # print('hp : ', hp_scores)
    # print('res : ', round * hp_scores)

    return units, round, hp_scores, round * hp_scores


def change_attack(units, race, new_attack):

    for _unit in units:
        if _unit.race == race:
            _unit.attack = new_attack


def task_15(filename):

    print('-' * 20)

    # Read input data
    field, units = load_input(filename)

    # for _unit in units:
    #     print(_unit.position, _unit.race)

    _attack = 3

    while True:

        print('Attack : ', _attack)

        change_attack(units, UNIT_ELF, _attack)
        count_elves = get_count_elves(units)

        tmp_field = copy.deepcopy(field)
        remain_units, round, hp_scores, total = run_battle(tmp_field, copy.deepcopy(units))

        if count_elves == get_count_elves(remain_units):
            print('last round : ', round)
            print('hp : ', hp_scores)
            print('res : ', total)
            print('Attack : ', _attack)
            break

        _attack += 1


# task_15('task_15_1.txt')
# task_15('task_15_2.txt')
# task_15('task_15_3.txt')
# task_15('task_15_4.txt')
# task_15('task_15_5.txt')
# task_15('task_15_6.txt')
task_15('task_15_7.txt')
