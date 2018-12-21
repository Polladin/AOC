

class List:

    def __init__(self):

        self.next_nodes = []
        self.prev_nodes = []
        self.node_vals = []
        self.len = 0

    def add_afer_next_node(self, after_node, node_val):
        return self.add_node(self.next_nodes[after_node], node_val)

    def add_node(self, after_node, node_val):

        if len(self.node_vals) == 0:
            self.node_vals.append(node_val)
            self.next_nodes = [0]
            self.prev_nodes = [0]

            idx_inserted_node = 0
            self.len = 1
        else:
            self.node_vals.append(node_val)
            idx_inserted_node = len(self.node_vals) - 1

            self.prev_nodes.append(after_node)
            self.next_nodes.append(self.next_nodes[after_node])

            self.prev_nodes[self.next_nodes[after_node]] = idx_inserted_node
            self.next_nodes[after_node] = idx_inserted_node

            self.len += 1

        # print(self.next_nodes)
        # print(self.prev_nodes)
        # print(self.node_vals)
        return idx_inserted_node

    def remove_7_node(self, idx_node):

        for _ in range(7):
            idx_node = self.prev_nodes[idx_node]

        return self.remove_node(idx_node)

    def remove_node(self, idx_node):

        self.next_nodes[self.prev_nodes[idx_node]] = self.next_nodes[idx_node]
        self.prev_nodes[self.next_nodes[idx_node]] = self.prev_nodes[idx_node]

        self.len -= 1

        return self.next_nodes[idx_node], self.node_vals[idx_node]

    def print_list(self, idx_node):

        res = [self.node_vals[idx_node]]
        next_node = self.next_nodes[idx_node]

        while next_node != idx_node:
            res.append(self.node_vals[next_node])
            next_node = self.next_nodes[next_node]

        print(res)


def load_input(filename):

    with open(filename) as f:
        raw_line = f.readline()
        num_players = int(raw_line.split()[0])
        max_marable = int(raw_line.split()[6])

    return num_players, max_marable


def task_9_1(filename):

    num_players, max_marable = load_input(filename)

    field = List()

    cur_node = field.add_node(None, 0)
    num_player = 0
    player_scores = [0 for _ in range(num_players)]

    for marable_val in range(max_marable):

        if marable_val % 23 == 0:
            cur_node, score = field.remove_7_node(cur_node)
            player_scores[num_player] += marable_val + score
        else:
            cur_node = field.add_afer_next_node(cur_node, marable_val)

        num_player = (num_player + 1) % num_players

    # field.print_list(cur_node)

    # print(player_scores)
    print(max(player_scores))


task_9_1('task_9_1.txt')
