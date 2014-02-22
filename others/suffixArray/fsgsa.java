
import java.util.*;

public class fsgsa {
		
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		sc.nextLine();

		String[] text = new String[n];
		
		for(int i=0;i<n;i++) {
			text[i] = sc.nextLine();
		}
		System.out.println(Arrays.toString(text));		

		GeneralizedSuffixTree gst = new GeneralizedSuffixTree(text);
		TestHelper.dumpEdges(gst.getSuffixTree());
	}
}

class TestHelper {
    public static void dumpEdges(SuffixTree suffixTree) {
        System.out.println("\tEdge \t\tStart \t\tEnd \t\tSuf \t\tFirst \t\tLast \t\tString");
        Queue<Node> queue = new LinkedList<Node>();

        queue.add(suffixTree.getRootNode());
        dumpEdges(suffixTree, queue);
    }

    private static void dumpEdges(SuffixTree suffixTree, Queue<Node> queue) {
        while (!queue.isEmpty()) {
            Node node = queue.remove();
            for (Edge edge : node.getEdges()) {
                Node suffixNode = edge.getEndNode().getSuffixNode();
                System.out.print("\t" + edge + " " +
                        "\t\t" + edge.getStartNode() + " " +
                        "\t\t" + edge.getEndNode() + " " +
                        "\t\t" + ((suffixNode == null) ? "-1" : suffixNode) + " " +
                        "\t\t" + edge.getBeginIndex() + " " +
                        "\t\t" + edge.getEndIndex() + " " +
                        "\t\t");

                System.out.println(suffixTree.getText().substring(edge.getBeginIndex(), edge.getEndIndex()+1));

                if (edge.getEndNode() != null)
                    queue.add(edge.getEndNode());
            }
        }
    }
}

class GeneralizedSuffixTree {
    // SOH - START OF HEADING
    public static final char TERMINATOR1 = '\u0001';
    // STX - START OF TEXT
    public static final char TERMINATOR2 = '\u0002';

    // unallocated Unicode space
    public static final char TERMINATORS_RANGE = '\ud800';

    private String texts[];
    private char terminators[];

    private String generalized;
    private SuffixTree suffixTree;

    public GeneralizedSuffixTree(String text1, String text2) {
        this(text1, text2, TERMINATOR1, TERMINATOR2);
    }

    public GeneralizedSuffixTree(String text1, String text2, char terminator1, char terminator2) {
        this(new String[]{text1, text2}, new char[]{terminator1, terminator2});
    }

    public GeneralizedSuffixTree(String texts[]) {
        this(texts, getDefaultTerminators(texts.length));
    }

