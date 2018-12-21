
def task_2(filename):

    strs = []

    with open(filename) as f:
        for _line in f.readlines():
            strs.append(_line.strip())

    count_2 = 0
    count_3 = 0

    for _str in strs:

        # count 2
        for _letter in _str:
            if _str.count(_letter) == 2:
                count_2 += 1
                break

        # count 3
        for _letter in _str:
            if _str.count(_letter) == 3:
                count_3 += 1
                break

    print(count_2 * count_3)


def task_2_2(filename):

    strs = []

    with open(filename) as f:
        for _line in f.readlines():
            strs.append(_line.strip())

    for i in range(len(strs)):
        for j in range(len(strs)):

            if i == j:
                continue

            count_diffs = 0

            for _l, _r in zip(strs[i], strs[j]):
                if _l != _r:
                    count_diffs += 1

                if count_diffs > 1:
                    break

            if count_diffs == 1:
                print(strs[i], strs[j])


task_2_2('task_2_1.txt')
