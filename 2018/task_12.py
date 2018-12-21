
def load_input(filename):

    rules = []
    rules_result = []

    with open(filename) as f:

        _raw_lines = f.readlines()

        initial_state = [_ch for _ch in _raw_lines[0].split()[2]]

        for _idx in range(2, len(_raw_lines)):
            _rule = [_raw_lines[_idx][_idx_ch] for _idx_ch in range(5)]

            rules.append(_rule)
            rules_result.append(_raw_lines[_idx][9])

    # print('Initial state:', initial_state)
    # print('rules:', rules)
    # print('res:', rules_result)

    return initial_state, rules, rules_result


def next_generation(offset, plants, rules, res):

    left_idx = plants.index('#') - 4
    right_idx = len(plants) - 1 - plants[::-1].index('#') + 4

    offset += left_idx

    new_field = ['.' for _ in range(2)]

    for _idx in range(left_idx, right_idx - 4):

        inserted_plant = '.'

        for _rule, _rule_res in zip(rules, res):

            accepted_rule = True

            for _idx_ch_rule in range(len(_rule)):
                if plants[_idx + _idx_ch_rule] != _rule[_idx_ch_rule]:
                    accepted_rule = False
                    break

            if accepted_rule:
                inserted_plant = _rule_res
                break

        new_field.append(inserted_plant)

    new_field.extend(['.' for _ in range(4)])

    return new_field, offset


def compare_with(calculated_states, new_state, print_len=False):

    new_left_idx = new_state.index('#')
    new_right_idx = len(new_state) - 1 - new_state[::-1].index('#')
    new_len = new_right_idx - new_left_idx

    if print_len:
        print('Len:', new_len)

    for _idx, _state in enumerate(calculated_states):

        state_left_idx = _state.index('#')
        state_right_idx = len(_state) - 1 - _state[::-1].index('#')

        if new_len != state_right_idx - state_left_idx:
            continue

        # print('Len compared')

        is_compared = True
        for _idx_plant in range(new_len):
            if new_state[new_left_idx + _idx_plant] != _state[state_left_idx + _idx_plant]:
                is_compared = False

        if is_compared:
            return True, _idx

    return False, None


def task_12(filename):

    initial_state_, rules, rules_result = load_input(filename)

    initial_state = ['.' for _ in range(4)]
    initial_state.extend(initial_state_)
    initial_state.extend(['.' for _ in range(4)])

    mem_states = [initial_state]

    # print('initial_state:', initial_state)
    offset = -4
    prev_offset = 0

    for _idx in range(50000000000):
        if _idx % 2000 == 0:
            print(_idx)

        initial_state, offset = next_generation(offset, initial_state, rules, rules_result)
        # is_compared, _idx_state = compare_with(mem_states, initial_state, print_len)
        is_compared = ''.join(mem_states[-1]) == ''.join(initial_state)

        mem_states.append(initial_state)

        if is_compared:
            print(''.join(initial_state))
            # print(''.join(mem_states[_idx_state]))
            print('offset diff:', offset - prev_offset)

            offset += 50000000000 - _idx - 1
            break

    res = 0

    for _idx in range(len(initial_state)):
        if initial_state[_idx] == '#':
            res += _idx + offset

    print('res:', res)


task_12('task_12_2.txt')


# Ans 2 : 1900000000384