    public GeneralizedSuffixTree(String texts[], char terminators[]) {
        this.texts = texts;
        this.terminators = terminators;

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < texts.length; i++) {
            sb.append(texts[i]);
            sb.append(terminators[i]);
        }
        generalized = sb.toString();
        suffixTree = new SuffixTree(generalized);
        fixSpanSuffixes(suffixTree.getRootNode());
    }

    private void fixSpanSuffixes(Node node) {
        for (Edge edge : node.getEdges()) {
            for (int i = 0; i < texts.length; i++) {
                if ((edge.getBeginIndex() <= getGeneralizedSubstringLength(i)) &&
                        (edge.getEndIndex() > getGeneralizedSubstringLength(i))) {

                    edge.setEndIndex(getGeneralizedSubstringLength(i));
                    continue;
                }
            }
            fixSpanSuffixes(edge.getEndNode());
        }
    }

    private int getGeneralizedSubstringLength(int n) {
        int length = 0;
        for (int i = 0; i <= n; i++) {
            length += texts[i].length() + 1;
        }
        return length - 1;
    }

    public String getLcsAsString() {
        CommonSubstr commonSubstr = getLcs();
        return texts[0].substring(commonSubstr.beginIndexes[0], commonSubstr.endIndexes[0] + 1);
    }

    public CommonSubstr getLcs() {
        int beginIndexes[] = new int[texts.length];
        int endIndexes[] = new int[texts.length];
        initBeginEndIndexes(beginIndexes, endIndexes);
        return getLcs(beginIndexes, endIndexes);
    }

    private void initBeginEndIndexes(int beginIndexes[], int endIndexes[]) {
        beginIndexes[0] = 0;
        endIndexes[0] = texts[0].length();

        for(int i=1; i<texts.length; i++) {
            beginIndexes[i] = endIndexes[i-1]+1;
            endIndexes[i] = beginIndexes[i]+texts[i].length();
        }
    }

    public int[] getDefaultBeginIndexes() {
        int beginIndexes[] = new int[texts.length];
        initBeginEndIndexes(beginIndexes, new int[texts.length]);
        return beginIndexes;
    }

    public int[] getDefaultEndIndexes() {
        int endIndexes[] = new int[texts.length];
        initBeginEndIndexes(new int[texts.length], endIndexes);
        return endIndexes;
    }

    public static char[] getDefaultTerminators(int length) {
        char terminators[] = new char[length];
        for(int i=0; i<length; i++)
            terminators[i] = (char)(TERMINATORS_RANGE + i);
        return terminators;
    }

    public int[] incIndexes(int indexes[]) {
        for(int i=0; i<texts.length; i++)
            indexes[i]++;
        return indexes;
    }

    public CommonSubstr getLcs(int beginIndexes[], int endIndexes[]) {
        // calculate LCS status for each node: strings count, suffix length
        Map<Node, LCSNodeStatus> statuses = new HashMap<Node, LCSNodeStatus>();
        getLCSNodeStatus(suffixTree.getRootNode(), 0, statuses);

        CommonSubstr commonSubstr = getLcs(beginIndexes, endIndexes, statuses);
        statuses.clear();

        return commonSubstr;
    }

    private CommonSubstr getLcs(int beginIndexes[], int endIndexes[], Map<Node, LCSNodeStatus> statuses) {
        int max = 0;
        int foundBeginIndexes[] = null;

        for (LCSNodeStatus status : statuses.values()) {
            if ((status.getHeight() > 0) && (status.isAllStrings()) && (max <= status.getHeight())) {
                Node node = status.getNode();
                int workingBeginIndexes[] = initFoundBeginIndexes();

                updateFoundBeginIndexes(beginIndexes, endIndexes, node, status.getHeight(),
                        statuses, workingBeginIndexes);

                if (verifyFoundBeginIndexes(workingBeginIndexes)) {
                    foundBeginIndexes = workingBeginIndexes;
                    max = status.getHeight();
                }
            }
        }

        if (foundBeginIndexes == null)
            return null;

        return new CommonSubstr(foundBeginIndexes, max);
    }

    private int[] initFoundBeginIndexes() {
        int beginIndexes[] = new int[texts.length];
        for(int i=0; i<texts.length; i++)
            beginIndexes[i] = Integer.MAX_VALUE;
        return beginIndexes;
    }

    private void updateFoundBeginIndexes(int beginIndexes[], int endIndexes[], Node node, int height,
                                            Map<Node, LCSNodeStatus> statuses, int[] foundBeginIndexes) {
        for (Edge edge : node.getEdges()) {
            LCSNodeStatus nodeStatus = statuses.get(edge.getEndNode());
            if ((nodeStatus != null) && nodeStatus.isAllStrings()) {
                updateFoundBeginIndexes(beginIndexes, endIndexes, edge.getEndNode(),
                            height + getEdgeHeight(edge), statuses, foundBeginIndexes);
            } else {
                int stringNumber = getEdgeStringNumber(edge);
                int beginIndex = edge.getBeginIndex() - height;

                if ((beginIndex < endIndexes[stringNumber]) &&
                        (beginIndex >= beginIndexes[stringNumber]) &&
                        (foundBeginIndexes[stringNumber] > beginIndex)) {

                    foundBeginIndexes[stringNumber] = beginIndex;
                }
            }
        }
    }

    private boolean verifyFoundBeginIndexes(int[] beginIndexes) {
        for(int i=0; i<texts.length; i++)
            if (beginIndexes[i] == Integer.MAX_VALUE)
                return false;
        return true;
    }

    public List<CommonSubstr> diff() {
        // calculate LCS status for each node: strings count, suffix length
        Map<Node, LCSNodeStatus> statuses = new HashMap<Node, LCSNodeStatus>();
        getLCSNodeStatus(suffixTree.getRootNode(), 0, statuses);

        List<CommonSubstr> list = diff(getDefaultBeginIndexes(), getDefaultEndIndexes(), statuses);
        statuses.clear();

        return list;
    }

    private List<CommonSubstr> diff(int beginIndexes[], int endIndexes[], Map<Node, LCSNodeStatus> statuses) {
        CommonSubstr commonSubstr = getLcs(beginIndexes, endIndexes, statuses);
        if (commonSubstr == null)
            return new LinkedList<CommonSubstr>();

        List<CommonSubstr> prev = diff(beginIndexes, commonSubstr.beginIndexes, statuses);
        List<CommonSubstr> next = diff(incIndexes(commonSubstr.endIndexes), endIndexes, statuses);

        prev.add(commonSubstr);
        if (next != null)
            prev.addAll(next);
        return prev;
    }

    private int getEdgeStringNumber(Edge edge) {
        for (int i = 0; i < texts.length; i++) {
            if (edge.getEndIndex() <= getGeneralizedSubstringLength(i))
                return i;
        }
        return -1;
    }

    private int getEdgeHeight(Edge edge) {
        return edge.getEndIndex() - edge.getBeginIndex();
    }

    private int getEdgeHeightForNodeStatus(Edge edge) {
        int result = getEdgeHeight(edge);

        int stringNumber = getEdgeStringNumber(edge);
        if (edge.getEndIndex() != getGeneralizedSubstringLength(stringNumber))
            result += 1;
        return result;
    }

    private LCSNodeStatus getLCSNodeStatus(Node node, int height, Map<Node, LCSNodeStatus> statuses) {
        LCSNodeStatus nodeStatus = new LCSNodeStatus(node, height);
        if (node.getEdges().size() == 0) {
            return nodeStatus;
        }

        for (Edge edge : node.getEdges()) {
            LCSNodeStatus status = getLCSNodeStatus(edge.getEndNode(),
                    height + getEdgeHeightForNodeStatus(edge), statuses);

            status.addString(getEdgeStringNumber(edge));
            nodeStatus.mergeStatus(status);
        }
        statuses.put(node, nodeStatus);
        return nodeStatus;
    }

    public String getGeneralizedString() {
        return generalized;
    }

    public SuffixTree getSuffixTree() {
        return suffixTree;
    }


    /**
     * Suffix Tree Node Status for Longest Common Substring (LCS)
     */
    private class LCSNodeStatus {
        private Node node;
        private boolean allStrings;
        private Set<Integer> stringSet;
        private int height;

        public LCSNodeStatus(Node node, int height) {
            this.node = node;
            allStrings = false;
            stringSet = new HashSet<Integer>();

            this.height = height;
        }

        public boolean isAllStrings() {
            if (!allStrings) {
                for (int i = 0; i < texts.length; i++) {
                    if (!stringSet.contains(i))
                        return false;
                }
                allStrings = true;
            }
            return allStrings;
        }

        public void addString(int number) {
            if (!isAllStrings()) {
                if (!stringSet.contains(number))
                    stringSet.add(number);
            }
        }

        public int getHeight() {
            return height;
        }

        public Node getNode() {
            return node;
        }

        public void mergeStatus(LCSNodeStatus status) {
            allStrings |= status.allStrings;
            if (!isAllStrings()) {
                stringSet.addAll(status.stringSet);
            }
        }
    }


    public class CommonSubstr {
        private int beginIndexes[];
        private int endIndexes[];

        public CommonSubstr(int beginIndexes[], int endIndexes[]) {
            this.beginIndexes = beginIndexes;
            this.endIndexes = endIndexes;
        }

        public CommonSubstr(int beginIndexes[], int max) {
            this.beginIndexes = beginIndexes;
            endIndexes = new int[texts.length];
            for(int i=0; i<texts.length; i++) {
                endIndexes[i] = beginIndexes[i] + max - 1;
            }
        }

        public int[] getBeginIndexes() {
            return beginIndexes;
        }

        public int[] getEndIndexes() {
            return endIndexes;
        }
    }
}

