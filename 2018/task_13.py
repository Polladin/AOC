import pprint
import copy


NEXT_CHOICE = ['L', 'S', 'R']
DIRECTION_TURN_MAP = {'L': {'>': '^',
                            '<': 'v',
                            '^': '<',
                            'v': '>'},
                      'S': {'>': '>',
                            '<': '<',
                            '^': '^',
                            'v': 'v'},
                      'R': {'>': 'v',
                            '<': '^',
                            '^': '>',
                            'v': '<'},}

TURN_MAP = {'\\': {'>': 'v',
                   '<': '^',
                   '^': '<',
                   'v': '>'},
            '/': {'>': '^',
                  '<': 'v',
                  '^': '>',
                  'v': '<'}}


class Cart:

    def __init__(self, x, y, direction):

        self.x = x
        self.y = y

        # Next step
        self.direction = direction

        # Next choice on a fork
        self.next_choice = 0

    def next_step(self):

        if self.direction == '>':
            self.x += 1
        elif self.direction == '<':
            self.x -= 1
        elif self.direction == 'v':
            self.y += 1
        elif self.direction == '^':
            self.y -= 1

    def next_step_direction(self, current_ch):

        if current_ch == '\\' or current_ch == '/':
            self.direction = TURN_MAP[current_ch][self.direction]
        elif current_ch == '+':
            self.direction = DIRECTION_TURN_MAP[NEXT_CHOICE[self.next_choice]][self.direction]
            self.next_choice = (self.next_choice + 1) % len(NEXT_CHOICE)


DIRECTION_MAP = {'>': 'R', '<': 'L', '^': 'T', 'v': 'B'}
DIRECTION_MAP_TO_CONNECTION = {'>': '-', '<': '-', '^': '|', 'v': '|'}


def load_input(filename):

    # Read file
    with open(filename) as f:
        raw_lines = f.readlines()

    # Initialize carts
    carts = []

    # Get field border
    y_max = len(raw_lines)
    x_max = max([len(_line) for _line in raw_lines])

    # Create field
    field = [[' ' for _ in range(x_max)] for _ in range(y_max)]

    # Fill the field
    for _y, _line in enumerate(raw_lines):
        for _x, _ch in enumerate(_line.strip('\n')):

            if _ch == '>' or _ch == '<' or _ch == '^' or _ch == 'v':
                carts.append(Cart(_x, _y, _ch))
                field[_y][_x] = DIRECTION_MAP_TO_CONNECTION[_ch]
            else:
                field[_y][_x] = _ch

    # for _line in field:
    #     print(''.join(_line))

    return field, carts


def find_collision(carts, current_cart_id):

    for _cart_id, _cart in enumerate(carts):

        if _cart_id == current_cart_id:
            continue

        if _cart.x == carts[current_cart_id].x and \
           _cart.y == carts[current_cart_id].y:
            return True, (_cart.x, _cart.y), _cart_id

    return False, None, None


def draw_field(field, carts):

    tmp_field = copy.deepcopy(field)

    for _cart in carts:
        tmp_field[_cart.y][_cart.x] = _cart.direction

    for _line in tmp_field:
        print(''.join(_line))


def task_13(filename):

    # Load input
    field, carts = load_input(filename)

    is_collision_found = False
    collision_coords = None

    # Endless loop for carts evolution
    while len(carts) > 1:

        # Sort carts
        carts = sorted(carts, key=lambda _cart: (_cart.y, _cart.x))

        # draw_field(field, carts)
        next_step_carts = []

        # Do step foe a cart
        for _card_id, _cart in enumerate(carts):

            # Cart already was crashed
            is_collision_found, _, _ = find_collision(carts, _card_id)
            if is_collision_found:
                continue

            # Move cart
            _cart.next_step()

            # Calc next step direction
            _cart.next_step_direction(field[_cart.y][_cart.x])

            # Is collision
            is_collision_found, collision_coords, cart_id_collision = find_collision(carts, _card_id)

            if not is_collision_found:
                next_step_carts.append(_cart)
            else:
                if carts[cart_id_collision] in next_step_carts:
                    del next_step_carts[next_step_carts.index(carts[cart_id_collision])]

        carts = next_step_carts

    # print('collision_coords :', collision_coords)
    print('Last cart :', carts[0].x, carts[0].y)


task_13('task_13_2.txt')


