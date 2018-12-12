

# Get input graph
def load_input(filename):

    dependencies = {}

    with open(filename) as f:

        for _line in f.readlines():

            first_hop = _line.split()[1]
            second_hop = _line.split()[7]

            # Initialize dependencies
            if first_hop not in dependencies:
                dependencies[first_hop] = []
            if second_hop not in dependencies:
                dependencies[second_hop] = []

            # second hop should be build after first hop
            dependencies[second_hop].append(first_hop)

    return dependencies


# topological sort
def topological_sort(dep):

    result = []

    while len(dep):

        hop_wo_dep = min([_hop for _hop in dep if len(dep[_hop]) == 0])

        # remove hops w/o any dependencies
        del dep[hop_wo_dep]

        # remove hops for other hops dependencies
        for _, _other_hop_dependency in dep.items():
            if hop_wo_dep in _other_hop_dependency:
                del _other_hop_dependency[_other_hop_dependency.index(hop_wo_dep)]

        result.append(hop_wo_dep)

    return result


#
def worker(worker_id, workers, work_id, start_time):

    # work time
    work_time = ord(work_id) - ord('A') + 1 + 60

    # [end_time, work_id]
    workers[worker_id] = [start_time + work_time, work_id, worker_id]


def get_active_tasks(dep, task_list, active_tasks):

    # result = []

    for _task in task_list:
        if len(dep[_task]) == 0:
            active_tasks.append(_task)
            del dep[_task]

    for _task in active_tasks:
        if _task in task_list:
            del task_list[task_list.index(_task)]

    # return result


def get_next_worker_with_min_time(workers):

    _workers_with_tasks = [_worker for _worker in workers if len(_worker)]

    return min(_workers_with_tasks)


def remove_from_dep(dep, work_id):

    for _, _dep_hops in dep.items():
        if work_id in _dep_hops:
            del _dep_hops[_dep_hops.index(work_id)]


def get_next_task(dep):

    result = []

    for _task, _depend in dep.items():
        if len(_depend) == 0:
            result.append(_task)

    return sorted(result)[0] if result else None


def work(dep, task_list):

    num_workers = 5

    free_workers = [_i for _i in range(num_workers)]
    workers = [[] for _ in range(num_workers)]

    cur_time = 0
    done_tasks = []
    active_tasks = []

    while len(task_list) or len(free_workers) != num_workers or len(active_tasks) > 0:

        # print('Task List : ', task_list)
        get_active_tasks(dep, task_list, active_tasks)

        while len(active_tasks) and len(free_workers):
            # Add  task to worker
            worker(free_workers[0], workers, active_tasks[0], cur_time)
            del free_workers[0]
            # Remove task from active
            del active_tasks[0]

        # Get next time
        # print(workers)
        next_free_worker = get_next_worker_with_min_time(workers)
        work_id = next_free_worker[1]
        worker_id = next_free_worker[2]

        # Add task to Done container
        done_tasks.append(work_id)

        # move time
        cur_time = next_free_worker[0]

        # done work
        remove_from_dep(dep, work_id)
        # print('Dep : ', dep)

        # free worker
        workers[worker_id] = []
        free_workers.append(worker_id)

        # update active tasks
        get_active_tasks(dep, task_list, active_tasks)
        # print('Active: ', active_tasks)

    print(cur_time)

    return done_tasks


def task_7_1(filename):

    # Get input
    dep = load_input(filename)

    # topological alphabetic sort
    sorted_hops = topological_sort(dep)

    # prepare output
    print(''.join(sorted_hops))


def task_7_2(filename):

    # Get input
    dep = load_input(filename)

    # topological alphabetic sort
    sorted_hops = topological_sort(dep)

    dep = load_input(filename)

    # Complete all tasks
    # print('Sorted : ', sorted_hops)
    res = work(dep, sorted_hops)

    #
    print(''.join(res))


# task_7_1('task_7_1.txt')
task_7_2('task_7_1.txt')

