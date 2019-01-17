import numpy as np


class WallInfo:

    def __init__(self, x_range, y_range):

        self.x_range = x_range
        self.y_range = y_range

    def fill_field(self, field):

        if self.x_range[0] == self.x_range[1]:
            field[self.x_range[0], self.y_range[0]:self.y_range[1] + 1] = 8
        else:
            field[self.x_range[0]:self.x_range[1] + 1, self.y_range[0]] = 8


def print_field(field):

    for _y in range(len(field[0])):

        str_line = ''

        for _x in range(len(field)):
            if field[_x][_y] == 0:
                str_line += '.'
            if field[_x][_y] == 8:
                str_line += '#'
            if field[_x][_y] == 3:
                str_line += '+'
            if field[_x][_y] == 2:
                str_line += '|'
            if field[_x][_y] == 5:
                str_line += '~'

        print(str_line)


def load_input(filename):

    wall_info = []

    # Initialize wall info
    with open(filename) as f:

        for _line in f.readlines():

            if _line[0] == 'x':
                x_val = int(_line.split(',')[0].split('=')[1])
                y_val_left = int(_line.split(',')[1].split('=')[1].split('..')[0])
                y_val_right = int(_line.split(',')[1].split('=')[1].split('..')[1])

                wall_info.append(WallInfo(x_range=[x_val, x_val],
                                          y_range=[y_val_left, y_val_right]))
            else:
                y_val = int(_line.split(',')[0].split('=')[1])
                x_val_left = int(_line.split(',')[1].split('=')[1].split('..')[0])
                x_val_right = int(_line.split(',')[1].split('=')[1].split('..')[1])
                wall_info.append(WallInfo(x_range=[x_val_left, x_val_right],
                                          y_range=[y_val, y_val]))

    # get x_min, x_max and y_min, y_max
    x_min = wall_info[0].x_range[0]
    x_max = wall_info[0].x_range[1]
    y_min = 0 #wall_info[0].y_range[0]
    y_max = wall_info[0].y_range[1]

    for _wall in wall_info:
        x_min = min(x_min, _wall.x_range[0])
        x_max = max(x_max, _wall.x_range[1])
        y_min = min(y_min, _wall.y_range[0])
        y_max = max(y_max, _wall.y_range[1])

    x_min -= 2
    # y_min -= 2
    x_max += 2
    y_max += 2

    # Create field
    field = np.zeros((x_max - x_min + 1, y_max - y_min + 1), dtype=np.int8)

    # Normalize data
    for _wall in wall_info:
        _wall.x_range[0] -= x_min
        _wall.x_range[1] -= x_min
        _wall.y_range[0] -= y_min
        _wall.y_range[1] -= y_min

    for _wall in wall_info:
        _wall.fill_field(field)

    # Add spring
    field[500 - x_min][0 - y_min] = 3
    start_point = [500 - x_min, 0 - y_min]

    # print_field(field)

    return field, start_point


def find_left(field, position):

    _x, _y = position
    is_endless = False

    while True:
        while field[_x][_y + 1] != 0 and field[_x - 1][_y] != 8:
            _x -= 1

        if field[_x][_y + 1] == 0:
            field[_x][_y + 1] = 2
            is_endless = rec_waterfall(field, [_x, _y + 1])

        # print(field[_x, _y + 1])
        if field[_x, _y + 1] != 5 or field[_x - 1][_y] == 8:
            break

    return is_endless, _x


def find_right(field, position):

    _x, _y = position
    is_endless = False

    while True:
        if _x + 1 >= len(field) or _y + 1 >= len(field[0]):
            print_field(field)

        while field[_x][_y + 1] != 0 and field[_x + 1][_y] != 8:
            _x += 1
            if _x + 1 >= len(field) or _y + 1 >= len(field[0]):
                print_field(field)

        if field[_x][_y + 1] == 0:
            field[_x][_y + 1] = 2
            is_endless = rec_waterfall(field, [_x, _y + 1])

            if is_endless:
                break

        if field[_x, _y + 1] != 5 or field[_x + 1][_y] == 8:
            break

    return is_endless, _x


def rec_waterfall(field, position):

    stack_point = [position]
    y_max = len(field[0])
    is_endless = False

    while len(stack_point) > 0:
        # print(stack_point)
        _x, _y = stack_point[-1]

        if _y + 1 >= y_max:
            # End of map
            is_endless = True
            break

        # Fall on sand '|'
        if field[_x][_y + 1] == 2:
            is_endless = True
            break

        # Fall throw sand '.'
        if field[_x][_y + 1] == 0:
            field[_x][_y + 1] = 2
            stack_point.append([_x, _y + 1])
            continue

        # Find left
        # print('find left')
        is_endless_left, x_left = find_left(field, stack_point[-1])

        # Find right
        # print('find right')
        is_endless_right, x_right = find_right(field, stack_point[-1])

        if is_endless_left or is_endless_right:
            field[x_left:x_right + 1, _y] = 2
            is_endless = True
            break
        else:
            field[x_left:x_right + 1, _y] = 5

        stack_point.pop(-1)

    return is_endless


def task_17(filename):

    field, start_point = load_input(filename)
    stack_point = [start_point]

    rec_waterfall(field, stack_point.pop(-1))

    print_field(field)

    res = 0
    for _x in range(1, len(field)):
        for _y in range(1, len(field[0]) - 2):
            if field[_x][_y] == 5: # field[_x][_y] == 2 or
                res += 1

    print('Result : ', res)


task_17('task_17.txt')
