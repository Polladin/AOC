import cProfile
import numpy as np

FIELD_SIZE_X = 5
FIELD_SIZE_Y = 5


def fill_field(field, serial_number, size):

    for i in range(size):
        for j in range(size):
            rack_id = i + 10
            field[i][j] = (rack_id * j + serial_number) * rack_id
            field[i][j] = int(((field[i][j] % 1000) / 100)) - 5


def fill_scores(field, scores):

    for i in range(FIELD_SIZE_X - 2):
        for j in range(FIELD_SIZE_Y - 2):
            for _x_offset in range(3):
                for _y_offset in range(3):
                    scores[i][j] += field[i + _x_offset][j + _y_offset]


def add_to_score(field, scores, id_to_add):

    # print('id_to_add :', id_to_add)

    for i in range(FIELD_SIZE_X - id_to_add):
        for j in range(FIELD_SIZE_Y - id_to_add):
            _x_offset = id_to_add - 1
            for _y_offset in range(id_to_add):
                scores[i][j] += field[i + _x_offset][j + _y_offset]

            _y_offset = id_to_add - 1
            for _x_offset in range(id_to_add - 1):
                scores[i][j] += field[i + _x_offset][j + _y_offset]


def get_max_score(scores, id_grid):

    max_score = scores[0][0]
    max_coords = [0, 0]

    for i in range(FIELD_SIZE_X - id_grid):
        for j in range(FIELD_SIZE_Y - id_grid):
            if scores[i][j] > max_score:
                max_score = scores[i][j]
                max_coords = [i, j]

    return max_score, max_coords


def task_11(serial_number):

    # scores = np.zeros((FIELD_SIZE_X - 2, FIELD_SIZE_Y - 2))
    field = np.zeros((FIELD_SIZE_X, FIELD_SIZE_Y))

    # Fill a field
    fill_field(field, serial_number, FIELD_SIZE_X)

    # Fill scores
    # fill_scores(field, scores)
    scores = np.copy(field)

    # Find max in scores
    max_scores, max_coordinate = get_max_score(scores, 1)
    max_grid = 1

    for _id in range(2, FIELD_SIZE_X):
        if _id % 10 == 0:
            print('ID :', _id)
        print(scores)
        add_to_score(field, scores, _id)
        _score, _coord = get_max_score(scores, _id)

        if _score > max_scores:
            max_scores = _score
            max_coordinate = _coord
            max_grid = _id

        # if _id == 16:
        #     print(scores[90][269])
    print(scores)
    print('max_scores : ', max_scores)
    print('max_coordinate : ', max_coordinate)
    print('max grid :', max_grid)


def fill_even(field_by_2, curr_field, size_by_2):

    for _i in range(len(curr_field)):
        for _j in range(len(curr_field[0])):
            curr_field[_i][_j] = field_by_2[_i][_j] + \
                                 field_by_2[_i + size_by_2][_j] + \
                                 field_by_2[_i][_j + size_by_2] + \
                                 field_by_2[_i + size_by_2][_j + size_by_2]


def fill_odd(field0, prev_field, curr_field, size_of_cell):

    for _i in range(len(curr_field)):
        for _j in range(len(curr_field[0])):

            subfield = field0[_i:_i + size_of_cell, _j:_j + size_of_cell]

            curr_field[_i][_j] = prev_field[_i][_j]
            curr_field[_i][_j] += np.sum(subfield, axis=0)[size_of_cell - 1]
            curr_field[_i][_j] += np.sum(subfield, axis=1)[size_of_cell - 1]
            curr_field[_i][_j] -= field0[_i + size_of_cell - 1][_j + size_of_cell - 1]


def fill_odd_2(field0, field_by_2, field_by_2_1, curr_field, size_of_cell):

    size_by_2 = int(size_of_cell / 2)

    for _i in range(len(curr_field)):
        for _j in range(len(curr_field[0])):

            curr_field[_i][_j] = field_by_2[_i, _j] + field_by_2[_i + size_by_2 + 1, _j + size_by_2 + 1]
            curr_field[_i][_j] += field_by_2_1[_i][_j + size_by_2] + field_by_2_1[_i + size_by_2][_j]
            curr_field[_i][_j] -= field0[_i + size_by_2][_j + size_by_2]


def find_max_in_fields(all_fields):

    max_val = all_fields[0][0][0]
    max_idx = 0
    max_pos = (0, 0)

    for _idx in range(len(all_fields)):

        for _i in range(len(all_fields[_idx])):
            for _j in range(len(all_fields[_idx][_i])):
                if all_fields[_idx][_i][_j] > max_val:
                    max_val = all_fields[_idx][_i][_j]
                    max_idx = _idx
                    max_pos = (_i, _j)

    return max_val, max_idx, max_pos


def task_11_2(serial_number):

    MAX_CELL_SIZE = 300

    all_fields = []

    # Create fields for all possible size
    for _idx in range(MAX_CELL_SIZE):
        all_fields.append(np.zeros((MAX_CELL_SIZE - _idx, MAX_CELL_SIZE - _idx)))

    # Fill a first field 300 x 300
    fill_field(all_fields[0], serial_number, MAX_CELL_SIZE)

    # for _field in all_fields:
    #     print(_field)

    for _idx in range(2, MAX_CELL_SIZE + 1):

        # print('Index:', _idx)

        # Fill even fields size
        if _idx % 2 == 0:
            fill_even(all_fields[int(_idx / 2) - 1], all_fields[_idx - 1], int(_idx / 2))
        else:
            # fill_odd(all_fields[0], all_fields[_idx - 2], all_fields[_idx - 1], _idx)
            fill_odd_2(all_fields[0], all_fields[int(_idx / 2) - 1], all_fields[int(_idx / 2)], all_fields[_idx - 1], _idx )
        # break

    # Find max
    max_val, max_idx, max_pos = find_max_in_fields(all_fields)

    print('max_scores : ', max_val)
    print('max_coordinate : ', max_pos)
    print('max grid :', max_idx + 1)

    # for _field in all_fields:
    #     print(_field)


# task_11_2(7989)
cProfile.run('task_11_2(7989)')
