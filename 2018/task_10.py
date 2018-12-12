import numpy as np

def load_input(filename):

    points = []
    velo = []

    with open(filename) as f:

        for _line in f.readlines():

            points_raw = _line.split('<')[1].split('>')[0].split(',')
            points.append([int(points_raw[0]), int(points_raw[1])])

            velo_raw = _line.split('<')[2].split('>')[0].split(',')
            velo.append([int(velo_raw[0]), int(velo_raw[1])])

    print(points)
    print(velo)

    return points, velo


def get_max_diff(points):

    min_val = [points[0][0], points[0][1]]
    max_val = [points[0][0], points[0][1]]

    for _point in points:

        min_val[0] = min(min_val[0], _point[0])
        min_val[1] = min(min_val[1], _point[1])

        max_val[0] = max(max_val[0], _point[0])
        max_val[1] = max(max_val[1], _point[1])

        # print('min_val : ', min_val)
        # print('max_val : ', max_val)

    return [max_val[0] - min_val[0], max_val[1] - min_val[1]]


def get_min_val(points):
    min_val = [points[0][0], points[0][1]]
    for _point in points:
        min_val[0] = min(min_val[0], _point[0])
        min_val[1] = min(min_val[1], _point[1])
    return min_val


def evaluate(points, velo):

    for _point, _velo in zip(points, velo):

        _point[0] += _velo[0]
        _point[1] += _velo[1]


def evaluate_back(points, velo):

    for _point, _velo in zip(points, velo):

        _point[0] -= _velo[0]
        _point[1] -= _velo[1]


def print_message(points):

    diff = get_max_diff(points)
    min_val = get_min_val(points)

    arr = np.zeros((diff[0] + 1, diff[1] + 1))

    for _point in points:
        _point[0] -= min_val[0]
        _point[1] -= min_val[1]

        arr[_point[0]][_point[1]] = 8

    # print(np.transpose(arr))
    arr = np.transpose(arr)

    for i in range(diff[1] + 1):
        to_print = []
        for j in range(diff[0] + 1):
            if arr[i][j] == 0:
                to_print.append(' ')
            else:
                to_print.append('*')
        print(''.join(to_print))


def task_10_1(filename):

    points, velo = load_input(filename)

    max_diff = get_max_diff(points)

    evaluate(points, velo)
    next_max_diff = get_max_diff(points)

    res_seconds = 0

    while next_max_diff[0] < max_diff[0] or next_max_diff[1] < max_diff[1]:
        max_diff = next_max_diff
        evaluate(points, velo)
        next_max_diff = get_max_diff(points)
        res_seconds += 1

    evaluate_back(points, velo)

    print_message(points)

    print('Sec : ', res_seconds)

    # print(max_diff)
    # print(next_max_diff)


task_10_1('task_10_2.txt')
