

def collapse(polymer):

    map_letter = {}

    for _i in range(ord('a'), ord('z') + 1):
        map_letter[chr(_i)] = chr(_i).upper()
        map_letter[chr(_i).upper()] = chr(_i)

    has_changes = True

    while has_changes:

        new_poly = ''
        has_changes = False

        idx = 1
        while idx < len(polymer):
            if map_letter[polymer[idx - 1]] == polymer[idx]:
                idx += 2
                has_changes = True
            else:
                new_poly += polymer[idx - 1]
                idx += 1

        if idx == len(polymer):
            new_poly += polymer[idx - 1]

        polymer = new_poly

    return polymer


def remove_symbol(polymer, sym):
    
    new_polymer = ''
    
    for _ch in polymer:
        if _ch != sym.upper() and _ch != sym.lower():
            new_polymer += _ch

    return new_polymer


def task_5(filename):

    with open(filename) as f:
        polymer = f.readline().strip()

    polymer = collapse(polymer)

    unique_chars = ''.join(set(polymer)).lower()

    min_val = len(polymer)

    for _ch in unique_chars:

        new_poly = remove_symbol(polymer, _ch)
        new_poly = collapse(new_poly)

        min_val = min(min_val, len(new_poly))

        # print(new_poly)
        # print(len(new_poly))

    print(min_val)

task_5('task_5_1.txt')
