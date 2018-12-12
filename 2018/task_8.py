

def load_input(filename):

    with open(filename) as f:
        res = [int(_num.strip()) for _num in f.readline().split()]

    return res


def add_child(inp, idx, meta):

    count_childs = inp[idx]
    count_meta = inp[idx + 1]
    next_idx = idx + 2
    sum_child_node = []
    sum_all = 0

    for _ in range(count_childs):
        next_idx, child_val = add_child(inp, next_idx, meta)
        sum_child_node.append(child_val)

    # print(sum_child_node)

    for _ in range(count_meta):
        meta.append(inp[next_idx])

        if count_childs > 0:
            if inp[next_idx] - 1 < len(sum_child_node):
                sum_all += sum_child_node[inp[next_idx] - 1]
        else:
            sum_all += inp[next_idx]

        next_idx += 1

    return next_idx, sum_all


def task_8_1(filename):

    nums = load_input(filename)

    meta = []

    _, sum_all = add_child(nums, 0, meta)

    print(meta)
    print(sum(meta))
    print(sum_all)


task_8_1('task_8_2.txt')
