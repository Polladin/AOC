
import numpy as np


class Point:

    def __init__(self, x, y, id):

        self.x = x
        self.y = y
        self.id = id
        self.queue = []
        self.step = 0


def read_points(filename):

    idx = 0
    points = []

    with open(filename) as f:
        for _line in f.readlines():
            points_raw = [_coord.strip() for _coord in _line.split(',')]
            points.append(Point(x=int(points_raw[0]),
                                y=int(points_raw[1]),
                                id=idx))
            idx += 1

    return points


CELL_OFFSET = [[1, 0], [0, 1], [-1, 0], [0, -1]]


def fill_queue(field, cur_pos, target_queue):

    x_max = field.shape[0]
    y_max = field.shape[1]

    cell_offsets = []

    if cur_pos[0] > 0:
        cell_offsets.append([-1, 0])
    if cur_pos[1] > 0:
        cell_offsets.append([0, -1])
    if cur_pos[0] + 1 < x_max:
        cell_offsets.append([1, 0])
    if cur_pos[1] + 1 < y_max:
        cell_offsets.append([0, 1])

    # print(cur_pos)
    # print(cell_offsets)

    for _offset in cell_offsets:
        if field[cur_pos[0] + _offset[0]][cur_pos[1] + _offset[1]] == -1:
            new_coord = [cur_pos[0] + _offset[0], cur_pos[1] + _offset[1]]
            if new_coord not in target_queue:
                target_queue.append(new_coord)


def calc_result(field):

    x_max, y_max = field.shape

    map_points_id = {}

    for i in range(x_max):
        for j in range(y_max):

            if field[i][j] not in map_points_id:
                map_points_id[field[i][j]] = 1
            else:
                map_points_id[field[i][j]] += 1

    return map_points_id


def find_xmax_and_ymax(points):

    x_max = 0
    y_max = 0

    for _point in points:
        x_max = max(x_max, _point.x)
        y_max = max(y_max, _point.y)

    return x_max, y_max


def move_points(points, offset_x, offset_y):

    for _point in points:
        _point.x += offset_x
        _point.y += offset_y


def task_6(filename):

    points = read_points(filename)

    # Get Max X and Max Y
    x_max, y_max = find_xmax_and_ymax(points)

    x_max_field = x_max * 2 + 1
    y_max_field = y_max * 2 + 1

    move_points(points, int(x_max / 2), int(y_max / 2))

    # Create Field
    field = np.full((x_max_field, y_max_field), -1)
    field_info = [[[] for _ in range(y_max_field)] for _ in range(x_max_field)]

    # Initialize start points
    for _point in points:

        # Init field
        field[_point.x][_point.y] = _point.id
        field_info[_point.x][_point.y] = [0, _point]

        # Init queue
        fill_queue(field, [_point.x, _point.y], _point.queue)

    # print(field)

    # Arrays for marked points
    points_inf = []
    points_end = []

    # BFS
    step = 0

    while len(points_inf) + len(points_end) != len(points):

        step += 1

        for _point in points:

            next_queue = []

            for _next_coords in _point.queue:

                # Mark point on field
                if field[_next_coords[0]][_next_coords[1]] == -1:

                    # Not filled point
                    field[_next_coords[0]][_next_coords[1]] = _point.id
                    field_info[_next_coords[0]][_next_coords[1]] = [step, _point]

                    # Find next points
                    fill_queue(field, _next_coords, next_queue)

                elif field_info[_next_coords[0]][_next_coords[1]][0] == step:

                    # Point already filled on the same step
                    field[_next_coords[0]][_next_coords[1]] = - 2
                    field_info[_next_coords[0]][_next_coords[1]] = [step]

                # fill points_inf
                if _next_coords[0] < 1 or _next_coords[0] >= x_max_field - 1 or \
                   _next_coords[1] < 1 or _next_coords[1] >= y_max_field - 1:
                    # print('Add to inf : ', _point.id, ' with coords : ', _next_coords)
                    if _point.id not in points_inf:
                        points_inf.append(_point.id)

            _point.queue = next_queue

            # print('Point id : ', _point.id, ' queue : ', next_queue)

            # fill points_end
            if len(_point.queue) == 0 and \
               _point.id not in points_end and \
               _point.id not in points_inf:
                points_end.append(_point.id)

        # print(field)
        print('Step : ', step)

    print('Points end : ', points_end)
    print('Points inf : ', points_inf)

    res_map = calc_result(field)

    max_cells = 0
    for _point_id in points_end:
        max_cells = max(max_cells, res_map[_point_id])

    print(res_map)
    print('Max cells : ', max_cells)


def task_6_2(filename):

    points = read_points(filename)

    # Get Max X and Max Y
    x_max, y_max = find_xmax_and_ymax(points)

    field = np.zeros((x_max, y_max))

    count_cells = 0

    for i in range(x_max):
        for j in range(y_max):

            for _point in points:
                field[i][j] += abs(_point.x - i) + abs(_point.y - j)

            if field[i][j] < 10000:
                count_cells += 1

    print(count_cells)


# task_6('task_6_2.txt')
task_6_2('task_6_2.txt')
