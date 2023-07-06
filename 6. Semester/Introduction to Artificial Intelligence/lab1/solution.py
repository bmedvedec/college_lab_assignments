import sys
import argparse
from collections import deque
import heapq
from heapq import heappush, heappop


class Node:
    # special method for initializing objects (Node)
    def __init__(self, state, cost):
        self.state = state
        self.cost = cost
        self.parent = None
        self.successors = []
        self.f = 0

    # special method for printing
    def __str__(self):
        return self.state

    # special methods for comparing nodes
    def __eq__(self, other):
        return self.state == other.state

    def __lt__(self, other):
        return self.state < other.state

    # special method for hashing
    def __hash__(self):
        return hash(self.state)


def read_state_space(ss):
    # read state space from file
    with open(ss, "r", encoding="utf-8") as file:
        lines = file.read().splitlines()

    # remove comments
    lines.remove("#") if "#" in lines else None

    nodes = {}  # dictionary of nodes

    # skip first two lines (start state and goal states)
    for line in lines[2:]:
        temp = line.split(":")  # split state and successors

        node = Node(temp[0], 0)  # create node with cost 0

        for succ in temp[1].strip().split(" "):  # split successors
            if succ == "":
                continue  # skip empty strings (node doesn't have successors)

            succ = succ.split(",")  # split successor state and cost
            # add successor to node
            node.successors.append(Node(succ[0], float(succ[1])))

        node.successors.sort()  # sort successors by state name
        nodes[node.state] = node  # add node to dictionary

    start_node = nodes[lines[0]]  # get start node
    goal_nodes = [nodes[state]
                  for state in lines[1].split(" ")]  # get goal nodes

    return nodes, start_node, goal_nodes


def read_heuristic(h):
    # read heuristic from file
    with open(h, "r", encoding="utf-8") as file:
        lines = file.read().splitlines()

    # return dictionary of heuristic values
    return {
        line.split(":")[0]: float(line.split(":")[1].strip()) for line in lines
    }


def expand(nodes, n):
    # expand node n and return list of successors
    return [Node(succ.state, succ.cost) for succ in nodes[n.state].successors]


def path_finder(alg, node):
    # find path from start node to goal node
    path = {
        "trail": [],
        "cost": 0,
        "length": 0
    }

    # for ucs and astar path cost sum is implemented in algorithm function
    if alg == "bfs":
        while node.parent:  # while node has parent
            path["trail"].append(node.state)  # add node to path trail
            path["cost"] += node.cost  # add node cost to path cost
            path["length"] += 1  # increment path length
            node = node.parent  # set parent node as current node

        # add last (start_node) node to path trail, add cost and increment length
        path["trail"].append(node.state)
        path["cost"] += node.cost
        path["length"] += 1

    elif alg == "ucs" or alg == "astar":
        path["cost"] = node.cost  # set path cost to goal node cost
        while node.parent:
            path["trail"].append(node.state)
            path["length"] += 1
            node = node.parent

        path["trail"].append(node.state)
        path["length"] += 1

    path["trail"].reverse()  # reverse path trail
    return path


def print_results(alg, h, found, length_visited, path):
    if alg == "astar":
        print("# A-STAR", h)
    else:
        print("#", alg.upper())

    if found:
        print("[FOUND_SOLUTION]: yes")
        print("[STATES_VISITED]:", length_visited)
        print("[PATH_LENGTH]:", path["length"])
        print("[TOTAL_COST]:", path["cost"])
        print("[PATH]:", " => ".join(path["trail"]))
    else:
        print("[FOUND_SOLUTION]: no")


def bfs(ss):
    nodes, start_node, goal_nodes = read_state_space(
        ss)  # get nodes, start node and goal nodes
    open = deque([start_node])  # queue of nodes
    visited = set()

    while open:
        n = open.popleft()  # get first node from open list
        visited.add(n.state)  # add node to visited list

        if n in goal_nodes:  # if node is goal node
            # find path from start node to goal node
            path = path_finder("bfs", n)
            print_results("bfs", None, True, len(
                visited), path)  # print results
            return

        # expand node n and return list of successors
        expanded = expand(nodes, n)

        # for every successor, add it to open list if it's not in visited list and set his parent to n
        for succ in expanded:
            if succ.state not in visited:
                succ.parent = n
                open.append(succ)

    # print results if no solution is found
    print_results("bfs", None, False, len(visited), None)


def ucs(ss):
    nodes, start_node, goal_nodes = read_state_space(ss)
    # priority queue of nodes sorted by cost, and then by state name
    open = [(start_node.cost, start_node.state, start_node)]
    visited = set()  # set of visited nodes

    while open:
        # get first node from open list ([2] for node object])
        n = heappop(open)[2]
        visited.add(n.state)  # add node to visited list

        if n in goal_nodes:
            path = path_finder("ucs", n)
            print_results("ucs", None, True, len(visited), path)
            return

        expanded = expand(nodes, n)

        for succ in expanded:
            if succ.state not in visited:
                succ.parent = n
                succ.cost = n.cost + succ.cost
                # add node to open list that is sorted by cost, and then by state name
                heappush(open, (succ.cost, succ.state, succ))

    print_results("ucs", None, False, len(visited), None)