class SuffixTree {
    private String text;
    private Node root;
    private int nodesCount;

    public SuffixTree(String text) {
        nodesCount = 0;
        this.text = text;
        root = new Node(this, null);

        Suffix active = new Suffix(root, 0, -1);
        for (int i = 0; i < text.length(); i++) {
            addPrefix(active, i);
        }
    }

    private void addPrefix(Suffix active, int endIndex) {
        Node lastParentNode = null;
        Node parentNode;

        while (true) {
            Edge edge;
            parentNode = active.getOriginNode();

            // Step 1 is to try and find a matching edge for the given node.
            // If a matching edge exists, we are done adding edges, so we break out of this big loop.
            if (active.isExplicit()) {
                edge = active.getOriginNode().findEdge(text.charAt(endIndex));
                if (edge != null)
                    break;
            } else {
                //implicit node, a little more complicated
                edge = active.getOriginNode().findEdge(text.charAt(active.getBeginIndex()));
                int span = active.getSpan();
                if (text.charAt(edge.getBeginIndex() + span + 1) == text.charAt(endIndex))
                    break;
                parentNode = edge.splitEdge(active);
            }

            // We didn't find a matching edge, so we create a new one, add it to the tree at the parent node position,
            // and insert it into the hash table.  When we create a new node, it also means we need to create
            // a suffix link to the new node from the last node we visited.
            Edge newEdge = new Edge(endIndex, text.length() - 1, parentNode);
            newEdge.insert();
            updateSuffixNode(lastParentNode, parentNode);
            lastParentNode = parentNode;

            // This final step is where we move to the next smaller suffix
            if (active.getOriginNode() == root)
                active.incBeginIndex();
            else
                active.changeOriginNode();
            active.canonize();
        }
        updateSuffixNode(lastParentNode, parentNode);
        active.incEndIndex();   //Now the endpoint is the next active point
        active.canonize();
    }

