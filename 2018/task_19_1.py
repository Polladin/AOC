from task_19_2 import *
import copy


def load_input(filename):

    ip_reg = None
    cmds_info = []

    with open(filename) as f:

        for _line in f.readlines():

            if _line[0] == '#':
                ip_reg = int(_line.split()[-1])
                continue

            cmds_info.append(CommandInfo(cmd_name=_line.split()[0],
                                         regs=[int(_ch) for _ch in _line.split()[1:]]))

    return ip_reg, cmds_info


def compare_regs(regs_1, regs_2):

    count_compared_params = 0
    compared = True
    idx_not_compared = -1

    # print('reg1:', regs_1)
    # print('reg2:', regs_2)

    for _idx in range(len(regs_1)):

        if regs_1[_idx] == regs_2[_idx]:
            count_compared_params += 1
        elif abs(regs_1[_idx] - regs_2[_idx]) > 1:
            compared = False
        else:
            idx_not_compared = _idx

    if count_compared_params + 1 < len(regs_1):
        compared = False

    if compared and regs_1[idx_not_compared] < 100:
        compared = False

    return compared, idx_not_compared


def get_next_max(mem, val):
    gr = sorted([_val for _val in mem if _val > val])

    if len(gr) > 0:
        return gr[0] - 1
    else:
        return val


def task_19(filename):

    ip_reg, cmds_info = load_input(filename)

    mem = [0 for _ in range(6)]
    mem[0] = 1
    map_regs = dict()

    idx_to_print = 0
    print(mem)

    _step = 0

    while mem[ip_reg] < len(cmds_info):
        cur_command = cmds_info[mem[ip_reg]]
        # print(cur_command)
        CommandProcessor.run_command(cur_command.name, cur_command.regs, mem)
        # print(mem)
        mem[ip_reg] += 1

        print(cur_command)
        print(mem)

        _step += 1

        if _step == 30:
            break

        # if mem[ip_reg] not in map_regs:
        #     map_regs[mem[ip_reg]] = copy.deepcopy(mem)
        # else:
        #     compared, idx_not_compared = compare_regs(map_regs[mem[ip_reg]], mem)
        #     if compared:
        #         print('Compared reg:', idx_not_compared)
        #         # print(mem)
        #         # print(map_regs[mem[ip_reg]])
        #         print('next max:', get_next_max(mem, mem[idx_not_compared]))
        #         mem[idx_not_compared] = get_next_max(mem, mem[idx_not_compared])
        #
        #         # idx_to_print += 1
        #         # if idx_to_print == 10:
        #         #     break
        #
        #     map_regs[mem[ip_reg]] = copy.deepcopy(mem)

    print(mem)


def progs_chapter_1():

    R1 = 1
    R2 = 10551305
    R4 = 1
    R5 = 0
    R0 = 1

    while R5 == 0:

        if R1 * R4 == R2 > 0:
            R0 = R1 + R0
        R4 += 1
        R5 = 1 if R4 > R2 else 0


def progs_chapter_2():

    res = 0

    for _idx in range(1, 10551306):
        if 10551305 % _idx == 0:
            res += _idx

    print(res)


progs_chapter_2()
# task_19('task_19_1.txt')

