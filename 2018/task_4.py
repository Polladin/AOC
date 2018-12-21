
import pprint


def task_4(filename):

    with open(filename) as f:
        records = sorted([_line.strip() for _line in f.readlines()])

    with open('task_4_2.txt', 'w') as f:
        for _str in records:
            f.write(_str + '\n')

    # pp = pprint.PrettyPrinter(indent=4)
    # pp.pprint(records[1:20])

    guard_id = None

    # [date [0:60]]
    guards_info = []

    for _record in records:

        # Get Guard id
        if _record.split()[2] == 'Guard':
            guard_id = _record.split()[3]
            guards_info.append({'guard_id': guard_id,
                                'date_time': _record.split(']')[1:],
                                'sleep_time': [0 for _ in range(60)]})

        # Skip if no guard id is known
        if not guard_id:
            continue

        # Wake up
        if _record.split()[2] == 'wakes':

            if _record.split()[1].split(':')[0] == '00':
                time_to_wake = int(_record.split()[1].split(':')[1][:-1])
            else:
                time_to_wake = 0

            for i in range(time_to_wake, 60):
                guards_info[-1]['sleep_time'][i] = 0

        # Falls asleep
        if _record.split()[2] == 'falls':

            if _record.split()[1].split(':')[0] == '00':
                time_to_wake = int(_record.split()[1].split(':')[1][:-1])
            else:
                time_to_wake = 0

            for i in range(time_to_wake, 60):
                guards_info[-1]['sleep_time'][i] = 1

    max_sleep_guard = {'total_sleep': 0, 'id': 'None', 'max_sleep': -1, 'm': -1}
    guard_total_info = {}

    total_sleep_in_min = [0 for _ in range(60)]

    for _guard in guards_info:

        # Call max sleep time
        _guard['max_sleep_time'] = 0
        _guard['next_minute'] = -1

        sleep_time = 0
        for i in range(60):
            if _guard['sleep_time'][i] == 1:
                total_sleep_in_min[i] += 1
                sleep_time += 1
            elif sleep_time > 0:
                if sleep_time > _guard['max_sleep_time']:
                    _guard['max_sleep_time'] = sleep_time
                    _guard['next_minute'] = i
                sleep_time = 0

        _guard['max_sleep_time'] = max(_guard['max_sleep_time'], sleep_time)

        if _guard['guard_id'] not in guard_total_info:
            guard_total_info.update({_guard['guard_id']: {'max_sleep': -1, 'total_sleep': 0, 'm': -1, 'arr': []}})

        if _guard['max_sleep_time'] > guard_total_info[_guard['guard_id']]['max_sleep']:
            # print(_guard['guard_id'], ' : ', _guard['max_sleep_time'], ' : ', _guard['next_minute'])
            guard_total_info[_guard['guard_id']]['max_sleep'] = _guard['max_sleep_time']
            guard_total_info[_guard['guard_id']]['m'] = _guard['next_minute']

        guard_total_info[_guard['guard_id']]['arr'].append(_guard['sleep_time'])
        guard_total_info[_guard['guard_id']]['max_sleep'] = max(guard_total_info[_guard['guard_id']]['max_sleep'],
                                                                _guard['max_sleep_time'])
        guard_total_info[_guard['guard_id']]['total_sleep'] = guard_total_info[_guard['guard_id']]['total_sleep']\
                                                              + sum(_guard['sleep_time'])

        if guard_total_info[_guard['guard_id']]['total_sleep'] > max_sleep_guard['total_sleep']:
            max_sleep_guard['total_sleep'] = guard_total_info[_guard['guard_id']]['total_sleep']
            max_sleep_guard['max_sleep'] = guard_total_info[_guard['guard_id']]['max_sleep']
            max_sleep_guard['id'] = _guard['guard_id']
            max_sleep_guard['m'] = guard_total_info[_guard['guard_id']]['m']

        # print(_guard['guard_id'], ' : ', _guard['max_sleep_time'])

    _guard = guard_total_info[max_sleep_guard['id']]

    time_array = [0 for _ in range(60)]

    for _arr in _guard['arr']:
        for _idx in range(60):
            time_array[_idx] += _arr[_idx]

    # print('Size : ', len(_guard['arr']))
    # print('Max : ', max(time_array))
    # print('Max idx : ', time_array.index(max(time_array)))
    # # print(time_array)
    # print(max_sleep_guard)

    max_minute = total_sleep_in_min.index(max(total_sleep_in_min))

    asleep_man = {}
    max_man = {'id': '', 'cnt': -1}

    for _guard in guards_info:

        if _guard['guard_id'] not in asleep_man:
            asleep_man[_guard['guard_id']] = 0

        if _guard['sleep_time'][max_minute] == 1:
            asleep_man[_guard['guard_id']] += 1

        if asleep_man[_guard['guard_id']] > max_man['cnt']:
            max_man['id'] = _guard['guard_id']
            max_man['cnt'] = asleep_man[_guard['guard_id']]

    print('Minute : ', max_minute)
    print(max_man)

    # pp = pprint.PrettyPrinter(indent=4)
    # pp.pprint(guards_info)


task_4('task_4_1.txt')
