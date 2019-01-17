
def load_input(filename):

    points = []

    with open(filename) as f:
        for _line in f.readlines():
            points.append([int(_p.strip()) for _p in _line.split(',')])

    return points


def get_manh_dist(p1, p2):

    dist = 0

    for i in range(len(p1)):
        dist += abs(p2[i] - p1[i])

    return dist


def is_any_common_point_in_clusters(cluster_1, cluster_2, points):

    for _point_cluster_1 in cluster_1:

        for _point_cluster_2 in cluster_2:

            if get_manh_dist(points[_point_cluster_1], points[_point_cluster_2]) <= 3:
                return True

    return False


def merge_clusters(clusters, points):

    new_clusters = []

    while len(clusters):

        common_point_found = False
        cur_cluster = clusters[0]

        compare_with_cluster = 1

        while compare_with_cluster < len(clusters):

            # Is any points from cluster 1 has common point with cluster 2
            if is_any_common_point_in_clusters(cur_cluster, clusters[compare_with_cluster], points):

                # Merge clusters
                new_clusters.append([*cur_cluster, *clusters[compare_with_cluster]])

                # Remove old clusters
                del clusters[compare_with_cluster]
                del clusters[0]

                common_point_found = True

                break

            # Clusters have not any common points
            compare_with_cluster += 1

        if not common_point_found:
            new_clusters.append(cur_cluster)
            del clusters[0]

    return new_clusters


def task_25(filename):

    points = load_input(filename)

    clusters = [[_idx] for _idx in range(len(points))]

    while True:

        count_clusters = len(clusters)
        print('Count clusters : ', count_clusters)

        clusters = merge_clusters(clusters, points)

        if count_clusters == len(clusters):
            break

    print(len(clusters))


# task_25('task_25_1.txt')
# task_25('task_25_2.txt')
# task_25('task_25_3.txt')
# task_25('task_25_4.txt')
task_25('task_25_5.txt')
