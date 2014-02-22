import java.util.*;
import java.lang.*;
import java.math.*;
import java.io.*;

class Node {
    public int suffix_node;

    public Node() {
        this.suffix_node = -1;
    }

    public static int Count = 1;
}

class Edge {
    public int first_char_index;
    public int last_char_index;
    public int end_node;
    public int start_node;

    /**
     * A given edge gets a copy of itself inserted into the table with this function.
     * It uses a linear probe technique, which means in the case of a collision,
     * we just step forward through the table until we find the first unused slot.
     */
    public void insert() {
        int i = hash(start_node, SuffixTree.T[first_char_index]);
        while (SuffixTree.EDGES[i].start_node != -1) {
            i = ++i % SuffixTree.HASH_TABLE_SIZE;
        }
        SuffixTree.EDGES[i] = this;
    }

    /**
     * Removing an edge from the hash table is a little more tricky.
     * You have to worry about creating a gap in the table that will make it impossible to find
     * other entries that have been inserted using a probe. Working around this means that
     * after setting an edge to be unused, we have to walk ahead in the table,
     * filling in gaps until all the elements can be found.
     * <p/>
     * Knuth, Sorting and Searching, Algorithm R, p. 527
     */
    public void remove() {
        int i = hash(start_node, SuffixTree.T[first_char_index]);
        while (SuffixTree.EDGES[i].start_node != start_node ||
                SuffixTree.EDGES[i].first_char_index != first_char_index)
            i = ++i % SuffixTree.HASH_TABLE_SIZE;
        for (; ;) {
            SuffixTree.EDGES[i].start_node = -1;
            int j = i;
            for (; ;) {
                i = ++i % SuffixTree.HASH_TABLE_SIZE;
                if (SuffixTree.EDGES[i].start_node == -1)
                    return;
                int r = hash(SuffixTree.EDGES[i].start_node, SuffixTree.T[SuffixTree.EDGES[i].first_char_index]);
                if (i >= r && r > j)
                    continue;
                if (r > j && j > i)
                    continue;
                if (j > i && i >= r)
                    continue;
                break;
            }
            SuffixTree.EDGES[j] = SuffixTree.EDGES[i];
        }
    }

    /**
     * The default ctor for Edge just sets start_node to the invalid value.
     * This is done to guarantee that the hash table is initially filled with unused edges.
     */
    public Edge() {
        start_node = -1;
    }

    /**
     * I create new edges in the program while walking up the set of suffixes from the active point to the endpoint.
     * Each time I create a new edge, I also add a new node for its end point.
     * The node entry is already present in the Nodes[] array, and its suffix node is set to -1
     * by the default Node() ctor, so I don't have to do anything with it at this point.
     *
     * @param init_first_char_index
     * @param init_last_char_index
     * @param parent_node
     */
    public Edge(int init_first_char_index, int init_last_char_index, int parent_node) {
        this.first_char_index = init_first_char_index;
        this.last_char_index = init_last_char_index;
        this.start_node = parent_node;
        this.end_node = Node.Count++;
    }

    /**
     * When a suffix ends on an implicit node, adding a new character means I have to split an existing edge.
     * This function is called to split an edge at the point defined by the Suffix argument.
     * The existing edge loses its parent, as well as some of its leading characters.
     * The newly created edge descends from the original parent, and now has the existing edge as a child.
     * <p/>
     * Since the existing edge is getting a new parent and starting character,
     * its hash table entry will no longer be valid.  That's why it gets removed at the start of the function.
     * After the parent and start char have been recalculated, it is re-inserted.
     * <p/>
     * The number of characters stolen from the original node and given to the new node is equal to the number
     * of characters in the suffix argument, which is last - first + 1;
     *
     * @param s
     * @return
     */
    public int splitEdge(Suffix s) {
        remove();
        Edge new_edge = new Edge(first_char_index,
                first_char_index + s.last_char_index - s.first_char_index,
                s.origin_node);
        new_edge.insert();
        SuffixTree.NODES[new_edge.end_node].suffix_node = s.origin_node;
        first_char_index += s.last_char_index - s.first_char_index + 1;
        start_node = new_edge.end_node;
        insert();
        return new_edge.end_node;
    }

    /**
     * The whole reason for storing edges in a hash table is that it makes this function fairly efficient.
     * When I want to find a particular edge leading out of a particular node, I call this function.
     * It locates the edge in the hash table, and returns a copy of it. If the edge isn't found,
     * the edge that is returned to the caller will have start_node set to -1, which is the value
     * used in the hash table to flag an unused entry.
     *
     * @param node
     * @param c
     * @return
     */
    public static Edge find(int node, int c) {
        int i = hash(node, c);
        for (; ;) {
            if (SuffixTree.EDGES[i].start_node == node)
                if (c == SuffixTree.T[SuffixTree.EDGES[i].first_char_index])
                    return SuffixTree.EDGES[i];
            if (SuffixTree.EDGES[i].start_node == -1)
                return SuffixTree.EDGES[i];
            i = ++i % SuffixTree.HASH_TABLE_SIZE;
        }
    }

    /**
     * Edges are inserted into the hash table using this hashing function.
     *
     * @param node
     * @param c
     * @return
     */
    public static int hash(int node, int c) {
        return ((node << 8) + c) % SuffixTree.HASH_TABLE_SIZE;
    }
}

class Suffix {
    public int origin_node;
    public int first_char_index;
    public int last_char_index;

    public Suffix(int node, int start, int stop) {
        this.origin_node = node;
        this.first_char_index = start;
        this.last_char_index = stop;
    }

    public boolean explicit() {
        return this.first_char_index > this.last_char_index;
    }

