
import sys
import operator

class UnionFind():
    def __init__(self, n_nodes):
        """
        Union-Find data structure initialization sets each node to be its own
        parent (so that each node is in its own set/connected component), and
        to also have rank 0.
        Input - n_nodes: no of nodes
        """
        self.parents = {}
        self.ranks = {}
        self.scores = {} # nothing but size

        for node in range(1,n_nodes+1):
            self.parents[node] = node
            self.scores[node] = 1
            self.ranks[node] = 0

    def get_tree(self):
        tree = {node:[] for node in self.parents}
        for node in self.parents:
            if node != self.parents[node]:
                tree[self.parents[node]].append(node)
        return tree

    def print(self):
        print("parents",self.parents)
        print("ranks",self.ranks)
        print("scores",self.scores)
        print("tree",self.get_tree())

    def get_score(self, node):
        return self.scores[node]

    def find(self, node):
        """
        Finds which set/connected component that a node belongs to by returning
        the root node within that set.
        Technical remark: The code here implements path compression.
        Input- node: the node that we want to figure out which set/connected
            component it belongs to
        Output- the root node for the set/connected component that `node` is in
        """
        if self.parents[node] != node:
            # path compression
            self.parents[node] = self.find(self.parents[node])
        return self.parents[node]

    def union(self, node1, node2):
        """
        Merges the connected components of two nodes.
        Inputs - node1: first node - node2: second node
        """
        root1 = self.find(node1)
        root2 = self.find(node2)

        if root1 != root2:  # only merge if the connected components differ

            if self.ranks[root1] > self.ranks[root2]:
                self.parents[root2] = root1
                self.scores[root1] += self.scores[root2]
            else:
                self.parents[root1] = root2
                self.scores[root2] += self.scores[root1]
                if self.ranks[root1] == self.ranks[root2]:
                    self.ranks[root2] += 1

# main
t = int(input().strip())
for a0 in range(t):
    n,m = input().strip().split(' ')
    n,m = [int(n),int(m)]

    # initializing node degrees for prioritizing which
    # node to process first
    edges = []
    redundant_edges = []
    uf = UnionFind(n)
    edges_uf_scores = {}
    roots = set()

    for a1 in range(m):
        x,y = input().strip().split(' ')
        node1,node2 = [int(x),int(y)]
        edges.append((node1,node2))

        root1 = uf.find(node1)
        root2 = uf.find(node2)
        if(root1 == root2):
            redundant_edges.append((node1,node2))
        else:
            uf.union(node1,node2)

    # make nodes root consistent
    for (x,y) in edges:
        root1 = uf.find(x)
        roots.add(root1)
        root2 = uf.find(y)
        if root1 != root2:
            roots.add(root2)

    root_list = [(root, uf.get_score(root)) for root in roots]
    ordered_roots = sorted(root_list, reverse=True, key=lambda x: x[1])

    # uf.print()
    # print("ordered_roots",ordered_roots)
    # print("redundant_edges",redundant_edges)

    frndshp_value = 0
    group_score = 0
    memoization = {}

    group_last_step_score = 0
    prev_groups_last_score = 0
    all_groups_last_score = 0

    for (root, score) in ordered_roots:

        # print("--------(root, score)",(root, score))
        # calculation on series 1*2 + 2*3 + 4*5 + 5*6 + ...
        if score in memoization:
            group_score = memoization[score]
        else:
            group_score = 0
            for i in range(1,score):
                if i in memoization:
                    group_score += memoization[i]
                    break
                else:
                    memoization[i] = group_score
                    group_score += (i * (i+1))

            memoization[score] = group_score

        frndshp_value += (prev_groups_last_score*(score-1) + group_score)

        group_last_step_score = score*(score-1)
        all_groups_last_score += group_last_step_score
        prev_groups_last_score = all_groups_last_score

        # print("group_score",group_score)
        # print("group_last_step_score",group_last_step_score)
        # print("prev_groups_last_score",prev_groups_last_score)
        # print("all_groups_last_score",all_groups_last_score)
        # print("current_frndshp_value",frndshp_value)

    frndshp_value += (len(redundant_edges)*all_groups_last_score)

    # print("frndshp_value",frndshp_value)
    print(frndshp_value)




