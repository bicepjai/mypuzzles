
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
        self.roots = set()
        self.total_value = 0
        self.last_value = 0

        for node in range(1,n_nodes+1):
            self.parents[node] = node
            self.scores[node] = 1
            self.ranks[node] = 0


    def print(self):
        print("parents",self.parents)
        print("ranks",self.ranks)
        print("scores",self.scores)
        print("roots",self.roots)
        print("tree",self.get_tree())

    def get_tree(self):
        tree = {node:[] for node in self.parents}
        for node in self.parents:
            if node != self.parents[node]:
                tree[self.parents[node]].append(node)
        return tree

    def update_value(self):
        values = set()
        current_value = 0
        for root in self.roots:
            if not (self.scores[root] in values):
                current_value += (self.scores[root] * (self.scores[root]-1))
        # print("current_value",current_value)
        self.total_value += current_value
        self.last_value = current_value

    def get_value(self):
        return self.total_value

    def get_last_value(self):
        return self.last_value

    def get_parent(self, node):
        return self.parents[node]

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
                self.roots.add(root1)
                self.scores[root1] += self.scores[root2]
            else:
                self.parents[root1] = root2
                self.scores[root2] += self.scores[root1]
                self.roots.add(root2)
                if self.ranks[root1] == self.ranks[root2]:
                    self.ranks[root2] += 1

            self.update_value()

# main

t = int(input().strip())
for a0 in range(t):
    n,m = input().strip().split(' ')
    n,m = [int(n),int(m)]

    # initializing node degrees for prioritizing which
    # node to process first
    edges = []
    node_degrees = {node:0 for node in range(1,n+1)}
    uf_order_edges = UnionFind(n)
    edges_uf_scores = {}

    for a1 in range(m):
        x,y = input().strip().split(' ')
        x,y = [int(x),int(y)]

        #updating node values to figure out what nodes to work on first
        node_degrees[x] += 1
        if x != y:
            node_degrees[y] += 1
        edge = (x,y)
        if x < y:
            edge = (y,x)
        edges.append((int(x),int(y)))
        uf_order_edges.union(x,y)

    # print("node_degrees",node_degrees)
    # print("edges",edges)
    # uf_order_edges.print()

    # make nodes root consistent
    for (x,y) in edges:
        uf_order_edges.find(x)
        uf_order_edges.find(y)

    print("-----uf_order_edges------")
    # grouping edges based on parent
    ordered_edges = []
    edge_groups = {}
    for (x,y) in edges:
        root = uf_order_edges.get_parent(x)
        if root in edge_groups:
            edge_groups[root].append((x,y))
        else:
            edge_groups[root] = [(x,y)]

    # sort the group in terms of size,
    edge_groups = sorted(edge_groups.items(), reverse=True, key=lambda x: len(x[1]))
    # print("edge_groups",edge_groups)

    print("-----edge_groups------")

    # sort based on nodes & node_degrees inside each group
    def edge_sort_max_degree(x):
        return max(node_degrees[x[0]], node_degrees[x[1]]) + max(x[0],x[1])

    for (root,edges) in edge_groups:
        sorted_edge_group_nodes = sorted(edges)
        ordered_edges += sorted(sorted_edge_group_nodes, reverse=True, key=edge_sort_max_degree)

    # print("ordered_edges",ordered_edges)

    # calculation of friendship value
    uf = UnionFind(n)
    redundant_edges = []
    for (node1,node2) in ordered_edges:
        # print("-------------",(node1,node2))

        root1 = uf.find(node1)
        root2 = uf.find(node2)
        if(root1 == root2):
            redundant_edges.append((node1,node2))
        else:
            uf.union(node1,node2)
            uf.print()

    # print("redundant_edges",redundant_edges)
    redundant_edges_value = uf.get_last_value() * len(redundant_edges)
    frndshp_value = uf.get_value() + redundant_edges_value
    print("frndshp_value",frndshp_value)




