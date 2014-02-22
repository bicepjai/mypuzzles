import java.io.*;
import java.util.*;
 
public class solution {
 
  static ArrayList<Node> balances;
 
  static class Node {
    boolean balanced;
    int wleft; //weights
    int wright;
    int addedleft; //added weights
    int addedright;
    int totalleft; //total weight of balances on the left side
    int totalright;
    String[] lefts;
    String[] rights;
 
    public Node (int wl, String[] ln, int wr, String[] rn) {
      balanced = false;
      wleft = wl;
      wright = wr;
      addedleft = 0;
      addedright = 0;
      totalleft = 0;
      totalright = 0;
      lefts = ln;
      rights = rn;
    }
 
    public boolean isBalanced() {
      return balanced;
    }
 
    public void setBalanced() {
      balanced = true;
    }
 
    public int getLeftW() {
      return wleft;
    }
 
    public int getRightW() {
      return wright;
    }
 
    public void setLeftW(int w) {
      totalleft += w;
    }
 
    public void setRightW(int w) {
      totalright += w;
    }
 
    public int getTotalLeft() {
      return totalleft + wleft; // both weights and balances on the left
    }
 
    public int getTotalRight() {
      return totalright + wright;
    }
 
    public int getAddedLeftW() {
      return addedleft;
    }
 
    public int getAddedRightW() {
      return addedright;
    }
 
    public void setAddedLeft(int w) {
      addedleft = w;
    }
 
    public void setAddedRight(int w) {
      addedright = w;
    }
 
    public int getTotalWeight() {
      return 10 + wleft + wright + totalleft + totalright + addedleft + addedright;
    }
 
    public String[] getLefts() {
      return lefts;
    }
 
    public String[] getRights() {
      return rights;
    }
 
  }
 
  public static void weighAndBalance(Node n) {
//  System.out.println("Weighing starts.");
    String[] lefts = n.getLefts();
    if (lefts!=null) {
      for (int j=0; j<lefts.length;j++){
				weighAndBalance(balances.get(Integer.parseInt(lefts[j])));
        n.setLeftW(balances.get(Integer.parseInt(lefts[j])).getTotalWeight());
      }
    }
    String[] rights = n.getRights();
    if (rights!=null) {
      for (int j=0; j<rights.length;j++){
				weighAndBalance(balances.get(Integer.parseInt(rights[j])));
        n.setRightW(balances.get(Integer.parseInt(rights[j])).getTotalWeight());
      }
    }
//Balancing.
    int diff = n.getTotalLeft() - n.getTotalRight();
    if (diff < 0) n.setAddedLeft(0-diff);
    else n.setAddedRight(diff);
    n.setBalanced();
  }
 
  public static void main(String[] args) {
// Reading input...
    int howMany = 0;
    balances = new ArrayList<Node>();
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      String s = br.readLine();
      howMany = Integer.parseInt(s);
      for (int i = 0; i < howMany; i++) {
        String left = br.readLine().trim();
        int wl = 0;
        String[] lefts = null;
        if (left.contains(" ")) {
          wl = Integer.parseInt(left.substring(0, left.indexOf(" ")));
          lefts = left.substring(left.indexOf(" ")).trim().split(" ");
        } else {
          wl = Integer.parseInt(left);
        }
        String right = br.readLine().trim();
        int wr = 0;
        String[] rights = null;
        if (right.contains(" ")) {
          wr = Integer.parseInt(right.substring(0, right.indexOf(" ")));
          rights = right.substring(right.indexOf(" ")).trim().split(" ");
        } else {
          wr = Integer.parseInt(right);
        }
				Node node = new Node(wl, lefts, wr, rights);
        balances.add(node);
      }
      br.close();
    } catch (Exception e) {
      System.err.println("Error:" + e.getMessage());
    }
 
///Then on to balancing the balances.
 
    for (int i = 0; i < howMany; i++) {
      Node balancedNode = balances.get(i);
      if (!balancedNode.isBalanced()) {
        weighAndBalance(balancedNode);
      }
      balancedNode.setBalanced();
    }
 
// And finally printing the output
    for (int i = 0; i < howMany; i++) {
      System.out.print(i+": ");
      System.out.print(String.valueOf(balances.get(i).getAddedLeftW())+" ");
      System.out.println(String.valueOf(balances.get(i).getAddedRightW()));
    }
 
  }
 
}