    private void updateSuffixNode(Node node, Node suffixNode) {
        if ((node != null) && (node != root)) {
            node.setSuffixNode(suffixNode);
        }
    }

    public int getNewNodeNumber() {
        return nodesCount++;
    }

    public boolean contains(String str) {
        return indexOf(str) >= 0;
    }

    public int indexOf(String str) {
        if (str.length() == 0)
            return -1;

        int index = -1;
        Node node = root;

        int i = 0;
        while (i < str.length()) {
            if ((node == null) || (i == text.length()))
                return -1;

            Edge edge = node.findEdge(str.charAt(i));
            if (edge == null)
                return -1;

            index = edge.getBeginIndex() - i;
            i++;

            for (int j = edge.getBeginIndex() + 1; j <= edge.getEndIndex(); j++) {
                if (i == str.length())
                    break;
                if (text.charAt(j) != str.charAt(i))
                    return -1;
                i++;
            }
            node = edge.getEndNode();
        }
        return index;
    }

    public String getText() {
        return text;
    }

    public Node getRootNode() {
        return root;
    }
}

class Suffix {
    private Node originNode;
    private int beginIndex;
    private int endIndex;

    public Suffix(Node originNode, int beginIndex, int endIndex) {
        this.originNode = originNode;
        this.beginIndex = beginIndex;
        this.endIndex = endIndex;
    }

    public boolean isExplicit() {
        return beginIndex > endIndex;
    }

