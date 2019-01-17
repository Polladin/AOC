
def task_22():

    depth = 8787
    target = (725, 725)

    # depth = 510
    # target = (10, 10)
    # # target = (15, 15)

    result = 0

    field = [[0 for _ in range(target[1] + 1)] for _ in range(target[0] + 1)]
    scores = [[0 for _ in range(target[1] + 1)] for _ in range(target[0] + 1)]

    for _x in range(target[0] + 1):

        # print('x:', _x)

        for _y in range(target[1] + 1):

            if _x == 0 and _y == 0:
                field[_x][_y] = 0
            elif _x == target[0] and _y == target[1]:
                field[_x][_y] = 0
            elif _y == 0:
                field[_x][_y] = (_x * 16807 + depth) % 20183
            elif _x == 0:
                field[_x][_y] = (_y * 48271 + depth) % 20183
            else:
                field[_x][_y] = (field[_x - 1][_y] * field[_x][_y - 1] + depth) % 20183

            scores[_x][_y] = field[_x][_y] % 3
            result += scores[_x][_y]

    # for _line in field:
    #     print(_line)
    #
    # for _line in scores:
    #     print(_line)
    #
    # for _y in range(target[1] + 1):
    #     _line_str = ''
    #     for _x in range(target[0] + 1):
    #         if scores[_x][_y] == 0:
    #             _line_str += '.'
    #         elif scores[_x][_y] == 1:
    #             _line_str += '='
    #         else:
    #             _line_str += '|'
    #     print(_line_str)

    print(result)


task_22()
