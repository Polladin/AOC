
import numpy as np

FIELD_SIZE_X = 301
FIELD_SIZE_Y = 301


def fill_field(field, serial_number):

    for i in range(FIELD_SIZE_X):
        for j in range(FIELD_SIZE_Y):
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
    fill_field(field, serial_number)

    # Fill scores
    # fill_scores(field, scores)
    scores = np.copy(field)

    # Find max in scores
    max_scores, max_coordinate = get_max_score(scores, 1)
    max_grid = 1

    for _id in range(2, 301):
        if _id % 10 == 0:
            print('ID :', _id)
        add_to_score(field, scores, _id)
        _score, _coord = get_max_score(scores, _id)

        if _score > max_scores:
            max_scores = _score
            max_coordinate = _coord
            max_grid = _id

        # if _id == 16:
        #     print(scores[90][269])

    print('max_scores : ', max_scores)
    print('max_coordinate : ', max_coordinate)
    print('max grid :', max_grid)


task_11(7989)
