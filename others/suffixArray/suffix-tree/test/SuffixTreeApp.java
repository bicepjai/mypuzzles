package com.blogspot.illyakeeplearning.suffixtree;

public class SuffixTreeApp {
    public static void main(String [] args) {
        SuffixTree st = new SuffixTree("package com.blogspot.illyakeeplearning.suffixtree;\n" +
                "\n" +
                "public class SuffixTree {\n" +
                "    private String text;\n" +
                "    private Node root;\n" +
                "    private int nodesCount;\n" +
                "\n" +
                "    public SuffixTree(String text) {\n" +
                "        nodesCount = 0;\n" +
                "        this.text = text;\n" +
                "        root = new Node(this, null);\n" +
                "\n" +
                "        Suffix active = new Suffix(root, 0, -1);\n" +
                "        for (int i = 0; i < text.length(); i++) {\n" +
                "            addPrefix(active, i);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    private void addPrefix(Suffix active, int endIndex) {\n" +
                "        Node lastParentNode = null;\n" +
                "        Node parentNode;\n" +
                "\n" +
                "        while (true) {\n" +
                "            Edge edge;\n" +
                "            parentNode = active.getOriginNode();\n" +
                "\n" +
                "            // Step 1 is to try and find a matching edge for the given node.\n" +
                "            // If a matching edge exists, we are done adding edges, so we break out of this big loop.\n" +
                "            if (active.isExplicit()) {\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(endIndex));\n" +
                "                if (edge != null)\n" +
                "                    break;\n" +
                "            } else {\n" +
                "                //implicit node, a little more complicated\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(active.getBeginIndex()));\n" +
                "                int span = active.getSpan();\n" +
                "                if (text.charAt(edge.getBeginIndex() + span + 1) == text.charAt(endIndex))\n" +
                "                    break;\n" +
                "                parentNode = edge.splitEdge(active);\n" +
                "            }\n" +
                "\n" +
                "            // We didn't find a matching edge, so we create a new one, add it to the tree at the parent node position,\n" +
                "            // and insert it into the hash table.  When we create a new node, it also means we need to create\n" +
                "            // a suffix link to the new node from the last node we visited.\n" +
                "            Edge newEdge = new Edge(endIndex, text.length() - 1, parentNode);\n" +
                "            newEdge.insert();\n" +
                "            updateSuffixNode(lastParentNode, parentNode);\n" +
                "            lastParentNode = parentNode;\n" +
                "\n" +
                "            // This final step is where we move to the next smaller suffix\n" +
                "            if (active.getOriginNode() == root)\n" +
                "                active.incBeginIndex();\n" +
                "            else\n" +
                "                active.changeOriginNode();\n" +
                "            active.canonize();\n" +
                "        }\n" +
                "        updateSuffixNode(lastParentNode, parentNode);\n" +
                "        active.incEndIndex();   //Now the endpoint is the next active point\n" +
                "        active.canonize();\n" +
                "    }\n" +
                "\n" +
                "    private void updateSuffixNode(Node node, Node suffixNode) {\n" +
                "        if ((node != null) && (node != root)) {\n" +
                "            node.setSuffixNode(suffixNode);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    public int getNewNodeNumber() {\n" +
                "        return nodesCount++;\n" +
                "    }\n" +
                "\n" +
                "    public boolean contains(String str) {\n" +
                "        return indexOf(str) >= 0;\n" +
                "    }\n" +
                "\n" +
                "    public int indexOf(String str) {\n" +
                "        if (str.length() == 0)\n" +
                "            return -1;\n" +
                "\n" +
                "        int index = -1;\n" +
                "        Node node = root;\n" +
                "\n" +
                "        int i = 0;\n" +
                "        while (i<str.length()) {\n" +
                "            if ((node == null) || (i == text.length()))\n" +
                "                return -1;\n" +
                "\n" +
                "            Edge edge = node.findEdge(str.charAt(i));\n" +
                "            if (edge == null)\n" +
                "                return -1;\n" +
                "\n" +
                "            index = edge.getBeginIndex()-i;\n" +
                "            i++;\n" +
                "\n" +
                "            for(int j=edge.getBeginIndex()+1; j<=edge.getEndIndex(); j++) {\n" +
                "                if (i == str.length())\n" +
                "                    break;\n" +
                "                if (text.charAt(j) != str.charAt(i))\n" +
                "                    return -1;\n" +
                "                i++;\n" +
                "            }\n" +
                "            node = edge.getEndNode();\n" +
                "        }\n" +
                "        return index;\n" +
                "    }\n" +
                "\n" +
                "    public String getText() {\n" +
                "        return text;\n" +
                "    }\n" +
                "\n" +
                "    public Node getRootNode() {\n" +
                "        return root;\n" +
                "    }\n" +
                "}\n" +
                "package com.blogspot.illyakeeplearning.suffixtree;\n" +
                "\n" +
                "public class SuffixTree {\n" +
                "    private String text;\n" +
                "    private Node root;\n" +
                "    private int nodesCount;\n" +
                "\n" +
                "    public SuffixTree(String text) {\n" +
                "        nodesCount = 0;\n" +
                "        this.text = text;\n" +
                "        root = new Node(this, null);\n" +
                "\n" +
                "        Suffix active = new Suffix(root, 0, -1);\n" +
                "        for (int i = 0; i < text.length(); i++) {\n" +
                "            addPrefix(active, i);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    private void addPrefix(Suffix active, int endIndex) {\n" +
                "        Node lastParentNode = null;\n" +
                "        Node parentNode;\n" +
                "\n" +
                "        while (true) {\n" +
                "            Edge edge;\n" +
                "            parentNode = active.getOriginNode();\n" +
                "\n" +
                "            // Step 1 is to try and find a matching edge for the given node.\n" +
                "            // If a matching edge exists, we are done adding edges, so we break out of this big loop.\n" +
                "            if (active.isExplicit()) {\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(endIndex));\n" +
                "                if (edge != null)\n" +
                "                    break;\n" +
                "            } else {\n" +
                "                //implicit node, a little more complicated\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(active.getBeginIndex()));\n" +
                "                int span = active.getSpan();\n" +
                "                if (text.charAt(edge.getBeginIndex() + span + 1) == text.charAt(endIndex))\n" +
                "                    break;\n" +
                "                parentNode = edge.splitEdge(active);\n" +
                "            }\n" +
                "\n" +
                "            // We didn't find a matching edge, so we create a new one, add it to the tree at the parent node position,\n" +
                "            // and insert it into the hash table.  When we create a new node, it also means we need to create\n" +
                "            // a suffix link to the new node from the last node we visited.\n" +
                "            Edge newEdge = new Edge(endIndex, text.length() - 1, parentNode);\n" +
                "            newEdge.insert();\n" +
                "            updateSuffixNode(lastParentNode, parentNode);\n" +
                "            lastParentNode = parentNode;\n" +
                "\n" +
                "            // This final step is where we move to the next smaller suffix\n" +
                "            if (active.getOriginNode() == root)\n" +
                "                active.incBeginIndex();\n" +
                "            else\n" +
                "                active.changeOriginNode();\n" +
                "            active.canonize();\n" +
                "        }\n" +
                "        updateSuffixNode(lastParentNode, parentNode);\n" +
                "        active.incEndIndex();   //Now the endpoint is the next active point\n" +
                "        active.canonize();\n" +
                "    }\n" +
                "\n" +
                "    private void updateSuffixNode(Node node, Node suffixNode) {\n" +
                "        if ((node != null) && (node != root)) {\n" +
                "            node.setSuffixNode(suffixNode);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    public int getNewNodeNumber() {\n" +
                "        return nodesCount++;\n" +
                "    }\n" +
                "\n" +
                "    public boolean contains(String str) {\n" +
                "        return indexOf(str) >= 0;\n" +
                "    }\n" +
                "\n" +
                "    public int indexOf(String str) {\n" +
                "        if (str.length() == 0)\n" +
                "            return -1;\n" +
                "\n" +
                "        int index = -1;\n" +
                "        Node node = root;\n" +
                "\n" +
                "        int i = 0;\n" +
                "        while (i<str.length()) {\n" +
                "            if ((node == null) || (i == text.length()))\n" +
                "                return -1;\n" +
                "\n" +
                "            Edge edge = node.findEdge(str.charAt(i));\n" +
                "            if (edge == null)\n" +
                "                return -1;\n" +
                "\n" +
                "            index = edge.getBeginIndex()-i;\n" +
                "            i++;\n" +
                "\n" +
                "            for(int j=edge.getBeginIndex()+1; j<=edge.getEndIndex(); j++) {\n" +
                "                if (i == str.length())\n" +
                "                    break;\n" +
                "                if (text.charAt(j) != str.charAt(i))\n" +
                "                    return -1;\n" +
                "                i++;\n" +
                "            }\n" +
                "            node = edge.getEndNode();\n" +
                "        }\n" +
                "        return index;\n" +
                "    }\n" +
                "\n" +
                "    public String getText() {\n" +
                "        return text;\n" +
                "    }\n" +
                "\n" +
                "    public Node getRootNode() {\n" +
                "        return root;\n" +
                "    }\n" +
                "}\n" +
                "package com.blogspot.illyakeeplearning.suffixtree;\n" +
                "\n" +
                "public class SuffixTree {\n" +
                "    private String text;\n" +
                "    private Node root;\n" +
                "    private int nodesCount;\n" +
                "\n" +
                "    public SuffixTree(String text) {\n" +
                "        nodesCount = 0;\n" +
                "        this.text = text;\n" +
                "        root = new Node(this, null);\n" +
                "\n" +
                "        Suffix active = new Suffix(root, 0, -1);\n" +
                "        for (int i = 0; i < text.length(); i++) {\n" +
                "            addPrefix(active, i);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    private void addPrefix(Suffix active, int endIndex) {\n" +
                "        Node lastParentNode = null;\n" +
                "        Node parentNode;\n" +
                "\n" +
                "        while (true) {\n" +
                "            Edge edge;\n" +
                "            parentNode = active.getOriginNode();\n" +
                "\n" +
                "            // Step 1 is to try and find a matching edge for the given node.\n" +
                "            // If a matching edge exists, we are done adding edges, so we break out of this big loop.\n" +
                "            if (active.isExplicit()) {\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(endIndex));\n" +
                "                if (edge != null)\n" +
                "                    break;\n" +
                "            } else {\n" +
                "                //implicit node, a little more complicated\n" +
                "                edge = active.getOriginNode().findEdge(text.charAt(active.getBeginIndex()));\n" +
                "                int span = active.getSpan();\n" +
                "                if (text.charAt(edge.getBeginIndex() + span + 1) == text.charAt(endIndex))\n" +
                "                    break;\n" +
                "                parentNode = edge.splitEdge(active);\n" +
                "            }\n" +
                "\n" +
                "            // We didn't find a matching edge, so we create a new one, add it to the tree at the parent node position,\n" +
                "            // and insert it into the hash table.  When we create a new node, it also means we need to create\n" +
                "            // a suffix link to the new node from the last node we visited.\n" +
                "            Edge newEdge = new Edge(endIndex, text.length() - 1, parentNode);\n" +
                "            newEdge.insert();\n" +
                "            updateSuffixNode(lastParentNode, parentNode);\n" +
                "            lastParentNode = parentNode;\n" +
                "\n" +
                "            // This final step is where we move to the next smaller suffix\n" +
                "            if (active.getOriginNode() == root)\n" +
                "                active.incBeginIndex();\n" +
                "            else\n" +
                "                active.changeOriginNode();\n" +
                "            active.canonize();\n" +
                "        }\n" +
                "        updateSuffixNode(lastParentNode, parentNode);\n" +
                "        active.incEndIndex();   //Now the endpoint is the next active point\n" +
                "        active.canonize();\n" +
                "    }\n" +
                "\n" +
                "    private void updateSuffixNode(Node node, Node suffixNode) {\n" +
                "        if ((node != null) && (node != root)) {\n" +
                "            node.setSuffixNode(suffixNode);\n" +
                "        }\n" +
                "    }\n" +
                "\n" +
                "    public int getNewNodeNumber() {\n" +
                "        return nodesCount++;\n" +
                "    }\n" +
                "\n" +
                "    public boolean contains(String str) {\n" +
                "        return indexOf(str) >= 0;\n" +
                "    }\n" +
                "\n" +
                "    public int indexOf(String str) {\n" +
                "        if (str.length() == 0)\n" +
                "            return -1;\n" +
                "\n" +
                "        int index = -1;\n" +
                "        Node node = root;\n" +
                "\n" +
                "        int i = 0;\n" +
                "        while (i<str.length()) {\n" +
                "            if ((node == null) || (i == text.length()))\n" +
                "                return -1;\n" +
                "\n" +
                "            Edge edge = node.findEdge(str.charAt(i));\n" +
                "            if (edge == null)\n" +
                "                return -1;\n" +
                "\n" +
                "            index = edge.getBeginIndex()-i;\n" +
                "            i++;\n" +
                "\n" +
                "            for(int j=edge.getBeginIndex()+1; j<=edge.getEndIndex(); j++) {\n" +
                "                if (i == str.length())\n" +
                "                    break;\n" +
                "                if (text.charAt(j) != str.charAt(i))\n" +
                "                    return -1;\n" +
                "                i++;\n" +
                "            }\n" +
                "            node = edge.getEndNode();\n" +
                "        }\n" +
                "        return index;\n" +
                "    }\n" +
                "\n" +
                "    public String getText() {\n" +
                "        return text;\n" +
                "    }\n" +
                "\n" +
                "    public Node getRootNode() {\n" +
                "        return root;\n" +
                "    }\n" +
                "}$");
        st.contains("size");
        //SuffixTree st = new SuffixTree("In computer science, a suffix tree (also called suffix trie, PAT tree or, in an earlier form, position tree) is a data structure that presents the suffixes of a given string in a way that allows for a particularly fast implementation of many important string operations. The suffix tree for a string S is a tree whose edges are labeled with strings, and such that each suffix of S corresponds to exactly one path from the tree's root to a leaf. It is thus a radix tree (more specifically, a Patricia trie) for the suffixes of S. Constructing such a tree for the string S takes time and space linear in the length of S. Once constructed, several operations can be performed quickly, for instance locating a substring in S, locating a substring if a certain number of mistakes are allowed, locating matches for a regular expression pattern etc. Suffix trees also provided one of the first linear-time solutions for the longest common substring problem. These speedups come at a cost: storing a string's suffix tree typically requires significantly more space than storing the string itself. $");
        //SuffixTree st = new SuffixTree("googol");
        //SuffixTree st = new SuffixTree("A worldwide community of experts is working every day to help us defeat the latest threats to your online security.");
        //SuffixTree st = new SuffixTree("googol and cacao$");
    }
}