    public boolean implicit() {
        return last_char_index >= first_char_index;
    }

    public void canonize() {
        if (!explicit()) {
            Edge edge = Edge.find(origin_node, SuffixTree.T[first_char_index]);
            int edge_span = edge.last_char_index - edge.first_char_index;
            while (edge_span <= (last_char_index - first_char_index)) {
                first_char_index = first_char_index + edge_span + 1;
                origin_node = edge.end_node;
                if (first_char_index <= last_char_index) {
                    edge = Edge.find(edge.end_node, SuffixTree.T[first_char_index]);
                    edge_span = edge.last_char_index - edge.first_char_index;
                }
            }
        }
    }
}

class SuffixTree {
    public static final int MAX_LENGTH = 1000;

    //a prime roughly 10% larger
    public static int HASH_TABLE_SIZE = 2179;

    // This is the hash table where all the currently defined EDGES are stored.
    // You can dump out all the currently defined EDGES by iterating through the table
    // and finding EDGES whose start_node is not -1.
    public static Edge[] EDGES = new Edge[HASH_TABLE_SIZE];

    // The array of defined NODES. The count is 1 at the start
    // because the initial tree has the root node defined, with no children.
    public static Node[] NODES = new Node[MAX_LENGTH * 2];

    static {
        for (int i = 0; i < EDGES.length; i++) {
            EDGES[i] = new Edge();
        }
        for (int i = 0; i < NODES.length; i++) {
            NODES[i] = new Node();
        }
    }

    // The input buffer and character count. Please note that N is the length of the input string -1,
    // which means it denotes the maximum index in the input buffer.
    public static char[] T;
    public static int N;

    /**
     * This routine constitutes the heart of the algorithm. It is called repetitively, once for each of the prefixes
     * of the input string.  The prefix in question is denoted by the index of its last character.
     * <p/>
     * At each prefix, we start at the active point, and add a new edge denoting the new last character,
     * until we reach a point where the new edge is not needed due to the presence of an existing edge
     * starting with the new last character.  This point is the end point.
     * <p/>
     * Luckily for use, the end point just happens to be the active point for the next pass through the tree.
     * All we have to do is update it's last_char_index to indicate that it has grown by a single character,
     * and then this routine can do all its work one more time.
     *
     * @param active
     * @param last_char_index
     */
    public static void addPrefix(Suffix active, int last_char_index) {
        int parent_node;
        int last_parent_node = -1;

        for (; ;) {
            Edge edge;
            parent_node = active.origin_node;

            // Step 1 is to try and find a matching edge for the given node.
            // If a matching edge exists, we are done adding edges, so we break
            // out of this big loop.
            if (active.explicit()) {
                edge = Edge.find(active.origin_node, T[last_char_index]);
                if (edge.start_node != -1)
                    break;
            } else {
                //implicit node, a little more complicated
                edge = Edge.find(active.origin_node, T[active.first_char_index]);
                int span = active.last_char_index - active.first_char_index;
                if (T[edge.first_char_index + span + 1] == T[last_char_index])
                    break;
                parent_node = edge.splitEdge(active);
            }

            // We didn't find a matching edge, so we create a new one, add
            // it to the tree at the parent node position, and insert it
            // into the hash table.  When we create a new node, it also
            // means we need to create a suffix link to the new node from
            // the last node we visited.
            Edge new_edge = new Edge(last_char_index, N, parent_node);
            new_edge.insert();
            if (last_parent_node > 0)
                NODES[last_parent_node].suffix_node = parent_node;
            last_parent_node = parent_node;

            // This final step is where we move to the next smaller suffix
            if (active.origin_node == 0)
                active.first_char_index++;
            else
                active.origin_node = NODES[active.origin_node].suffix_node;
            active.canonize();
        }
        if (last_parent_node > 0)
            NODES[last_parent_node].suffix_node = parent_node;
        active.last_char_index++;  //Now the endpoint is the next active point
        active.canonize();
    }

    // This routine prints out the contents of the suffix tree at the end of the program by walking through
    // the hash table and printing out all used edges. It would be really great if I had some code that
    // will print out the tree in a graphical fashion, but I don't!
    public static void dump_edges(int current_n, PrintStream out) {
        out.println("\tStart \t\tEnd \t\tSuf \t\tFirst \t\tLast \t\tString");
        for (int j = 0; j < HASH_TABLE_SIZE; j++) {
            Edge s = EDGES[j];
            if (s.start_node == -1)
                continue;

            out.print("\t" + s.start_node + " " +
                    "\t\t" + s.end_node + " " +
                    "\t\t" + NODES[s.end_node].suffix_node + " " +
                    "\t\t" + s.first_char_index + " " +
                    "\t\t" + s.last_char_index + " " +
                    "\t\t");
            int top;
            if (current_n > s.last_char_index)
                top = s.last_char_index;
            else
                top = current_n;
            for (int l = s.first_char_index; l <= top; l++) {
                out.print(T[l]);
            }
            out.println();
            out.flush();
        }
    }
}

public class stringFB {
	
	public static void main(String[] args){
		String line = "mississippi";
		SuffixTree.T = line.toCharArray();
    SuffixTree.N = line.length() - 1;

    // The active point is the first non-leaf suffix in the tree.
    // We start by setting this to be the empty string at node 0.
    // The addPrefix() function will update this value after every new prefix is added.

    // The initial active prefix
    Suffix active = new Suffix(0, 0, -1);
    for (int i = 0; i <= SuffixTree.N; i++) {
        SuffixTree.addPrefix(active, i);
    }
    SuffixTree.dump_edges(SuffixTree.N, System.out);		
	}
}