    public boolean isImplicit() {
        return endIndex >= beginIndex;
    }

    public void canonize() {
        if (!isExplicit()) {
            Edge edge = originNode.findEdge(originNode.charAt(beginIndex));

            int edgeSpan = edge.getSpan();
            while (edgeSpan <= getSpan()) {
                beginIndex += edgeSpan + 1;
                originNode = edge.getEndNode();
                if (beginIndex <= endIndex) {
                    edge = edge.getEndNode().findEdge(originNode.charAt(beginIndex));
                    edgeSpan = edge.getSpan();
                }
            }
        }
    }

    public int getSpan() {
        return endIndex - beginIndex;
    }

    public Node getOriginNode() {
        return originNode;
    }

    public int getBeginIndex() {
        return beginIndex;
    }

    public void incBeginIndex() {
        beginIndex++;
    }

    public void changeOriginNode() {
        originNode = originNode.getSuffixNode();
    }

    public int getEndIndex() {
        return endIndex;
    }

    public void incEndIndex() {
        endIndex++;
    }
}

class Node {
    private SuffixTree suffixTree;

    private Node suffixNode;
    private Map<Character, Edge> edges;
    private int name;

    public Node(Node node, Node suffixNode) {
        this(node.suffixTree, suffixNode);
    }

    public Node(SuffixTree suffixTree, Node suffixNode) {
        this.suffixTree = suffixTree;
        name = suffixTree.getNewNodeNumber();

        this.suffixNode = suffixNode;
        edges = new HashMap<Character, Edge>();
    }

    public char charAt(int index) {
        return suffixTree.getText().charAt(index);
    }

    public void addEdge(int charIndex, Edge edge) {
        edges.put(charAt(charIndex), edge);
    }

    public void removeEdge(int charIndex) {
        edges.remove(charAt(charIndex));
    }

    public Edge findEdge(char ch) {
        return edges.get(ch);
    }

    public Node getSuffixNode() {
        return suffixNode;
    }

    public void setSuffixNode(Node suffixNode) {
        this.suffixNode = suffixNode;
    }

    public Collection<Edge> getEdges() {
        return edges.values();
    }

    @Override
    public String toString() {
        return ((Integer) name).toString();
    }

    @Override
    public int hashCode() {
        return name;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if ((obj == null) || (obj.getClass() != this.getClass()))
            return false;

        Node node = (Node) obj;
        return name == node.name;
    }
}

class Edge {
    private int beginIndex;     // can't be changed
    private int endIndex;
    private Node startNode;
    private Node endNode;       // can't be changed, could be used as edge id

    // each time edge is created, a new end node is created
    public Edge(int beginIndex, int endIndex, Node startNode) {
        this.beginIndex = beginIndex;
        this.endIndex = endIndex;
        this.startNode = startNode;
        this.endNode = new Node(startNode, null);
    }

    public Node splitEdge(Suffix suffix) {
        remove();
        Edge newEdge = new Edge(beginIndex, beginIndex + suffix.getSpan(), suffix.getOriginNode());
        newEdge.insert();
        newEdge.endNode.setSuffixNode(suffix.getOriginNode());
        beginIndex += suffix.getSpan() + 1;
        startNode = newEdge.getEndNode();
        insert();
        return newEdge.getEndNode();
    }

    public void insert() {
        startNode.addEdge(beginIndex, this);
    }

    public void remove() {
        startNode.removeEdge(beginIndex);
    }

    public int getSpan() {
        return endIndex - beginIndex;
    }

    public int getBeginIndex() {
        return beginIndex;
    }

    public int getEndIndex() {
        return endIndex;
    }

    public void setEndIndex(int endIndex) {
        this.endIndex = endIndex;
    }

    public Node getStartNode() {
        return startNode;
    }

    public void setStartNode(Node startNode) {
        this.startNode = startNode;
    }

    public Node getEndNode() {
        return endNode;
    }

    @Override
    public String toString() {
        return endNode.toString();
    }
}


