
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
        self.children = {}
        self.scores = {}
        self.ranks = {}
        self.total_value = 0

        for node in range(1,n_nodes+1):
            self.parents[node] = node
            self.children[node] = set()
            self.scores[node] = 0
            self.ranks[node] = 0

    def get_value(self):
        return self.total_value

    def print_tree(self):
        print("parents",self.parents)
        print("children",self.children)
        print("ranks",self.ranks)
        print("scores",self.scores)

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
        frnd_value = 0

        if root1 != root2:  # only merge if the connected components differ

            # print("root1",root1,"root2",root2)
            # update scores
            for node in self.scores:
                if (self.parents[node] == root1) or (self.parents[node] == root2):
                    self.scores[node] += 1

            if self.ranks[root1] > self.ranks[root2]:
                self.parents[root2] = root1
                # processing for children and scores
                self.children[root1].add(root2)
                self.scores[root2] = self.scores[root1]
            else:
                self.parents[root1] = root2
                # processing for children and scores
                self.children[root2].add(root1)
                self.scores[root1] = self.scores[root2]

                if self.ranks[root1] == self.ranks[root2]:
                    self.ranks[root2] += 1

            frnd_value = sum(self.scores.values())
            self.total_value += frnd_value
        # print("level score",sum(self.scores.values()),"total",self.total_value)

        return (root1, root2, frnd_value)

# main

edges = []
redundant_edges = []
node_values = {}

t = int(input().strip())
for a0 in range(t):
    n,m = input().strip().split(' ')
    n,m = [int(n),int(m)]

    # initializing node values
    node_values = {node:0 for node in range(1,n+1)}
    for a1 in range(m):
        x,y = input().strip().split(' ')
        x,y = [int(x),int(y)]
        #updating node values to figure out what nodes to work on first
        node_values[x] += 1
        if x != y:
            node_values[y] += 1

        edges.append((int(x),int(y)))

uf = UnionFind(n)

# preparing edges in order that would give most friendship value
print(node_values)
print(edges)

def edge_sort(x):
    if node_values[x[0]] != node_values[x[1]]:
        return max(node_values[x[0]], node_values[x[1]])
    else:
        return x

edges = sorted(edges, key=edge_sort)
print("sorted",edges)
# uf.print_tree()

nof_repeated_edges = 0
for (a,b) in edges:
    # print("-------------")
    root1, root2, frnd_value = uf.union(a,b)
    if root1 == root2:
        nof_repeated_edges += 1
    # print(a,b)
    # uf.print_tree()

print(uf.get_value() + (frnd_value * nof_repeated_edges) )




