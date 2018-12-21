
def read_graph(filename):

    graph = {}

    with open(filename) as f:
        for _line in f.readlines():

            first_hop = _line.split()[1]
            next_hop = _line.split()[7]

            if first_hop not in graph:
                graph[first_hop] = []

            if next_hop not in graph:
                graph[next_hop] = []

            graph[first_hop].append(next_hop)

    for _hop in graph:
        graph[_hop] = sorted(graph[_hop])[::-1]

    # for _hop in graph:
    #     print(_hop, ' : ', graph[_hop])
    # print(graph)

    return graph


def dfs(idx, hops, graph, visited, res):

    visited[idx] = True

    for _next_hop in graph[hops[idx]]:

        next_idx = hops.index(_next_hop)

        if not visited[next_idx]:
            dfs(next_idx, hops, graph, visited, res)

    res.append(hops[idx])


def get_reversed_graph(graph):

    new_graph = {}

    for _hop in graph:

        for _other_hop in graph[_hop]:

            if _other_hop not in new_graph:
                new_graph[_other_hop] = []
            if _hop not in new_graph:
                new_graph[_hop] = []

            new_graph[_other_hop].append(_hop)

    return new_graph


def my_sort(graph):

    new_graph = get_reversed_graph(graph)

    res = []

    while len(new_graph) > 0:

        equal_hop = None

        for _hop in sorted(new_graph):
            if len(new_graph[_hop]) == 0:
                equal_hop = _hop
                break

        res.append(equal_hop)

        # for _hop_to_del in equal_hops:
        _hop_to_del = equal_hop
        del new_graph[_hop_to_del]

        for _hop in new_graph:
            if _hop_to_del in new_graph[_hop]:
                del new_graph[_hop][new_graph[_hop].index(_hop_to_del)]

    # print(res)
    print(''.join(res))
    return res


def task_7(filename):

    graph = read_graph(filename)

    order = my_sort(graph)
    rev_graph = get_reversed_graph(graph)

    workers = [[] for _ in range(5)]

    done = []

    while len(order) > 0:

        time = 0
        min_time = 0

        next_orders = []

        for _order in order:
            if len(rev_graph[_order]) == 0:
                next_orders.append(_order)

        for _order in next_orders:
            for _id_worker in range(len(workers)):
                if len(workers[_id_worker]) == 0:
                    workers[_id_worker] = [time + ord(_order) - ord('A') + 1, _order]
                    min_time = time + ord(_order) - ord('A') + 1

        # get worker with min time
        for _id_worker in range(len(workers)):
            min_time = min(min_time, workers[_id_worker][0])

        time = min_time

        for _id_worker in range(len(workers)):
            if workers[_id_worker][0] == time:
                done.append(workers[_id_worker][1])

                del rev_graph[workers[_id_worker][1]]
                for _order in rev_graph:
                    if workers[_id_worker][1] in rev_graph[_order]:
                        del rev_graph[_order][rev_graph[_order].index(workers[_id_worker][1])]


    #
    # visited = [False for _ in range(len(graph))]
    #
    # hops = sorted(list(graph.keys()))[::-1]
    # res = []
    #
    # for _idx in range(len(hops)):
    #
    #     if not visited[_idx]:
    #         dfs(_idx, hops, graph, visited, res)
    #
    # # print(res[::-1])
    # print(''.join(res[::-1]))
    #
    # for _idx in range(len(res)):


task_7('task_7_2.txt')


