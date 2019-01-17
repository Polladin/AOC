

OPEN_GROUND = '.'
TREES = '|'
LUMBERYARD = '#'


def load_input(filename):

    field = []

    with open(filename) as f:

        for _line in f.readlines():
            field.append([_ch for _ch in _line.strip()])

    # for _line in field:
    #     print(_line)

    return field


def get_sub_cells(field, pos):

    _x = pos[0]
    _y = pos[1]

    x_matrix = [-1, 0, 1]
    y_matrix = [-1, 0, 1]

    if _x == 0:
        x_matrix = [0, 1]
    elif _x + 1 >= len(field):
        x_matrix = [-1, 0]

    if _y == 0:
        y_matrix = [0, 1]
    elif _y + 1 >= len(field[0]):
        y_matrix = [-1, 0]

    res = []

    for _x_offset in x_matrix:
        for _y_offset in y_matrix:
            if _x_offset != 0 or _y_offset != 0:
                res.append(field[_x + _x_offset][_y + _y_offset])

    return res


def apply_rule(cur_cell, adj):

    if cur_cell == OPEN_GROUND:
        if adj.count(TREES) >= 3:
            return TREES
        else:
            return OPEN_GROUND
    elif cur_cell == TREES:
        if adj.count(LUMBERYARD) >= 3:
            return LUMBERYARD
        else:
            return TREES
    elif cur_cell == LUMBERYARD:
        if adj.count(LUMBERYARD) >= 1 and adj.count(TREES) >= 1:
            return LUMBERYARD
        else:
            return OPEN_GROUND

    raise RuntimeError('Unknown cell type')


def rules(field):

    new_field = [['.' for _ in range(len(field[0]))] for _ in range(len(field))]

    for _x in range(len(field)):
        for _y in range(len(field[0])):

            adj = get_sub_cells(field, [_x, _y])
            new_field[_x][_y] = apply_rule(field[_x][_y], adj)

    field = new_field

    # print('*' * 20)
    # for _line in field:
    #     print(''.join(_line))

    return field


def task_18(filename):

    field = load_input(filename)
    fields = [field]
    # fields = []
    # print('*' * 20)
    # for _line in field:
    #     print(''.join(_line))

    is_same = False

    field_to_cmp = []

    for _idx in range(1000000000):

        if _idx % 1000 == 0:
            print(_idx)

        new_field = rules(field)

        # if new_field == field_to_cmp:
        #     print('Cur idx:', _idx)
        #     print('Idx found:', fields.index(new_field))
        #     break

        if new_field in fields:
            print('Cur idx:', _idx)
            print('Idx found:', fields.index(new_field))
            field = new_field
            break
            # if not is_same:
            #     print('Cur idx:', _idx)
            #     print('Idx found:', fields.index(new_field))
            #     is_same = True
            #     field_to_cmp = new_field



        fields.append(new_field)
        field = new_field

    for _ in range(15):
        new_field = rules(field)
        field = new_field

    print('Last idx:', _idx)

    print('*' * 20)
    for _line in field:
        print(''.join(_line))

    res_tree = 0
    res_lumber = 0
    for _x in range(len(field)):
        for _y in range(len(field[0])):
            if field[_x][_y] == TREES:
                res_tree += 1
            elif field[_x][_y] == LUMBERYARD:
                res_lumber += 1

    print('Trees:', res_tree)
    print('Lumberyard:', res_lumber)
    print('Result:', res_tree * res_lumber)


task_18('task_18_2.txt')

