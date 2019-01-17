
from task_16_2 import *


def load_input(filename):

    BEFORE_STATE = 1
    CMD_STATE = 2
    AFTER_STATE = 3

    with open(filename) as f:

        command_info = []

        states = [BEFORE_STATE, CMD_STATE, AFTER_STATE]
        state_program = False
        current_state = 0
        program = []

        # Before: [0, 1, 2, 1]
        # 14 1 3 3
        # After:  [0, 1, 2, 1]
        before = None
        cmd = None

        for _line in f.readlines():

            if len(_line.strip()) == 0:
                continue

            if state_program:
                program.append([int(_ch) for _ch in _line.split()])
            else:
                if states[current_state] == BEFORE_STATE:
                    if _line.find('Before') == -1:
                        state_program = True
                        program.append([int(_ch) for _ch in _line.split()])
                    else:
                        before = [int(_ch) for _ch in _line.split('[')[1].split(']')[0].split(',')]
                if states[current_state] == AFTER_STATE:
                    after = [int(_ch) for _ch in _line.split('[')[1].split(']')[0].split(',')]
                    command_info.append(CommandInfo(before, cmd, after))
                if states[current_state] == CMD_STATE:
                    cmd = [int(_ch) for _ch in _line.split()]

                current_state = (current_state + 1) % len(states)

        # for _info in command_info:
        #     print(_info)

    return command_info, program


def next_opcodes_generator(all_map_opcodes):

    res_map = {}

    for _key, _val in all_map_opcodes.items():
        res_map[_key] = _val[0]

    yield res_map

    for _key, _val in all_map_opcodes.items():

        for _next_val in _val[1:]:
            res_map[_key] = _next_val
            yield res_map


def del_cmd(command_map, key_num):
    for _key in command_map:
        if _key != key_num and list(command_map[key_num])[0] in command_map[_key]:
            command_map[_key].remove(list(command_map[key_num])[0])


def task_16(filename):

    command_info, program = load_input(filename)
    print(len(command_info))
    # command_info = [CommandInfo([3, 2, 1, 1], [9, 2, 1, 2], [3, 2, 2, 1])]
    res = 0

    command_map = {}

    for _cmd in command_info:

        count_possible_opcodes = 0
        available_commads = []

        for _command_to_try in CommandProcessor.ALL_COMMANDS:
            if CommandProcessor.try_command(command_info=_cmd, command_name=_command_to_try):
                count_possible_opcodes += 1
                available_commads.append(_command_to_try)

        # if _cmd.cmd[0] == 5:
        #     print(_cmd)
        #     print('available_commads :', available_commads)



        if _cmd.cmd[0] not in command_map:
            command_map[_cmd.cmd[0]] = set(available_commads)
        else:
            # print('OpCode : ', _cmd.cmd[0])
            # print('set :', command_map[_cmd.cmd[0]])
            # print('new :', available_commads)
            command_map[_cmd.cmd[0]] = command_map[_cmd.cmd[0]].intersection(available_commads)
            # print('res :', command_map[_cmd.cmd[0]])

        if count_possible_opcodes >= 3:
            res += 1

    print('Result : ', res)

    del_cmd(command_map, 0)
    del_cmd(command_map, 7)
    del_cmd(command_map, 11)
    del_cmd(command_map, 13)
    del_cmd(command_map, 10)
    del_cmd(command_map, 2)
    del_cmd(command_map, 3)
    del_cmd(command_map, 9)
    del_cmd(command_map, 15)
    del_cmd(command_map, 5)
    del_cmd(command_map, 4)
    del_cmd(command_map, 14)
    del_cmd(command_map, 8)
    del_cmd(command_map, 1)
    del_cmd(command_map, 12)

    for _key in command_map:
        print('command_map :', _key, command_map[_key])
    # print(program)

    for _key, _val in command_map.items():
        command_map[_key] = sorted(list(_val))

    # for _map_opcode in next_opcodes_generator(command_map):

        # print(_map_opcode)

    mem = [0, 0, 0, 0]
    is_correct = True

    for _cmd in program:
        if not CommandProcessor.run_command(command_map[_cmd[0]][0], _cmd, mem):
            is_correct = False

    if is_correct:
        print(mem)

        # break


task_16('task_16_1.txt')

