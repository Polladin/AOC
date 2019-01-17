
import math
import numpy as np
import copy


class NanoBot:

    def __init__(self, pos, radius):

        self.pos = pos
        self.radius = radius
        self.idx = -1

    def __str__(self):

        str_to_print = 'pos ' + str(self.pos[0]) + ', ' + str(self.pos[1]) + ', ' + str(self.pos[2]) + ' '
        str_to_print += 'r: ' + str(self.radius)

        return str_to_print


def load_input(filename):

    bots = []

    with open(filename) as f:

        for _line in f.readlines():

            pos = [int(_coord) for _coord in _line.split('<')[1].split('>')[0].split(',')]

            radius = int(_line.split('r=')[1])

            bots.append(NanoBot(pos, radius))

    # bots = sorted(bots, key=lambda x: x.radius)[::-1]

    for _idx, _bot in enumerate(bots):
        _bot.idx = _idx

    return bots


def task_23(filename):

    bots = load_input(filename)
    count_in_radius = 0

    print(bots[0].radius)

    for _idx, _bot in enumerate(bots):

        if abs(_bot.pos[0] - bots[0].pos[0]) + \
           abs(_bot.pos[1] - bots[0].pos[1]) + \
           abs(_bot.pos[2] - bots[0].pos[2]) <= bots[0].radius:
            count_in_radius += 1

    print('res : ', count_in_radius)


def is_bots_in_range(lbot, rbot):

    bots_range = abs(lbot.pos[0] - rbot.pos[0]) + \
                 abs(lbot.pos[1] - rbot.pos[1]) + \
                 abs(lbot.pos[2] - rbot.pos[2])

    # print('First : ', str(lbot))
    # print('Second : ', str(rbot))
    # print('Result : ', str(bots_range > lbot.radius + rbot.radius), '\n')

    return 1 if bots_range <= lbot.radius + rbot.radius else 0


def is_bot_accepted_for_group(bot, bot_group, is_in_range_array):

    is_accepted = True

    for _bot_from_group in bot_group:

        if bot == _bot_from_group:
            is_accepted = False
            break

        # if not is_bots_in_range(bot, _bot_from_group):
        if not is_in_range_array[bot.idx][_bot_from_group.idx]:
            is_accepted = False
            break

    return is_accepted


def is_bot_in_group(bot, bot_group):

    return bot in bot_group

    # for _bot in bot_group:
    #     if bot.pos == _bot.pos:
    #         return True
    #
    # return False


# def find_shortest_distance(bots):
#
#     bots = sorted(bots, key=lambda x: x.radius)
#
#     for _offset in range(-bots[0].radius, bots[0].radius + 1):
#
#         for _coordinate


def calc_dist_with_point(bot, point):
    return abs(bot.pos[0] - point[0]) + abs(bot.pos[1] - point[1]) + abs(bot.pos[2] - point[2])


def calc_dist_with_bot(lbot, rbot):
    return abs(lbot.pos[0] - rbot.pos[0]) + abs(lbot.pos[1] - rbot.pos[1]) + abs(lbot.pos[2] - rbot.pos[2])


def task_23_2(filename):

    bots = load_input(filename)

    is_in_range_array = [np.array([is_bots_in_range(_lbot, _rbot) for _rbot in bots]) for _lbot in bots]
    # print(is_in_range_array)

    bot_groups = copy.deepcopy(is_in_range_array)
    bot_groups_idx = [[i] for i in range(len(bots))]

    for _idx, _bot in enumerate(is_in_range_array):

        for _idx_in_group, _bots_in_groups in enumerate(bot_groups):

            if _idx in bot_groups_idx[_idx_in_group]:
                continue

            if _bots_in_groups[_idx] == 1:
                bot_groups_idx[_idx_in_group].append(_idx)
                bot_groups[_idx_in_group] = _bots_in_groups * _bot

    bot_groups_idx = sorted(bot_groups_idx, key=lambda x: len(x))
    print(len(bot_groups_idx[-1]))

    grouped_bots = bot_groups_idx[-1]

    min_common_aria = 900000000
    min_idx = (-1, -1)

    for _lbot_idx in grouped_bots:
        for _rbot_idx in grouped_bots:
            bots_dist = abs(bots[_lbot_idx].pos[0] - bots[_rbot_idx].pos[0]) + \
                        abs(bots[_lbot_idx].pos[1] - bots[_rbot_idx].pos[1]) + \
                        abs(bots[_lbot_idx].pos[2] - bots[_rbot_idx].pos[2])

            if abs(bots_dist - bots[_lbot_idx].radius - bots[_rbot_idx].radius) < min_common_aria:
                min_common_aria = abs(bots_dist - bots[_lbot_idx].radius - bots[_rbot_idx].radius)
                min_idx = (_lbot_idx, _rbot_idx)

    print('min_common_aria : ', min_common_aria)
    print('min_idx : ', min_idx)
    print(bots[min_idx[0]])
    print(bots[min_idx[1]])

    middle_pos = [int((bots[min_idx[0]].pos[0] + bots[min_idx[1]].pos[0]) / 2),
                  int((bots[min_idx[0]].pos[1] + bots[min_idx[1]].pos[1]) / 2),
                  int((bots[min_idx[0]].pos[2] + bots[min_idx[1]].pos[2]) / 2)]
    print('middle_pos : ', middle_pos)

    lbot_dist_to_mid = calc_dist_with_point(bots[min_idx[0]], middle_pos)
    rbot_dist_to_mid = calc_dist_with_point(bots[min_idx[1]], middle_pos)

    print('lbot :', lbot_dist_to_mid)
    print('rbot :', rbot_dist_to_mid)


import cProfile

# task_23_2('task_23_3.txt')
cProfile.run('task_23_2("task_23_2.txt")')
