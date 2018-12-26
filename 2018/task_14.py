import cProfile
import numpy as np


def task_14(pattern):

    indexes = [0, 1]
    recipes = np.zeros(500000000, dtype=np.int8) # [3, 7]
    recipes[0] = 3
    recipes[1] = 7
    _idx = 2
    p_idx = 0
    res = 0
    np_pattern = np.asarray(pattern)

    while indexes[0] != indexes[1]:

        new_recipes = recipes[indexes[0]] + recipes[indexes[1]]

        if new_recipes >= 10:
            recipes[_idx] = (new_recipes // 10)
            _idx += 1

            if _idx >= len(pattern) and np.array_equal(recipes[_idx - len(pattern):_idx], np_pattern):
                print(_idx - len(pattern))
                break

        recipes[_idx] = new_recipes % 10
        _idx += 1

        if _idx >= len(pattern) and np.array_equal(recipes[_idx - len(pattern):_idx], np_pattern):
            print(_idx - len(pattern))
            break

        indexes[0] = (indexes[0] + 1 + recipes[indexes[0]]) % _idx
        indexes[1] = (indexes[1] + 1 + recipes[indexes[1]]) % _idx

        if _idx % 10000000 == 0 or _idx % 10000001 == 0:
            print(_idx)
            # break

        # print(recipes[0:20])

        # # print(indexes)
        # # print(recipes)
        #
        # if len(recipes) >= len(pattern):
        #     if recipes[len(recipes) - len(pattern):] == pattern:
        #         res = len(recipes) - len(pattern)
        #         break

    # print(recipes)
    # print(''.join([str(_num) for _num in res]))
    # print(res)


task_14([3, 6, 0, 7, 8, 1])
# cProfile.run('task_14([3, 6, 0, 7, 8, 1])')


# task_14([5, 1, 5, 8, 9]) # first appears after 9 recipes.
# task_14([0, 1, 2, 4, 5]) # first appears after 5 recipes.
# task_14([9, 2, 5, 1, 0]) # first appears after 18 recipes.
# task_14([5, 9, 4, 1, 4]) # first appears after 2018 recipes.