def ucs_prop(nodes, goal_states, node):  # ucs used for checking if heuristic is optimistic
    node.cost = 0
    open = [(node.cost, node.state, node)]
    visited = set()

    while open:
        n = heappop(open)[2]
        visited.add(n.state)

        if n in goal_states:
            return n.cost

        expanded = expand(nodes, n)
        for node in expanded:
            node.parent = n
            node.cost = n.cost + node.cost
            heappush(open, (node.cost, node.state, node))


def astar(ss, h):
    nodes, start_node, goal_nodes = read_state_space(ss)
    heuristic = read_heuristic(h)

    # set f value of start node to heuristic value
    nodes[start_node.state].f = heuristic[start_node.state]
    start_node.f = start_node.cost + heuristic[start_node.state]

    open = deque([start_node])  # queue of nodes
    closed = []  # list of nodes

    while open:
        n = open.popleft()
        closed.append(n)

        if n in goal_nodes:
            path = path_finder("astar", n)
            print_results("astar", h, True, len(closed), path)
            return

        expanded = expand(nodes, n)

        for succ in expanded:
            succ.parent = n
            succ.cost = n.cost + succ.cost
            succ.f = succ.cost + heuristic[succ.state]  # set heuristic value

            # if node is in closed list and has lower cost, remove it from closed list
            if succ in closed and closed[closed.index(succ)].cost > succ.cost:
                closed.remove(succ)

            # if node is in open list and has lower cost, remove it from open list
            if succ in open and open[open.index(succ)].cost > succ.cost:
                open.remove(succ)

            open.append(succ)

        # sort qeuue by f value
        open = deque(sorted(open, key=lambda x: (x.f, x.state)))

    print_results("astar", h, False, len(closed), None)


def check_optimistic_heuristic(ss, h):
    nodes, start_node, goal_nodes = read_state_space(ss)
    heuristic = read_heuristic(h)
    print("# HEURISTIC-OPTIMISTIC", h)
    optimistic = True

    # sort nodes by state alphabetically and return dict
    nodes = dict(sorted(nodes.items()))

    for node in nodes.values():
        # get min cost from node to goal node
        min_cost = ucs_prop(nodes, goal_nodes, node)

        # check if heuristic value is less than min cost (optimistic)
        if heuristic[node.state] <= min_cost:
            print("[CONDITION]: [OK] h({}) <= h*: {} <= {}".format(node.state,
                  heuristic[node.state], float(min_cost)))
        else:
            print("[CONDITION]: [ERR] h({}) <= h*: {} <= {}".format(node.state,
                  heuristic[node.state], float(min_cost)))
            optimistic = False

    # print conclusion
    if optimistic:
        print("[CONCLUSION]: Heuristic is optimistic.")
    else:
        print("[CONCLUSION]: Heuristic is not optimistic.")


def check_consistent_heuristic(ss, h):
    nodes, start_node, goal_nodes = read_state_space(ss)
    heuristic = read_heuristic(h)
    print("# HEURISTIC-CONSISTENT", h)
    consistent = True

    # sort nodes by state alphabetically and return dict
    nodes = dict(sorted(nodes.items()))

    for node in nodes.values():  # for every node
        for succ in node.successors:  # for every successor in node
            # check if heuristic value is less than or equal to heuristic value of successor + cost (consistent)
            if heuristic[node.state] <= heuristic[succ.state] + succ.cost:
                print("[CONDITION]: [OK] h({}) <= h({}) + c: {} <= {} + {}".format(node.state,
                      succ.state, heuristic[node.state], heuristic[succ.state], succ.cost))
            else:
                print("[CONDITION]: [ERR] h({}) <= h({}) + c: {} <= {} + {}".format(node.state,
                      succ.state, heuristic[node.state], heuristic[succ.state], succ.cost))
                consistent = False

    # print conclusion
    if consistent:
        print("[CONCLUSION]: Heuristic is consistent.")
    else:
        print("[CONCLUSION]: Heuristic is not consistent.")


def main():
    # parse command line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--alg", help="Algorithm",
                        choices=["bfs", "ucs", "astar"])
    parser.add_argument("--ss", help="State space")
    parser.add_argument("--h", help="Heuristic function")
    parser.add_argument(
        "--check-optimistic", help="Check if heuristic is optimistic", action="store_true")
    parser.add_argument(
        "--check-consistent", help="Check if heuristic is consistent", action="store_true")

    args = parser.parse_args()

    alg = args.alg
    ss = args.ss
    h = args.h
    check_optimistic = args.check_optimistic
    check_consistent = args.check_consistent

    if alg == "bfs":
        bfs(ss)
    elif alg == "ucs":
        ucs(ss)
    elif alg == "astar":
        astar(ss, h)

    if check_optimistic:
        check_optimistic_heuristic(ss, h)

    if check_consistent:
        check_consistent_heuristic(ss, h)


if __name__ == "__main__":
    main()


# sources used:
# https://docs.python.org/release/3.7.4/library/
# https://www.w3schools.com/python/
# https://www.geeksforgeeks.org/python-programming-language/
