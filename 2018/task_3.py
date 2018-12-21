import numpy as np

class Claim:

    def __init__(self, id, ldrop, tdrop, width, height ):

        self.id = id
        self.ldrop = ldrop
        self.tdrop = tdrop
        self.width = width
        self.height = height

    def __str__(self):

        return 'id: {} ldrop: {} tdrop: {} width: {} height: {}'\
            .format(self.id, self.ldrop, self.tdrop, self.width, self.height)


class Posision:

    def __init__(self, x, y):

        self.x = x
        self.y = y


def task_3_1(filename):

    claims = []

    with open(filename) as f:
        for _line in f.readlines():

            args = _line.split()
            # print(args)
            claims.append(Claim(id=args[0][1:],
                                ldrop=int(args[2].split(',')[0]),
                                tdrop=int(args[2].split(',')[1][:-1]),
                                width=int(args[3].split('x')[0]),
                                height=int(args[3].split('x')[1])))

    inches = np.zeros((1000, 1000))

    for _claim in claims:

        for i in range(_claim.ldrop, _claim.ldrop + _claim.width):
            for j in range(_claim.tdrop, _claim.tdrop + _claim.height):
                inches[i][j] += 1

    # used_inches = 0
    #
    # for i in range(1000):
    #     for j in range(1000):
    #         if inches[i][j] > 1:
    #             used_inches += 1
    #
    # print(used_inches)

    for _claim in claims:

        is_no_overlap = True

        for i in range(_claim.ldrop, _claim.ldrop + _claim.width):
            for j in range(_claim.tdrop, _claim.tdrop + _claim.height):
                if inches[i][j] > 1:
                    is_no_overlap = False

        if is_no_overlap:
            print(_claim)


task_3_1('task_3_1.txt')
