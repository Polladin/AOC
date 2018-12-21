

def task_1(fname):

    res = 0
    collections = set()
    collections.add(0)

    nums = []

    with open(fname) as f:
        for _line in f.readlines():
            nums.append(int(_line))

    idx = 0
    while True:

        res += nums[idx]
        idx = (idx + 1) % len(nums)

        if res in collections:
            print(res)
            break

        collections.add(res)

    # print(res)


task_1('task_1_2.txt')
